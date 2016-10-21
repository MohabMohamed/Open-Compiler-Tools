#include "Chalcedony/Lexer/Scanner.h"
#include "Chalcedony/Log.h"
#include "Chalcedony/Lexer/Token.h"
#include <deque>
#include <iostream>
#include <stack>
#include <sstream>
using namespace CT;
using namespace CT::Lexer;
using namespace CT::Regex;

Scanner::~Scanner()
{
	m_regexPrograms.clear();
}

CT::Handle<Token> Scanner::scan(InputStreamPtr input)
{
	while (true) {
		if (input->eof())
			return Token::eof;

		reset();
		std::vector<std::pair<StringMarker, CT::Handle<Token>>> all_matches;

		s64 match_size = 0;
		for (auto& program : m_regexPrograms)
		{
			//to mark the starting of the matching
			input->pushMarker();
			//execute the program
			StringMarker match = m_vm.exec(program.first, input);
			if (match != StringMarker::invalid)
			{
				CT::Handle<Token> result = Token::getMemory().allocate(*program.second);
				//Token result = std::get<1>(program);
				result->literal = match;

				all_matches.push_back(std::make_pair(match, result));
				match_size = std::max(match_size, match.getSize());
			}
			auto start_marker = input->popMarker();
			input->moveToMarkerStart(start_marker);
		}

		for (auto& match : all_matches)
		{
			//find the first match with the maximum size
			if (match.first.getSize() == match_size)
			{
				auto token = match.second;

				//set the input to the end of the matching token
				input->moveToMarkerEnd(token->literal);

				if (token->event)
					token->event(input, *token);

				if (!token->isSkip())
					return token;
				else
					break;
			}
		}

		if (!all_matches.empty())
			continue;

		break;
	}

	return Token::invalid;
}

void Scanner::registerToken(ProgramPtr regexProgram,CT::Handle<Token> token)
{
	m_regexPrograms.emplace_back(regexProgram, token);
}

void Scanner::reset()
{
	m_vm.reset();
	for (auto& program : m_regexPrograms)
	{
		program.first->reset();
	}
}

bool Scanner::isDefinedToken(const std::string& token)
{
	for(auto program: m_regexPrograms)
	{
		if(token == program.second->tag)
			return true;
	}
	return false;
}