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
	registerToken(builder.create("auto"), CT::Lexer::make_token("Auto"));
	registerToken(builder.create("break"), CT::Lexer::make_token("Break"));
	registerToken(builder.create("case"), CT::Lexer::make_token("Case"));
	registerToken(builder.create("char"), CT::Lexer::make_token("Char"));
	registerToken(builder.create("const"), CT::Lexer::make_token("Const"));
	registerToken(builder.create("continue"), CT::Lexer::make_token("Continue"));
	registerToken(builder.create("default"), CT::Lexer::make_token("Default"));
	registerToken(builder.create("double"), CT::Lexer::make_token("Double"));
	registerToken(builder.create("do"), CT::Lexer::make_token("Do"));
	registerToken(builder.create("else"), CT::Lexer::make_token("Else"));
	registerToken(builder.create("enum"), CT::Lexer::make_token("Enum"));
	registerToken(builder.create("extern"), CT::Lexer::make_token("Extern"));
	registerToken(builder.create("float"), CT::Lexer::make_token("Float"));
	registerToken(builder.create("for"), CT::Lexer::make_token("For"));
	registerToken(builder.create("goto"), CT::Lexer::make_token("Goto"));
	registerToken(builder.create("if"), CT::Lexer::make_token("If"));
	registerToken(builder.create("inline"), CT::Lexer::make_token("Inline"));
	registerToken(builder.create("int"), CT::Lexer::make_token("Int"));
	registerToken(builder.create("long"), CT::Lexer::make_token("Long"));
	registerToken(builder.create("register"), CT::Lexer::make_token("Register"));
	registerToken(builder.create("restrict"), CT::Lexer::make_token("Restrict"));
	registerToken(builder.create("return"), CT::Lexer::make_token("Return"));
	registerToken(builder.create("short"), CT::Lexer::make_token("Short"));
	registerToken(builder.create("signed"), CT::Lexer::make_token("Signed"));
	registerToken(builder.create("sizeof"), CT::Lexer::make_token("Sizeof"));
	registerToken(builder.create("static"), CT::Lexer::make_token("Static"));
	registerToken(builder.create("struct"), CT::Lexer::make_token("Struct"));
	registerToken(builder.create("switch"), CT::Lexer::make_token("Switch"));
	registerToken(builder.create("typedef"), CT::Lexer::make_token("Typedef"));
	registerToken(builder.create("union"), CT::Lexer::make_token("Union"));
	registerToken(builder.create("unsigned"), CT::Lexer::make_token("Unsigned"));
	registerToken(builder.create("void"), CT::Lexer::make_token("Void"));
	registerToken(builder.create("volatile"), CT::Lexer::make_token("Volatile"));
	registerToken(builder.create("while"), CT::Lexer::make_token("While"));
	registerToken(builder.create("_Alignas"), CT::Lexer::make_token("Alignas"));
	registerToken(builder.create("_Alignof"), CT::Lexer::make_token("Alignof"));
	registerToken(builder.create("_Atomic"), CT::Lexer::make_token("Atomic"));
	registerToken(builder.create("_Bool"), CT::Lexer::make_token("Bool"));
	registerToken(builder.create("_Complex"), CT::Lexer::make_token("Complex"));
	registerToken(builder.create("_Generic"), CT::Lexer::make_token("Generic"));
	registerToken(builder.create("_Imaginary"), CT::Lexer::make_token("Imaginary"));
	registerToken(builder.create("_Noreturn"), CT::Lexer::make_token("Noreturn"));
	registerToken(builder.create("_Static_assert"), CT::Lexer::make_token("StaticAssert"));
	registerToken(builder.create("_Thread_local"), CT::Lexer::make_token("ThreadLocal"));
	registerToken(builder.create("\\("), CT::Lexer::make_token("LeftParen"));
	registerToken(builder.create("\\)"), CT::Lexer::make_token("RightParen"));
	registerToken(builder.create("["), CT::Lexer::make_token("LeftBracket"));
	registerToken(builder.create("]"), CT::Lexer::make_token("RightBracket"));
	registerToken(builder.create("{"), CT::Lexer::make_token("LeftBrace"));
	registerToken(builder.create("}"), CT::Lexer::make_token("RightBrace"));
	registerToken(builder.create("\\*="), CT::Lexer::make_token("StarAssign"));
	registerToken(builder.create("/="), CT::Lexer::make_token("DivAssign"));
	registerToken(builder.create("%="), CT::Lexer::make_token("ModAssign"));
	registerToken(builder.create("\\+="), CT::Lexer::make_token("PlusAssign"));
	registerToken(builder.create("\\-="), CT::Lexer::make_token("MinusAssign"));
	registerToken(builder.create("<<="), CT::Lexer::make_token("LeftShiftAssign"));
	registerToken(builder.create(">>="), CT::Lexer::make_token("RightShiftAssign"));
	registerToken(builder.create("&="), CT::Lexer::make_token("AndAssign"));
	registerToken(builder.create("\\|="), CT::Lexer::make_token("XorAssign"));
	registerToken(builder.create("=="), CT::Lexer::make_token("Equal"));
	registerToken(builder.create("!="), CT::Lexer::make_token("NotEqual"));
	registerToken(builder.create("="), CT::Lexer::make_token("Assign"));
	registerToken(builder.create("<<"), CT::Lexer::make_token("LeftShift"));
	registerToken(builder.create(">>"), CT::Lexer::make_token("RightShift"));
	registerToken(builder.create("<="), CT::Lexer::make_token("LessEqual"));
	registerToken(builder.create("<"), CT::Lexer::make_token("Less"));
	registerToken(builder.create(">="), CT::Lexer::make_token("GreaterEqual"));
	registerToken(builder.create(">"), CT::Lexer::make_token("Greater"));
	registerToken(builder.create("\\+\\+"), CT::Lexer::make_token("PlusPlus"));
	registerToken(builder.create("\\+"), CT::Lexer::make_token("Plus"));
	registerToken(builder.create("\\->"), CT::Lexer::make_token("Arrow"));
	registerToken(builder.create("..."), CT::Lexer::make_token("Ellipsis"));
	registerToken(builder.create("."), CT::Lexer::make_token("Dot"));
	registerToken(builder.create("\\-\\-"), CT::Lexer::make_token("MinusMinus"));
	registerToken(builder.create("\\-"), CT::Lexer::make_token("Minus"));
	registerToken(builder.create("\\*"), CT::Lexer::make_token("Star"));
	registerToken(builder.create("/"), CT::Lexer::make_token("Div"));
	registerToken(builder.create("%"), CT::Lexer::make_token("Mod"));
	registerToken(builder.create("&&"), CT::Lexer::make_token("AndAnd"));
	registerToken(builder.create("&"), CT::Lexer::make_token("And"));
	registerToken(builder.create("\\|\\|"), CT::Lexer::make_token("OrOr"));
	registerToken(builder.create("\\|"), CT::Lexer::make_token("Or"));
	registerToken(builder.create("^"), CT::Lexer::make_token("Caret"));
	registerToken(builder.create("!"), CT::Lexer::make_token("Not"));
	registerToken(builder.create("~"), CT::Lexer::make_token("Tilde"));
	registerToken(builder.create("?"), CT::Lexer::make_token("Question"));
	registerToken(builder.create(":"), CT::Lexer::make_token("Colon"));
	registerToken(builder.create(";"), CT::Lexer::make_token("Semi"));
	registerToken(builder.create(","), CT::Lexer::make_token("Comma"));
	registerToken(builder.create("#"), CT::Lexer::make_token("Hash"));
	registerToken(builder.create("pragma"), CT::Lexer::make_token("Pragma"));
	registerToken(builder.create("include"), CT::Lexer::make_token("Include"));
	registerToken(builder.create("(0-9)"), CT::Lexer::make_token("Digit"));
	registerToken(builder.create("(0-9)(a-z)(0-9)|(0-9)"), CT::Lexer::make_token("Identifier"));
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
	registerToken(builder.create("#"), CT::Lexer::make_token("HASH"));
	registerToken(builder.create("include"), CT::Lexer::make_token("INCLUDE"));
}
CLexer::CLexer()
{
	init();
}