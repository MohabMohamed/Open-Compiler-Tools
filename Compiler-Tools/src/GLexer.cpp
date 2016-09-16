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
	registerToken(builder.create(";"), make_token_lib("semicolon"));
	registerToken(builder.create("#name"), make_token_lib("name_directive", [](CT::InputStreamPtr input, Token& token) -> bool {
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

	registerToken(builder.create("(A-Z)+"), make_token_lib("lex_id"));
	registerToken(builder.create(":="), make_token_lib("assign"));

	registerToken(builder.create("\""), make_token_lib("regex", [](CT::InputStreamPtr input, Token& token) -> bool {
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

	registerToken(builder.create("{"), make_token_lib("action", [](CT::InputStreamPtr input, Token& token) -> bool {
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

	registerToken(builder.create("(a-z)+"), make_token_lib("parse_id"));
	registerToken(builder.create("\\|"), make_token_lib("or"));
	registerToken(builder.create("_start_"), make_token_lib("start_rule"));

}

GLexer::GLexer()
{
	init();
}

CT::Lexer::GLexer::~GLexer()
{
}
