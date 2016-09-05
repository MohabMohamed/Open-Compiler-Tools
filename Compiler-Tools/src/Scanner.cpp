#include "Scanner.h"
#include "Log.h"
#include <stack>
#include <iostream>
#include <sstream>

using namespace CT;
using namespace CT::Lexer;
using namespace CT::Automata;

Scanner::~Scanner()
{
	m_scanningMachines.clear();
}

Token Scanner::scan(InputStreamPtr input)
{
	//reset the current scanning machines;
	reset();
	std::string literal = "";
	std::stack<Lexer::Token> token_stack;
	//process input
	while(!input->eof())
	{
		//get the next char
		char c = input->peek();
		if (c == '\0')
		{
			return Token::eof;
		}else if(isIgnoreChar(c))
		{
			input->popLetter();
			continue;
		}
		int i=0;
		std::vector<int> m_scheduledForDeletion;
		bool isOk = false;
		//go through machines providing input and check states
		for(auto& machineTagPair: m_currentMachines)
		{
			Automata::FSMState state = machineTagPair.first->consume(StateInput<char>(c));
			if(state == FSMState::FINAL)
			{
				if (!isOk && !machineTagPair.first->hasFurtherTransitions())
				{
					//create token and return
					Lexer::Token result;
					result.tag = machineTagPair.second.tag;
					result.event = machineTagPair.second.event;
					result.literal = literal + c;

					//consume the char
					input->popLetter();
					//invoke the event function
					if (machineTagPair.second.event != nullptr)
						machineTagPair.second.event(input, result);

					return result;
				}
				else {
					//create token and return
					Lexer::Token result;
					result.tag = machineTagPair.second.tag;
					result.event = machineTagPair.second.event;
					result.literal = literal + c;
					token_stack.push(result);
				}
	
			}else if(state == FSMState::OK)
			{
				//continue scanning
				isOk = true;

			}else if(state == FSMState::DEADEND)
			{
				//schedule this machine for deletion
				m_scheduledForDeletion.push_back(i);
			}
			i++;
		}

		if(m_scheduledForDeletion.size() == m_currentMachines.size())
		{
			if (!token_stack.empty())
			{
				auto token = token_stack.top();
				if (token.event != nullptr)
					token.event(input, token);
				return token;
			}
			//error scanning report and return nullptr
			Log::log(LOG_LEVEL::ERROR, "unable to recognize string='"+literal+c+"'", input->getPosition());
			return Token::invalid;
		}
		else
		{
			std::vector<std::pair<std::shared_ptr<Automata::NFA<char>>, Token>> newCurrent;
			//delete the dead machines

			for (int i = 0; i < m_currentMachines.size(); i++)
			{
				if (std::find(m_scheduledForDeletion.begin(), m_scheduledForDeletion.end(), i) == m_scheduledForDeletion.end())
				{
					newCurrent.push_back(m_currentMachines[i]);
				}
			}

			m_currentMachines = newCurrent;
		}

		literal += c;
		input->popLetter();
	}
	if (!token_stack.empty())
		return token_stack.top();
	return Token::eof;
}

void Scanner::registerToken(std::shared_ptr<NFA<char>> regexMachine, const Token& token)
{
	std::stringstream stream;
	stream << *regexMachine;
	Log::log(CT::LOG_LEVEL::LDEBUG, stream.str(), CT::Position::invalid);
	m_scanningMachines.push_back(std::make_pair(regexMachine, token));
}

void Scanner::reset()
{
	m_currentMachines.clear();
	for(auto machine: m_scanningMachines)
	{
		machine.first->reset();
	}
	m_currentMachines.insert(m_currentMachines.end(), m_scanningMachines.begin(), m_scanningMachines.end());
}

bool Scanner::isIgnoreChar(char c)
{
	return c == '\n' || c == ' ' || c == '\t' || c == '\r' || c == '\f' || c == '\v';
}

bool Scanner::isDefinedToken(const std::string& token)
{
	for(auto machine: m_scanningMachines)
	{
		if(token == machine.second.tag)
			return true;
	}
	return false;
}

bool CT::Lexer::CachedScanner::hasCachedTokens()
{
	if (m_cache.empty())
		return false;

	if (m_index >= m_cache.size())
		return false;

	return true;
}

CT::Lexer::CachedScanner::CachedScanner()
	:m_index(0)
{
}

CT::Lexer::CachedScanner::~CachedScanner()
{
	m_cache.clear();
}

Token CT::Lexer::CachedScanner::scan(InputStreamPtr input)
{
	if (!hasCachedTokens())
	{
		auto token = Scanner::scan(input);
		m_cache.push_back(token);
		m_index = m_cache.size() - 1;
		return token;
	}
	else {
		return m_cache[m_index++];
	}
}

Token CT::Lexer::CachedScanner::rewindToken()
{
	if (m_index > 0)
	{
		m_index--;
		return m_cache[m_index];
	}
	return Token::invalid;
}
