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
	registerToken(builder.create("(0-9)+"), make_tagged_token("INT",0));
	registerToken(builder.create("(0-9)*.(0-9)+"), make_tagged_token("REAL",1));
	registerToken(builder.create("\\+"), make_tagged_token("PLUS",2));
	registerToken(builder.create("\\*\\*"), make_tagged_token("POWER",3));
	registerToken(builder.create("\\*"), make_tagged_token("MUL",4));
	registerToken(builder.create("/"), make_tagged_token("DIV",5));
	registerToken(builder.create("\\-"), make_tagged_token("SUB",6));
	registerToken(builder.create("="), make_tagged_token("ASSIGN",7));
	registerToken(builder.create("\\("), make_tagged_token("LPAREN",8));
	registerToken(builder.create("\\)"), make_tagged_token("RPAREN",9));
	registerToken(builder.create("//"), make_tagged_token("COMMENT",10, [](CT::InputStreamPtr input, Token& token) -> bool
	{
		token.literal = "";
		while (input->peek() != '\n')
		{
			token.literal += input->popLetter();
		}
		return true;
	}
	));
	registerToken(builder.create("(a-z|A-Z|_)(a-z|A-Z|_|0-9)*"), make_tagged_token("ID",11));
}
SimpleCalcLexer::SimpleCalcLexer()
{
	init();
}