#include "Scanner.h"
#include "Log.h"
using namespace CT;
using namespace CT::Lexer;
using namespace CT::Automata;

Scanner::~Scanner()
{
	m_scanningMachines.clear();
}

Token Scanner::scan(std::istream& input)
{
	//reset the current scanning machines;
	reset();
	std::string literal = "";
	//process input
	while(!input.eof())
	{
		//peek the next char
		char c = input.peek();
		int i=0;
		std::vector<int> m_scheduledForDeletion;
		//go through machines providing input and check states
		for(auto machineTagPair : m_currentMachines)
		{
			Automata::FSMState state = machineTagPair.first->consume(StateInput<char>(c));
			if(state == FSMState::FINAL)
			{
				//create token and return
				Lexer::Token result;
				result.tag = machineTagPair.second.tag;
				result.event = machineTagPair.second.event;
				result.literal = literal+c;
				//consume the char
				input.get();
				//invoke the event function
				if(machineTagPair.second.event != nullptr)
					machineTagPair.second.event(input);

				return result;
			}else if(state == FSMState::OK)
			{
				//continue scanning

			}else if(state == FSMState::DEADEND)
			{
				//schedule this machine for deletion
				m_scheduledForDeletion.push_back(i);
			}
			i++;
		}

		if(m_scheduledForDeletion.size() == m_currentMachines.size())
		{
			//error scanning report and return nullptr
			Log::log(LOG_LEVEL::ERROR, "unable to recognize string='"+literal+c+"'", Position(0,0));
			return Token::invalid;
		}
		else
		{
			//delete the machine
			for(auto index: m_scheduledForDeletion)
			{
				m_currentMachines.erase(m_currentMachines.begin() + index);
			}
		}

		literal += c;
		input.get();
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