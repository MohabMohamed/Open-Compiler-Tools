#include "CLexer.h"
#include <Chalcedony/Automata/RegexBuilder.h>
#include <Chalcedony/InputStream.h>
#include <Chalcedony/Utilities.h>
#include <Chalcedony/Lexer/Token.h>
using namespace std;
using namespace CT;
using namespace CT::Lexer;
using namespace C;
void CLexer::init()
{
	CT::RegexBuilder builder;
	registerToken(builder.create("//"), CT::Lexer::make_token("SINGLE_LINE_COMMENT", [](CT::InputStreamPtr ct_input, Token& ct_token) -> bool
	{
	while (ct_input->peek() != '\n')
	{
		ct_input->popLetter();
	}
	ct_token.literal = CT::StringMarker::invalid;
	return true;
}
	));
	registerToken(builder.create("/*"), CT::Lexer::make_token("MULTI_LINE_COMMENT", [](CT::InputStreamPtr ct_input, Token& ct_token) -> bool
	{
	char prev = '\0';
	while(true)
	{
		auto c = ct_input->popLetter();
		if(c == '\0')
			return false;

		if(prev == '*' && c == '/')
			break;
		prev = c;
	}
	ct_token.literal = CT::StringMarker::invalid;
	return true;
}
	));
}
CLexer::CLexer()
{
	init();
}