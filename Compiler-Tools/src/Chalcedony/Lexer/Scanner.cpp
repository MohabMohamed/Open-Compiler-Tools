#include "Chalcedony/Lexer/Scanner.h"
#include "Chalcedony/Log.h"
#include "Chalcedony/Automata/State.hpp"
#include "Chalcedony/Lexer/Token.h"
#include <deque>
#include <iostream>
#include <stack>
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
	//reset the scanning state
	reset();
	std::string literal = "";
	//buffer to reverse the stack token
	std::deque<std::pair<Token, CT::Automata::FSMState>> token_stack_buffer;
	
	bool first_encounter = true;
	while (!input->eof())
	{
		char c = input->peek();
		if (c == '\0')
			break;

		//push the literal marker
		if (first_encounter)
			input->pushMarker();
		first_encounter = false;
		
		bool skippable_token = false;
		std::set<int> ToBeRemovedIndices;
		//check the state of each scanning machine after consuming this letter and take action according to thier state
		for (int i=0;i<m_currentMachines.size();i++)
		{
			auto state = m_currentMachines[i].first->consume(c);
			if (state == CT::Automata::FSMState::OK)
			{
				//check if skippable token then skip
				if (m_currentMachines[i].second != CT::Lexer::Token::skip)
				{
					//create a token of the current ok machine and save it
					Token result;
					result.tag = m_currentMachines[i].second.tag;
					result.event = m_currentMachines[i].second.event;
					result.literal = input->topMarker();
					token_stack_buffer.push_front(std::make_pair(result,state));
				}
			}
			else if (state == CT::Automata::FSMState::FINAL)
			{
				//check if skippable token then skip
				if (m_currentMachines[i].second != CT::Lexer::Token::skip)
				{
					//add the final token to the token stack
					//consume the letter to add it to the marker
					input->popLetter();
					Token result;
					result.tag = m_currentMachines[i].second.tag;
					result.event = m_currentMachines[i].second.event;
					result.literal = input->topMarker();
					token_stack_buffer.push_front(std::make_pair(result, state));
					//rewind the letter to continue scanning
					input->rewindLetter();
				}
				//else found a true skippable token then check if there's a token in token stack then return it it not then reset the marker
				else {
					if (!token_stack_buffer.empty())
					{
						//get a token of the stack and return it
						auto token = token_stack_buffer.back().first;
						token.literal = input->popMarker();
						if (token.event) {
							//if event has an error then call error function
							if (!token.event(input, token))
							{
								callErrorFunction(input);
								CT::Log::log(CT::LOG_LEVEL::ERROR, "error while performing token " + token.tag + " event", input->getPosition());
								return Token::invalid;
							}
						}
						return token;
					}
					else {
						//check if there's an action to process
						if (m_currentMachines[i].second.event)
						{
							Token result;
							result.tag = m_currentMachines[i].second.tag;
							result.literal = input->popMarker();
							result.event = m_currentMachines[i].second.event;
							m_currentMachines[i].second.event(input, result);
							//since this is a skip token we will process it and will do nothing about it
						}
						else
						{
							//reset marker
							input->popMarker();
							//pop the ignore letter
							input->popLetter();
						}
						//push fresh marker
						input->pushMarker();
						//reset the scan machines
						reset();
						skippable_token = true;
						//break out of the for loop
						break;
					}
				}
			}
			else if (state == CT::Automata::FSMState::DEADEND)
			{
				ToBeRemovedIndices.insert(i);
			}
		}
		//if found skippable token then continue the while loop
		if (skippable_token)
			continue;

		//add the buffered tokens to the token stack
		for (auto& token : token_stack_buffer)
			m_tokenStack.push(token);
		token_stack_buffer.clear();

		//remove the deadend machines
		int i = 0;
		m_currentMachines.erase(std::remove_if(m_currentMachines.begin(), m_currentMachines.end(), [&i, &ToBeRemovedIndices](const std::pair<std::shared_ptr<Automata::NFA<char>>, Token>& element)->bool {
			if (ToBeRemovedIndices.find(i) != ToBeRemovedIndices.end())
			{
				i++;
				return true;
			}
			i++;
			return false;
		}), m_currentMachines.end());

		//if there's no machines left check the stack if empty then return invalid token and check the error function
		if (m_currentMachines.empty()) {
			if (m_tokenStack.empty())
			{
				//then there's an error
				callErrorFunction(input);
				CT::Log::log(CT::LOG_LEVEL::ERROR, "unable to recognize string='" + literal + c + "'", input->getPosition());
				return Token::invalid;
			}
			else {
				//get a token of the stack and return it
				return popToken(input);
			}
		}

		//add c to literal
		literal += c;
		input->popLetter();
	}

	//check if the token stack not empty then return the top token
	auto stack_result = popToken(input);
	if (stack_result == Token::invalid)
		return Token::eof;
	else
		return stack_result;
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
	while (!m_tokenStack.empty())
		m_tokenStack.pop();

	m_currentMachines.clear();
	for(auto machine: m_scanningMachines)
	{
		machine.first->reset();
	}
	m_currentMachines.insert(m_currentMachines.end(), m_scanningMachines.begin(), m_scanningMachines.end());
}

Token CT::Lexer::Scanner::popToken(InputStreamPtr input)
{
	if (m_tokenStack.empty())
		return Token::invalid;
	auto token = m_tokenStack.top().first;
	auto state = m_tokenStack.top().second;
	bool found_final_token = state == CT::Automata::FSMState::FINAL;
	//search for the latest final state in the stack
	while (state == CT::Automata::FSMState::OK)
	{
		m_tokenStack.pop();
		if (m_tokenStack.empty())
		{
			//this is an error
			//this is ambiguty we didn't find a final token in the stack
			//then there's an error
			callErrorFunction(input);
			CT::Log::log(CT::LOG_LEVEL::ERROR, "cannot scan string='" + token.literal.getString() + "' as a " + token.tag, input->getPosition());
			return Token::invalid;
		}
		//pop the new token from the stack
		token = m_tokenStack.top().first;
		//rewind the input to the poped token
		input->moveToMarkerEnd(token.literal);

		state = m_tokenStack.top().second;
		found_final_token = state == CT::Automata::FSMState::FINAL;
	}

	token.literal = input->popMarker();
	if (token.event)
	{
		if (!token.event(input, token))
		{
			callErrorFunction(input);
			CT::Log::log(CT::LOG_LEVEL::ERROR, "error while performing token " + token.tag + " event", input->getPosition());
			return Token::invalid;
		}
	}
	return token;
}

bool Scanner::isIgnoreChar(char c)
{
	return m_ignoreCharSet.find(c) != m_ignoreCharSet.end();
	//return c == '\n' || c == ' ' || c == '\t' || c == '\r' || c == '\f' || c == '\v';
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