#include "SimpleCalcLexer.h"
#include <RegexBuilder.h>
#include <InputStream.h>
#include <Utilities.h>
#include <Token.h>
using namespace std;
using namespace CT;
using namespace CT::Lexer;
using namespace SimpleCalc;
void SimpleCalcLexer::init()
{
	CT::RegexBuilder builder;
	registerToken(builder.create("(0-9)+"), CT::Lexer::make_token("INT"));
	registerToken(builder.create("(0-9)*.(0-9)+"), CT::Lexer::make_token("REAL"));
	registerToken(builder.create("\\+"), CT::Lexer::make_token("PLUS"));
	registerToken(builder.create("\\*\\*"), CT::Lexer::make_token("POWER"));
	registerToken(builder.create("\\*"), CT::Lexer::make_token("MUL"));
	registerToken(builder.create("/"), CT::Lexer::make_token("DIV"));
	registerToken(builder.create("\\-"), CT::Lexer::make_token("SUB"));
	registerToken(builder.create("="), CT::Lexer::make_token("ASSIGN"));
	registerToken(builder.create("\\("), CT::Lexer::make_token("LPAREN"));
	registerToken(builder.create("\\)"), CT::Lexer::make_token("RPAREN"));
	registerToken(builder.create("//"), CT::Lexer::make_token("COMMENT", [](CT::InputStreamPtr input, Token& token) -> bool
	{
		token.literal = "";
		while (input->peek() != '\n')
		{
			token.literal += input->popLetter();
		}
		return true;
	}
	));
	registerToken(builder.create("(a-z|A-Z|_)(a-z|A-Z|_|0-9)*"), CT::Lexer::make_token("ID"));
}
SimpleCalcLexer::SimpleCalcLexer()
{
	init();
}