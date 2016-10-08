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
	registerToken(builder.create("(\n)"), CT::Lexer::make_token());
	registerToken(builder.create("(\r)"), CT::Lexer::make_token());
	registerToken(builder.create("( )"), CT::Lexer::make_token());
	registerToken(builder.create("(\t)"), CT::Lexer::make_token());
	registerToken(builder.create("(\v)"), CT::Lexer::make_token());
	registerToken(builder.create("(\f)"), CT::Lexer::make_token());
	registerToken(builder.create("(auto)"), CT::Lexer::make_token("Auto"));
	registerToken(builder.create("(break)"), CT::Lexer::make_token("Break"));
	registerToken(builder.create("(case)"), CT::Lexer::make_token("Case"));
	registerToken(builder.create("(char)"), CT::Lexer::make_token("Char"));
	registerToken(builder.create("(const)"), CT::Lexer::make_token("Const"));
	registerToken(builder.create("(continue)"), CT::Lexer::make_token("Continue"));
	registerToken(builder.create("(default)"), CT::Lexer::make_token("Default"));
	registerToken(builder.create("(double)"), CT::Lexer::make_token("Double"));
	registerToken(builder.create("(do)"), CT::Lexer::make_token("Do"));
	registerToken(builder.create("(else)"), CT::Lexer::make_token("Else"));
	registerToken(builder.create("(enum)"), CT::Lexer::make_token("Enum"));
	registerToken(builder.create("(extern)"), CT::Lexer::make_token("Extern"));
	registerToken(builder.create("(float)"), CT::Lexer::make_token("Float"));
	registerToken(builder.create("(for)"), CT::Lexer::make_token("For"));
	registerToken(builder.create("(goto)"), CT::Lexer::make_token("Goto"));
	registerToken(builder.create("(if)"), CT::Lexer::make_token("If"));
	registerToken(builder.create("(inline)"), CT::Lexer::make_token("Inline"));
	registerToken(builder.create("(__inline__)"), CT::Lexer::make_token("InlineGCC"));
	registerToken(builder.create("(int)"), CT::Lexer::make_token("Int"));
	registerToken(builder.create("(long)"), CT::Lexer::make_token("Long"));
	registerToken(builder.create("(register)"), CT::Lexer::make_token("Register"));
	registerToken(builder.create("(restrict)"), CT::Lexer::make_token("Restrict"));
	registerToken(builder.create("(return)"), CT::Lexer::make_token("Return"));
	registerToken(builder.create("(short)"), CT::Lexer::make_token("Short"));
	registerToken(builder.create("(signed)"), CT::Lexer::make_token("Signed"));
	registerToken(builder.create("(sizeof)"), CT::Lexer::make_token("Sizeof"));
	registerToken(builder.create("(static)"), CT::Lexer::make_token("Static"));
	registerToken(builder.create("(struct)"), CT::Lexer::make_token("Struct"));
	registerToken(builder.create("(switch)"), CT::Lexer::make_token("Switch"));
	registerToken(builder.create("(typedef)"), CT::Lexer::make_token("Typedef"));
	registerToken(builder.create("(union)"), CT::Lexer::make_token("Union"));
	registerToken(builder.create("(unsigned)"), CT::Lexer::make_token("Unsigned"));
	registerToken(builder.create("(void)"), CT::Lexer::make_token("Void"));
	registerToken(builder.create("(volatile)"), CT::Lexer::make_token("Volatile"));
	registerToken(builder.create("(while)"), CT::Lexer::make_token("While"));
	registerToken(builder.create("(_Alignas)"), CT::Lexer::make_token("Alignas"));
	registerToken(builder.create("(_Alignof)"), CT::Lexer::make_token("Alignof"));
	registerToken(builder.create("(_Atomic)"), CT::Lexer::make_token("Atomic"));
	registerToken(builder.create("(_Bool)"), CT::Lexer::make_token("Bool"));
	registerToken(builder.create("(_Complex)"), CT::Lexer::make_token("Complex"));
	registerToken(builder.create("(_Generic)"), CT::Lexer::make_token("Generic"));
	registerToken(builder.create("(_Imaginary)"), CT::Lexer::make_token("Imaginary"));
	registerToken(builder.create("(_Noreturn)"), CT::Lexer::make_token("Noreturn"));
	registerToken(builder.create("(_Static_assert)"), CT::Lexer::make_token("StaticAssert"));
	registerToken(builder.create("(_Thread_local)"), CT::Lexer::make_token("ThreadLocal"));
	registerToken(builder.create("(__extension__)"), CT::Lexer::make_token("Extension"));
	registerToken(builder.create("(__builtin_va_arg)"), CT::Lexer::make_token("BuiltInVaArg"));
	registerToken(builder.create("(__builtin_offsetof)"), CT::Lexer::make_token("BuiltInOffsetOf"));
	registerToken(builder.create("(__m128)"), CT::Lexer::make_token("SIMDNoType"));
	registerToken(builder.create("(__m128d)"), CT::Lexer::make_token("SIMDDType"));
	registerToken(builder.create("(__m128i)"), CT::Lexer::make_token("SIMDIType"));
	registerToken(builder.create("(__typeof__)"), CT::Lexer::make_token("TypeOf"));
	registerToken(builder.create("(__stdcall)"), CT::Lexer::make_token("StdCall"));
	registerToken(builder.create("(__declspec)"), CT::Lexer::make_token("DeclSpec"));
	registerToken(builder.create("(__asm)"), CT::Lexer::make_token("Asm"));
	registerToken(builder.create("(__attribute__)"), CT::Lexer::make_token("Attribute"));
	registerToken(builder.create("(//)"), CT::Lexer::make_token([](CT::InputStreamPtr ct_input, Token& ct_token) -> bool
	{
	ct_input->pushMarker(ct_token.literal);
	while (ct_input->peek() != '\n')
	{
		ct_input->popLetter();
	}
	ct_token.literal = ct_input->popMarker();
	return true;
}
	));
	registerToken(builder.create("(/\\*)"), CT::Lexer::make_token([](CT::InputStreamPtr ct_input, Token& ct_token) -> bool
	{
	ct_input->pushMarker(ct_token.literal);
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
	ct_token.literal = ct_input->popMarker();
	return true;
}
	));
	registerToken(builder.create("(\\()"), CT::Lexer::make_token("LeftParen"));
	registerToken(builder.create("(\\))"), CT::Lexer::make_token("RightParen"));
	registerToken(builder.create("([)"), CT::Lexer::make_token("LeftBracket"));
	registerToken(builder.create("(])"), CT::Lexer::make_token("RightBracket"));
	registerToken(builder.create("({)"), CT::Lexer::make_token("LeftBrace"));
	registerToken(builder.create("(})"), CT::Lexer::make_token("RightBrace"));
	registerToken(builder.create("(<<)"), CT::Lexer::make_token("LeftShift"));
	registerToken(builder.create("(>>)"), CT::Lexer::make_token("RightShift"));
	registerToken(builder.create("(<=)"), CT::Lexer::make_token("LessEqual"));
	registerToken(builder.create("(>=)"), CT::Lexer::make_token("GreaterEqual"));
	registerToken(builder.create("(\\*=)"), CT::Lexer::make_token("StarAssign"));
	registerToken(builder.create("(/=)"), CT::Lexer::make_token("DivAssign"));
	registerToken(builder.create("(%=)"), CT::Lexer::make_token("ModAssign"));
	registerToken(builder.create("(\\+=)"), CT::Lexer::make_token("PlusAssign"));
	registerToken(builder.create("(\\-=)"), CT::Lexer::make_token("MinusAssign"));
	registerToken(builder.create("(<<=)"), CT::Lexer::make_token("LeftShiftAssign"));
	registerToken(builder.create("(>>=)"), CT::Lexer::make_token("RightShiftAssign"));
	registerToken(builder.create("(&=)"), CT::Lexer::make_token("AndAssign"));
	registerToken(builder.create("(^=)"), CT::Lexer::make_token("XorAssign"));
	registerToken(builder.create("(\\|=)"), CT::Lexer::make_token("OrAssign"));
	registerToken(builder.create("(==)"), CT::Lexer::make_token("Equal"));
	registerToken(builder.create("(!=)"), CT::Lexer::make_token("NotEqual"));
	registerToken(builder.create("(=)"), CT::Lexer::make_token("Assign"));
	registerToken(builder.create("(\\+\\+)"), CT::Lexer::make_token("PlusPlus"));
	registerToken(builder.create("(\\->)"), CT::Lexer::make_token("Arrow"));
	registerToken(builder.create("(...)"), CT::Lexer::make_token("Ellipsis"));
	registerToken(builder.create("(\\-\\-)"), CT::Lexer::make_token("MinusMinus"));
	registerToken(builder.create("(&&)"), CT::Lexer::make_token("AndAnd"));
	registerToken(builder.create("(\\|\\|)"), CT::Lexer::make_token("OrOr"));
	registerToken(builder.create("(^)"), CT::Lexer::make_token("Caret"));
	registerToken(builder.create("(!)"), CT::Lexer::make_token("Not"));
	registerToken(builder.create("(~)"), CT::Lexer::make_token("Tilde"));
	registerToken(builder.create("(>)"), CT::Lexer::make_token("Greater"));
	registerToken(builder.create("(<)"), CT::Lexer::make_token("Less"));
	registerToken(builder.create("(&)"), CT::Lexer::make_token("And"));
	registerToken(builder.create("(\\|)"), CT::Lexer::make_token("Or"));
	registerToken(builder.create("(\\-)"), CT::Lexer::make_token("Minus"));
	registerToken(builder.create("(\\*)"), CT::Lexer::make_token("Star"));
	registerToken(builder.create("(/)"), CT::Lexer::make_token("Div"));
	registerToken(builder.create("(%)"), CT::Lexer::make_token("Mod"));
	registerToken(builder.create("(\\+)"), CT::Lexer::make_token("Plus"));
	registerToken(builder.create("(.)"), CT::Lexer::make_token("Dot"));
	registerToken(builder.create("(\\?)"), CT::Lexer::make_token("Question"));
	registerToken(builder.create("(:)"), CT::Lexer::make_token("Colon"));
	registerToken(builder.create("(;)"), CT::Lexer::make_token("Semi"));
	registerToken(builder.create("(,)"), CT::Lexer::make_token("Comma"));
	registerToken(builder.create("(#)"), CT::Lexer::make_token("Hash"));
	registerToken(builder.create("(pragma)"), CT::Lexer::make_token("Pragma"));
	registerToken(builder.create("(include)"), CT::Lexer::make_token("Include"));
	registerToken(builder.create("(define)"), CT::Lexer::make_token("Define"));
	registerToken(builder.create("((((a-z|A-Z|_))|((\\\\u(((0-9|a-f|A-F))((0-9|a-f|A-F))((0-9|a-f|A-F))((0-9|a-f|A-F))))|(\\\\U(((0-9|a-f|A-F))((0-9|a-f|A-F))((0-9|a-f|A-F))((0-9|a-f|A-F))))))((((a-z|A-Z|_))|((\\\\u(((0-9|a-f|A-F))((0-9|a-f|A-F))((0-9|a-f|A-F))((0-9|a-f|A-F))))|(\\\\U(((0-9|a-f|A-F))((0-9|a-f|A-F))((0-9|a-f|A-F))((0-9|a-f|A-F))))))|((0-9)))*)"), CT::Lexer::make_token("Identifier"));
	registerToken(builder.create("(((((((1-9))((0-9))*)((((u|U))((l|L))?)|(((u|U))((ll|LL)))|(((l|L))((u|U))?)|(((ll|LL))((u|U))?))?)|((0((0-7))*)((((u|U))((l|L))?)|(((u|U))((ll|LL)))|(((l|L))((u|U))?)|(((ll|LL))((u|U))?))?)|(((0(x|X))((0-9|a-f|A-F))+)((((u|U))((l|L))?)|(((u|U))((ll|LL)))|(((l|L))((u|U))?)|(((ll|LL))((u|U))?))?)|(0 (b|B) (0|1)+))|((((((((0-9))+)?.(((0-9))+))|((((0-9))+).))((e((\\+ | \\-))?(((0-9))+))|(E((\\+ | \\-))?(((0-9))+)))?((f|l|F|L))?)|((((0-9))+)((e((\\+ | \\-))?(((0-9))+))|(E((\\+ | \\-))?(((0-9))+)))((f|l|F|L))?))|(((0(x|X))(((((0-9|a-f|A-F))+)?.(((0-9|a-f|A-F))+))|((((0-9|a-f|A-F))+).))(((p|P)((\\+ | \\-))?(((0-9))+)))((f|l|F|L))?)|((0(x|X))(((0-9|a-f|A-F))+)(((p|P)((\\+ | \\-))?(((0-9))+)))((f|l|F|L))?)))))"), CT::Lexer::make_token("Constant"));
	registerToken(builder.create("(((u8)|(u|U|L))?\")"), CT::Lexer::make_token("StringConstant", [](CT::InputStreamPtr ct_input, Token& ct_token) -> bool
	{
	ct_input->pushMarker(ct_token.literal);
	char prev = '\0';
	auto c = ct_input->peek();
	while(true)
	{
		bool ignore = false;
		if(prev == '\\')
			ignore = true;
		if(c == '"' && !ignore)
			break;
		//pop peeked letter
		ct_input->popLetter();
		prev = c;
		c = ct_input->peek();
	}
	ct_input->popLetter();
	ct_token.literal = ct_input->popMarker();
	return true;
}
	));
	registerToken(builder.create("(')"), CT::Lexer::make_token("CharConstant", [](CT::InputStreamPtr ct_input, Token& ct_token) -> bool
	{
	ct_input->pushMarker(ct_token.literal);
	char val = ct_input->popLetter();
	char close_quote = ct_input->popLetter();
	if(close_quote != '\''){
		ct_input->rewindLetter();
		ct_input->rewindLetter();
		return false;
	}
	ct_token.literal = ct_input->popMarker();
	return true;
}
	));
}
CLexer::CLexer()
{
	init();
}