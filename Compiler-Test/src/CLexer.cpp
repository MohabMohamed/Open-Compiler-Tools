#include "CLexer.h"
#include <Chalcedony/Regex/Compiler.h>
#include <Chalcedony/Regex/Program.h>
#include <Chalcedony/InputStream.h>
#include <Chalcedony/Utilities.h>
#include <Chalcedony/Lexer/Token.h>
using namespace std;
using namespace CT;
using namespace CT::Lexer;
using namespace CT::Regex;
using namespace C;
void CLexer::init()
{
	CT::Regex::Compiler compiler;
	registerToken(compiler.compile("(\n)"), CT::Lexer::make_token());
	registerToken(compiler.compile("(\r)"), CT::Lexer::make_token());
	registerToken(compiler.compile("( )"), CT::Lexer::make_token());
	registerToken(compiler.compile("(\t)"), CT::Lexer::make_token());
	registerToken(compiler.compile("(\v)"), CT::Lexer::make_token());
	registerToken(compiler.compile("(\f)"), CT::Lexer::make_token());
	registerToken(compiler.compile("(auto)"), CT::Lexer::make_token("Auto"));
	registerToken(compiler.compile("(break)"), CT::Lexer::make_token("Break"));
	registerToken(compiler.compile("(case)"), CT::Lexer::make_token("Case"));
	registerToken(compiler.compile("(char)"), CT::Lexer::make_token("Char"));
	registerToken(compiler.compile("(const)"), CT::Lexer::make_token("Const"));
	registerToken(compiler.compile("(continue)"), CT::Lexer::make_token("Continue"));
	registerToken(compiler.compile("(default)"), CT::Lexer::make_token("Default"));
	registerToken(compiler.compile("(double)"), CT::Lexer::make_token("Double"));
	registerToken(compiler.compile("(do)"), CT::Lexer::make_token("Do"));
	registerToken(compiler.compile("(else)"), CT::Lexer::make_token("Else"));
	registerToken(compiler.compile("(enum)"), CT::Lexer::make_token("Enum"));
	registerToken(compiler.compile("(extern)"), CT::Lexer::make_token("Extern"));
	registerToken(compiler.compile("(float)"), CT::Lexer::make_token("Float"));
	registerToken(compiler.compile("(for)"), CT::Lexer::make_token("For"));
	registerToken(compiler.compile("(goto)"), CT::Lexer::make_token("Goto"));
	registerToken(compiler.compile("(if)"), CT::Lexer::make_token("If"));
	registerToken(compiler.compile("(inline)"), CT::Lexer::make_token("Inline"));
	registerToken(compiler.compile("(__inline__)"), CT::Lexer::make_token("InlineGCC"));
	registerToken(compiler.compile("(int)"), CT::Lexer::make_token("Int"));
	registerToken(compiler.compile("(long)"), CT::Lexer::make_token("Long"));
	registerToken(compiler.compile("(register)"), CT::Lexer::make_token("Register"));
	registerToken(compiler.compile("(restrict)"), CT::Lexer::make_token("Restrict"));
	registerToken(compiler.compile("(return)"), CT::Lexer::make_token("Return"));
	registerToken(compiler.compile("(short)"), CT::Lexer::make_token("Short"));
	registerToken(compiler.compile("(signed)"), CT::Lexer::make_token("Signed"));
	registerToken(compiler.compile("(sizeof)"), CT::Lexer::make_token("Sizeof"));
	registerToken(compiler.compile("(static)"), CT::Lexer::make_token("Static"));
	registerToken(compiler.compile("(struct)"), CT::Lexer::make_token("Struct"));
	registerToken(compiler.compile("(switch)"), CT::Lexer::make_token("Switch"));
	registerToken(compiler.compile("(typedef)"), CT::Lexer::make_token("Typedef"));
	registerToken(compiler.compile("(union)"), CT::Lexer::make_token("Union"));
	registerToken(compiler.compile("(unsigned)"), CT::Lexer::make_token("Unsigned"));
	registerToken(compiler.compile("(void)"), CT::Lexer::make_token("Void"));
	registerToken(compiler.compile("(volatile)"), CT::Lexer::make_token("Volatile"));
	registerToken(compiler.compile("(while)"), CT::Lexer::make_token("While"));
	registerToken(compiler.compile("(_Alignas)"), CT::Lexer::make_token("Alignas"));
	registerToken(compiler.compile("(_Alignof)"), CT::Lexer::make_token("Alignof"));
	registerToken(compiler.compile("(_Atomic)"), CT::Lexer::make_token("Atomic"));
	registerToken(compiler.compile("(_Bool)"), CT::Lexer::make_token("Bool"));
	registerToken(compiler.compile("(_Complex)"), CT::Lexer::make_token("Complex"));
	registerToken(compiler.compile("(_Generic)"), CT::Lexer::make_token("Generic"));
	registerToken(compiler.compile("(_Imaginary)"), CT::Lexer::make_token("Imaginary"));
	registerToken(compiler.compile("(_Noreturn)"), CT::Lexer::make_token("Noreturn"));
	registerToken(compiler.compile("(_Static_assert)"), CT::Lexer::make_token("StaticAssert"));
	registerToken(compiler.compile("(_Thread_local)"), CT::Lexer::make_token("ThreadLocal"));
	registerToken(compiler.compile("(__extension__)"), CT::Lexer::make_token("Extension"));
	registerToken(compiler.compile("(__builtin_va_arg)"), CT::Lexer::make_token("BuiltInVaArg"));
	registerToken(compiler.compile("(__builtin_offsetof)"), CT::Lexer::make_token("BuiltInOffsetOf"));
	registerToken(compiler.compile("(__m128)"), CT::Lexer::make_token("SIMDNoType"));
	registerToken(compiler.compile("(__m128d)"), CT::Lexer::make_token("SIMDDType"));
	registerToken(compiler.compile("(__m128i)"), CT::Lexer::make_token("SIMDIType"));
	registerToken(compiler.compile("(__typeof__)"), CT::Lexer::make_token("TypeOf"));
	registerToken(compiler.compile("(__stdcall)"), CT::Lexer::make_token("StdCall"));
	registerToken(compiler.compile("(__declspec)"), CT::Lexer::make_token("DeclSpec"));
	registerToken(compiler.compile("(__asm)"), CT::Lexer::make_token("Asm"));
	registerToken(compiler.compile("(__attribute__)"), CT::Lexer::make_token("Attribute"));
	registerToken(compiler.compile("(//)"), CT::Lexer::make_token([](CT::InputStreamPtr ct_input, Token& ct_token) -> bool
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
	registerToken(compiler.compile("(/\\*)"), CT::Lexer::make_token([](CT::InputStreamPtr ct_input, Token& ct_token) -> bool
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
	registerToken(compiler.compile("(\\()"), CT::Lexer::make_token("LeftParen"));
	registerToken(compiler.compile("(\\))"), CT::Lexer::make_token("RightParen"));
	registerToken(compiler.compile("(\\[)"), CT::Lexer::make_token("LeftBracket"));
	registerToken(compiler.compile("(\\])"), CT::Lexer::make_token("RightBracket"));
	registerToken(compiler.compile("({)"), CT::Lexer::make_token("LeftBrace"));
	registerToken(compiler.compile("(})"), CT::Lexer::make_token("RightBrace"));
	registerToken(compiler.compile("(<<)"), CT::Lexer::make_token("LeftShift"));
	registerToken(compiler.compile("(>>)"), CT::Lexer::make_token("RightShift"));
	registerToken(compiler.compile("(<=)"), CT::Lexer::make_token("LessEqual"));
	registerToken(compiler.compile("(>=)"), CT::Lexer::make_token("GreaterEqual"));
	registerToken(compiler.compile("(\\*=)"), CT::Lexer::make_token("StarAssign"));
	registerToken(compiler.compile("(/=)"), CT::Lexer::make_token("DivAssign"));
	registerToken(compiler.compile("(%=)"), CT::Lexer::make_token("ModAssign"));
	registerToken(compiler.compile("(\\+=)"), CT::Lexer::make_token("PlusAssign"));
	registerToken(compiler.compile("(-=)"), CT::Lexer::make_token("MinusAssign"));
	registerToken(compiler.compile("(<<=)"), CT::Lexer::make_token("LeftShiftAssign"));
	registerToken(compiler.compile("(>>=)"), CT::Lexer::make_token("RightShiftAssign"));
	registerToken(compiler.compile("(&=)"), CT::Lexer::make_token("AndAssign"));
	registerToken(compiler.compile("(^=)"), CT::Lexer::make_token("XorAssign"));
	registerToken(compiler.compile("(\\|=)"), CT::Lexer::make_token("OrAssign"));
	registerToken(compiler.compile("(==)"), CT::Lexer::make_token("Equal"));
	registerToken(compiler.compile("(!=)"), CT::Lexer::make_token("NotEqual"));
	registerToken(compiler.compile("(=)"), CT::Lexer::make_token("Assign"));
	registerToken(compiler.compile("(\\+\\+)"), CT::Lexer::make_token("PlusPlus"));
	registerToken(compiler.compile("(->)"), CT::Lexer::make_token("Arrow"));
	registerToken(compiler.compile("(\\.\\.\\.)"), CT::Lexer::make_token("Ellipsis"));
	registerToken(compiler.compile("(--)"), CT::Lexer::make_token("MinusMinus"));
	registerToken(compiler.compile("(&&)"), CT::Lexer::make_token("AndAnd"));
	registerToken(compiler.compile("(\\|\\|)"), CT::Lexer::make_token("OrOr"));
	registerToken(compiler.compile("(^)"), CT::Lexer::make_token("Caret"));
	registerToken(compiler.compile("(!)"), CT::Lexer::make_token("Not"));
	registerToken(compiler.compile("(~)"), CT::Lexer::make_token("Tilde"));
	registerToken(compiler.compile("(>)"), CT::Lexer::make_token("Greater"));
	registerToken(compiler.compile("(<)"), CT::Lexer::make_token("Less"));
	registerToken(compiler.compile("(&)"), CT::Lexer::make_token("And"));
	registerToken(compiler.compile("(\\|)"), CT::Lexer::make_token("Or"));
	registerToken(compiler.compile("(-)"), CT::Lexer::make_token("Minus"));
	registerToken(compiler.compile("(\\*)"), CT::Lexer::make_token("Star"));
	registerToken(compiler.compile("(/)"), CT::Lexer::make_token("Div"));
	registerToken(compiler.compile("(%)"), CT::Lexer::make_token("Mod"));
	registerToken(compiler.compile("(\\+)"), CT::Lexer::make_token("Plus"));
	registerToken(compiler.compile("(\\.)"), CT::Lexer::make_token("Dot"));
	registerToken(compiler.compile("(\\?)"), CT::Lexer::make_token("Question"));
	registerToken(compiler.compile("(:)"), CT::Lexer::make_token("Colon"));
	registerToken(compiler.compile("(;)"), CT::Lexer::make_token("Semi"));
	registerToken(compiler.compile("(,)"), CT::Lexer::make_token("Comma"));
	registerToken(compiler.compile("(#)"), CT::Lexer::make_token("Hash"));
	registerToken(compiler.compile("(pragma)"), CT::Lexer::make_token("Pragma"));
	registerToken(compiler.compile("(include)"), CT::Lexer::make_token("Include"));
	registerToken(compiler.compile("(define)"), CT::Lexer::make_token("Define"));
	registerToken(compiler.compile("((([a-zA-Z_])|((\\\\u(([0-9a-fA-F])([0-9a-fA-F])([0-9a-fA-F])([0-9a-fA-F])))|(\\\\U(([0-9a-fA-F])([0-9a-fA-F])([0-9a-fA-F])([0-9a-fA-F])))))((([a-zA-Z_])|((\\\\u(([0-9a-fA-F])([0-9a-fA-F])([0-9a-fA-F])([0-9a-fA-F])))|(\\\\U(([0-9a-fA-F])([0-9a-fA-F])([0-9a-fA-F])([0-9a-fA-F])))))|([0-9]))*)"), CT::Lexer::make_token("Identifier"));
	registerToken(compiler.compile("(((((([1-9])([0-9])*)((((u|U))((l|L))?)|(((u|U))((ll|LL)))|(((l|L))((u|U))?)|(((ll|LL))((u|U))?))?)|((0([0-7])*)((((u|U))((l|L))?)|(((u|U))((ll|LL)))|(((l|L))((u|U))?)|(((ll|LL))((u|U))?))?)|(((0(x|X))([0-9a-fA-F])+)((((u|U))((l|L))?)|(((u|U))((ll|LL)))|(((l|L))((u|U))?)|(((ll|LL))((u|U))?))?)|(0(b|B)(0|1)+))|((((((([0-9])+)?.(([0-9])+))|((([0-9])+).))((e((\\+ | \\-))?(([0-9])+))|(E((\\+ | \\-))?(([0-9])+)))?((f|l|F|L))?)|((([0-9])+)((e((\\+ | \\-))?(([0-9])+))|(E((\\+ | \\-))?(([0-9])+)))((f|l|F|L))?))|(((0(x|X))(((([0-9a-fA-F])+)?.(([0-9a-fA-F])+))|((([0-9a-fA-F])+).))(((p|P)((\\+ | \\-))?(([0-9])+)))((f|l|F|L))?)|((0(x|X))(([0-9a-fA-F])+)(((p|P)((\\+ | \\-))?(([0-9])+)))((f|l|F|L))?)))))"), CT::Lexer::make_token("Constant"));
	registerToken(compiler.compile("((u8|[uUL])?\")"), CT::Lexer::make_token("StringConstant", [](CT::InputStreamPtr ct_input, Token& ct_token) -> bool
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
	registerToken(compiler.compile("(')"), CT::Lexer::make_token("CharConstant", [](CT::InputStreamPtr ct_input, Token& ct_token) -> bool
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