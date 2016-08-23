#include "Scanner.h"
#include "Log.h"
#include <stack>
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
		if(isIgnoreChar(c))
		{
			input->popLetter();
			continue;
		}
		int i=0;
		std::vector<int> m_scheduledForDeletion;
		bool isOk = false;
		//go through machines providing input and check states
		for(int ix=0;ix<m_currentMachines.size();ix++)
		{
			auto machineTagPair = m_currentMachines[ix];
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
						machineTagPair.second.event(input);

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
					token.event(input);
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
	return Token::eof;
}

void Scanner::registerToken(std::shared_ptr<NFA<char>> regexMachine, const Token& token)
{
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