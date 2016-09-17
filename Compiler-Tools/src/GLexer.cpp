#include "GLexer.h"
#include "RegexBuilder.h"
#include "InputStream.h"
#include "Utilities.h"
#include "Token.h"
using namespace std;
using namespace CT;
using namespace CT::Lexer;

void GLexer::init()
{
	CT::RegexBuilder builder;
	registerToken(builder.create(";"), make_token("semicolon"));
	registerToken(builder.create("#name"), make_token("name_directive", [](CT::InputStreamPtr input, Token& token) -> bool {
		token.literal = "";
		char pc = input->peek();
		while (pc != '\n' && pc != ';')
		{
			token.literal += input->popLetter();
			pc = input->peek();
		}
		trim(token.literal);
		return true;
	}));

	auto code_segment_action = [](CT::InputStreamPtr input, Token& token) -> bool {

	};

	registerToken(builder.create("#header"), make_token("header_code", [](CT::InputStreamPtr input, Token& token) -> bool {
		token.literal = "";
		int i = 0;
		while (true)
		{
			auto c = input->popLetter();
			if (c == '{')
			{
				input->rewindLetter();
				break;
			}
		}

		while (true)
		{
			auto c = input->popLetter();
			if (c == '{')
			{
				i++;
			}
			else if (c == '}')
			{
				i--;
			}
			else {
				token.literal += c;
			}

			if (i == 0)
				break;
		}

		return true;
	}));

	registerToken(builder.create("#cpp"), make_token("cpp_code", [](CT::InputStreamPtr input, Token& token) -> bool {
		token.literal = "";
		int i = 0;
		while (true)
		{
			auto c = input->popLetter();
			if (c == '{')
			{
				input->rewindLetter();
				break;
			}
		}

		while (true)
		{
			auto c = input->popLetter();
			if (c == '{')
			{
				i++;
			}
			else if (c == '}')
			{
				i--;
			}
			else {
				token.literal += c;
			}

			if (i == 0)
				break;
		}

		return true;
	}));

	registerToken(builder.create("(A-Z)+"), make_token("lex_id"));
	registerToken(builder.create(":="), make_token("assign"));

	registerToken(builder.create("\""), make_token("regex", [](CT::InputStreamPtr input, Token& token) -> bool {
		token.literal = "";
		char prev = '\0';
		while (true) {
			char c = input->peek();
			if (c == '"' && prev == '\\')
				token.literal += c;
			else if (c == '"')
				break;

			token.literal += c;

			prev = input->popLetter();
		}
		//pop last quote
		input->popLetter();
		return true;
	}));

	registerToken(builder.create("{"), make_token("action", [](CT::InputStreamPtr input, Token& token) -> bool {
		int counter = 1;
		while (counter != 0)
		{
			char c = input->peek();
			if (c == '{')
				counter++;
			else if (c == '}')
				counter--;

			token.literal += c;
			input->popLetter();
		}
		return true;
	}));

	registerToken(builder.create("(a-z)+"), make_token("parse_id"));
	registerToken(builder.create("\\|"), make_token("or"));
	registerToken(builder.create("_start_"), make_token("start_rule"));

}

GLexer::GLexer()
{
	init();
}

CT::Lexer::GLexer::~GLexer()
{
}
