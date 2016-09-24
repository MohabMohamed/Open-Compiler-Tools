#include "Scanner.h"
#include "Log.h"
#include "State.hpp"
#include "Token.h"
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
	//input->pushMarker();
	std::stack<Lexer::Token> token_stack;

	bool is_first_encounter = true;
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
			if(is_first_encounter){
				input->popLetter();
				continue;
			}else{
				if (!token_stack.empty())
				{
					auto token = token_stack.top();
					token.literal = input->popMarker();
					if (token.event != nullptr)
					{
						auto eventResult = token.event(input, token);
						if (!eventResult)
							callErrorFunction(input);
					}
					auto inspect = token.literal.getString();
					return token;
				}
			}
		}

		if (is_first_encounter)
			input->pushMarker();
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
					//result.literal = literal + c;
					

					//consume the char
					input->popLetter();

					result.literal = input->popMarker();
					//invoke the event function
					if (machineTagPair.second.event != nullptr) {

						auto eventResult = machineTagPair.second.event(input, result);
						if (!eventResult)
							callErrorFunction(input);
					}
					auto inspect = result.literal.getString();
					return result;
				}
				else {
					//create token and return
					Lexer::Token result;
					result.tag = machineTagPair.second.tag;
					result.event = machineTagPair.second.event;
					//result.literal = literal + c;
					result.literal = input->topMarker();
					auto inspect = result.literal.getString();
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
		is_first_encounter = false;

		if(m_scheduledForDeletion.size() == m_currentMachines.size())
		{
			if (!token_stack.empty())
			{
				auto token = token_stack.top();
				token.literal = input->popMarker();
				if (token.event != nullptr)
				{

					auto eventResult = token.event(input, token);
					if (!eventResult)
						callErrorFunction(input);
				}
				auto inspect = token.literal.getString();
				return token;
			}
			//error scanning report and return nullptr
			Log::log(LOG_LEVEL::ERROR, "unable to recognize string='"+literal+c+"'", input->getPosition());
			callErrorFunction(input);
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
	if (!token_stack.empty()) {
		auto token = token_stack.top();
		token.literal = input->popMarker();
		if (token.event != nullptr)
		{
			auto eventResult = token.event(input, token);
			if (!eventResult)
				callErrorFunction(input);
		}
		return token_stack.top();
	}
	return Token::eof;
}

void Scanner::registerToken(std::shared_ptr<NFA<char>> regexMachine, const Token& token)
{
	std::stringstream stream;
	stream << *regexMachine;
	Log::log(CT::LOG_LEVEL::LDEBUG, stream.str(), CT::FilePosition::invalid);
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