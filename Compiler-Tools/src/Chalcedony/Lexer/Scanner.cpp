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

Token Scanner::scan(InputStreamPtr input)
{
	while (true)
	{
		if (input->eof())
			return Token::eof;

		reset();
		std::vector<std::tuple<StringMarker, Token>> all_matches;
		all_matches.reserve(m_regexPrograms.size());

		s64 match_size = 0;
		for (auto program : m_regexPrograms)
		{
			//to mark the starting of the matching
			input->pushMarker();
			//execute the program
			StringMarker match = m_vm.exec(std::get<0>(program), input);
			if (match != StringMarker::invalid)
			{
				Token result = std::get<1>(program);
				result.literal = match;

				all_matches.push_back(std::make_tuple(match, result));
				match_size = std::max(match_size, match.getSize());
			}
			auto start_marker = input->popMarker();
			input->moveToMarkerStart(start_marker);
		}

		for (auto match : all_matches)
		{
			//find the first match with the maximum size
			if (std::get<0>(match).getSize() == match_size)
			{
				auto token = std::get<1>(match);

				//set the input to the end of the matching token
				input->moveToMarkerEnd(token.literal);

				if (token.event)
					token.event(input, token);

				if (token != Token::skip)
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

void Scanner::registerToken(ProgramPtr regexProgram, const Token& token)
{
	m_regexPrograms.push_back(std::make_tuple(regexProgram, token));
}

void Scanner::reset()
{
	m_vm.reset();
	for (auto program : m_regexPrograms)
	{
		std::get<0>(program)->reset();
	}
}

bool Scanner::isDefinedToken(const std::string& token)
{
	for(auto program: m_regexPrograms)
	{
		if(token == std::get<1>(program).tag)
			return true;
	}
	return false;
}