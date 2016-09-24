#pragma once
#include "Chalcedony/Defines.h"
#include "Chalcedony/Lexer/Token.h"
#include "Chalcedony/InputStream.h"
#include "Chalcedony/Automata/RegexBuilder.h"
#include "Chalcedony/Lexer/Scanner.h"

namespace CT
{
	namespace Lexer
	{
		class CPPScanner: public Scanner
		{
		protected:
			void init()
			{
				//CT::RegexBuilder builder;

				//registerToken(builder.create("auto"), TokenManager<TOKEN_SPACE::USER>::make_token("auto"));
				//registerToken(builder.create("break"), TokenManager<TOKEN_SPACE::USER>::make_token("break"));
				//registerToken(builder.create("case"), TokenManager<TOKEN_SPACE::USER>::make_token("case"));
				//registerToken(builder.create("char"), TokenManager<TOKEN_SPACE::USER>::make_token("char"));
				//registerToken(builder.create("const"), TokenManager<TOKEN_SPACE::USER>::make_token("const"));
				//registerToken(builder.create("continue"), TokenManager<TOKEN_SPACE::USER>::make_token("continue"));
				//registerToken(builder.create("default"), TokenManager<TOKEN_SPACE::USER>::make_token("default"));
				//registerToken(builder.create("using"), TokenManager<TOKEN_SPACE::USER>::make_token("using"));
				//registerToken(builder.create("namespace"), TokenManager<TOKEN_SPACE::USER>::make_token("namespace"));
				//registerToken(builder.create("double"), TokenManager<TOKEN_SPACE::USER>::make_token("double"));
				//registerToken(builder.create("do"), TokenManager<TOKEN_SPACE::USER>::make_token("do"));
				//registerToken(builder.create("else"), TokenManager<TOKEN_SPACE::USER>::make_token("else"));
				//registerToken(builder.create("enum"), TokenManager<TOKEN_SPACE::USER>::make_token("enum"));
				//registerToken(builder.create("extern"), TokenManager<TOKEN_SPACE::USER>::make_token("extern"));
				//registerToken(builder.create("float"), TokenManager<TOKEN_SPACE::USER>::make_token("float"));
				//registerToken(builder.create("for"), TokenManager<TOKEN_SPACE::USER>::make_token("for"));
				//registerToken(builder.create("goto"), TokenManager<TOKEN_SPACE::USER>::make_token("goto"));
				//registerToken(builder.create("if"), TokenManager<TOKEN_SPACE::USER>::make_token("if"));
				//registerToken(builder.create("include"), TokenManager<TOKEN_SPACE::USER>::make_token("include"));
				//registerToken(builder.create("inline"), TokenManager<TOKEN_SPACE::USER>::make_token("inline"));
				//registerToken(builder.create("int"), TokenManager<TOKEN_SPACE::USER>::make_token("int"));
				//registerToken(builder.create("long"), TokenManager<TOKEN_SPACE::USER>::make_token("long"));
				//registerToken(builder.create("register"), TokenManager<TOKEN_SPACE::USER>::make_token("register"));
				//registerToken(builder.create("restrict"), TokenManager<TOKEN_SPACE::USER>::make_token("restrict"));
				//registerToken(builder.create("return"), TokenManager<TOKEN_SPACE::USER>::make_token("return"));
				//registerToken(builder.create("short"), TokenManager<TOKEN_SPACE::USER>::make_token("short"));
				//registerToken(builder.create("signed"), TokenManager<TOKEN_SPACE::USER>::make_token("signed"));
				//registerToken(builder.create("sizeof"), TokenManager<TOKEN_SPACE::USER>::make_token("sizeof"));
				//registerToken(builder.create("static"), TokenManager<TOKEN_SPACE::USER>::make_token("static"));
				//registerToken(builder.create("struct"), TokenManager<TOKEN_SPACE::USER>::make_token("struct"));
				//registerToken(builder.create("class"), TokenManager<TOKEN_SPACE::USER>::make_token("class"));
				//registerToken(builder.create("switch"), TokenManager<TOKEN_SPACE::USER>::make_token("switch"));
				//registerToken(builder.create("typedef"), TokenManager<TOKEN_SPACE::USER>::make_token("typedef"));
				//registerToken(builder.create("union"), TokenManager<TOKEN_SPACE::USER>::make_token("union"));
				//registerToken(builder.create("unsigned"), TokenManager<TOKEN_SPACE::USER>::make_token("unsigned"));
				//registerToken(builder.create("void"), TokenManager<TOKEN_SPACE::USER>::make_token("void"));
				//registerToken(builder.create("volatile"), TokenManager<TOKEN_SPACE::USER>::make_token("volatile"));
				//registerToken(builder.create("while"), TokenManager<TOKEN_SPACE::USER>::make_token("while"));
				//registerToken(builder.create("_Alignas"), TokenManager<TOKEN_SPACE::USER>::make_token("_Alignas"));
				//registerToken(builder.create("_Alignof"), TokenManager<TOKEN_SPACE::USER>::make_token("_Alignof"));
				//registerToken(builder.create("_Atomic"), TokenManager<TOKEN_SPACE::USER>::make_token("_Atomic"));
				//registerToken(builder.create("_Bool"), TokenManager<TOKEN_SPACE::USER>::make_token("_Bool"));
				//registerToken(builder.create("_Complex"), TokenManager<TOKEN_SPACE::USER>::make_token("_Complex"));
				//registerToken(builder.create("_Generic"), TokenManager<TOKEN_SPACE::USER>::make_token("_Generic"));
				//registerToken(builder.create("_Imaginary"), TokenManager<TOKEN_SPACE::USER>::make_token("_Imaginary"));
				//registerToken(builder.create("_Noreturn"), TokenManager<TOKEN_SPACE::USER>::make_token("_Noreturn"));
				//registerToken(builder.create("_Static_assert"), TokenManager<TOKEN_SPACE::USER>::make_token("_Static_assert"));
				//registerToken(builder.create("_Thread_local"), TokenManager<TOKEN_SPACE::USER>::make_token("_Thread_local"));
				//registerToken(builder.create("__func__"), TokenManager<TOKEN_SPACE::USER>::make_token("__func__"));
				//registerToken(builder.create("#"), TokenManager<TOKEN_SPACE::USER>::make_token("HASH"));

				//registerToken(builder.create("'"), TokenManager<TOKEN_SPACE::USER>::make_token("char_literal", [](CT::InputStreamPtr input, CT::Lexer::Token& token) -> bool {
				//	token.literal = "";
				//	bool ignore = false;
				//	auto char_c = input->popLetter();
				//	auto end_quote = input->popLetter();

				//	if (end_quote == '\'')
				//	{
				//		token.literal += char_c;
				//	}
				//	else if (char_c == '\\')
				//	{
				//		auto new_end_quote = input->popLetter();
				//		token.literal += char_c;
				//		token.literal += end_quote;
				//	}
				//	else {
				//		if (char_c != '\0')
				//			input->rewindLetter();
				//		if (end_quote != '\0')
				//			input->rewindLetter();
				//	}
				//	return true;
				//}));
				//registerToken(builder.create("'"), TokenManager<TOKEN_SPACE::USER>::make_token("SINGLE_QUOTE"));

				//registerToken(builder.create("\""), TokenManager<TOKEN_SPACE::USER>::make_token("string_literal", [](CT::InputStreamPtr input, CT::Lexer::Token& token) -> bool {
				//	token.literal = "";
				//	bool ignore = false;
				//	while (true)
				//	{
				//		if (input->peek() == '\\')
				//		{
				//			ignore = true;
				//			//consume the ignore char
				//			input->popLetter();
				//		}

				//		if (input->peek() == '"')
				//		{
				//			if (!ignore)
				//			{
				//				//on the way out remove the closing "
				//				input->popLetter();
				//				break;
				//			}
				//		}

				//		if (ignore)
				//			ignore = false;

				//		token.literal += input->popLetter();
				//	}
				//	return true;
				//}));

				//registerToken(builder.create("//"), TokenManager<TOKEN_SPACE::USER>::make_token("singleline_comment", [](CT::InputStreamPtr input, CT::Lexer::Token& token) -> bool {
				//	token.literal = "";
				//	while (input->peek() != '\n')
				//	{
				//		token.literal += input->popLetter();
				//	}
				//	return true;
				//}));

				//registerToken(builder.create("/\\*"), TokenManager<TOKEN_SPACE::USER>::make_token("multiline_comment", [](CT::InputStreamPtr input, CT::Lexer::Token& token) -> bool {
				//	token.literal = "";
				//	while (true)
				//	{
				//		auto mul = input->popLetter();
				//		auto slash = input->popLetter();
				//		if (mul == '*' && slash == '/')
				//		{
				//			break;
				//		}
				//		else
				//		{
				//			if (mul != '\0')
				//				input->rewindLetter();
				//			if (slash != '\0')
				//				input->rewindLetter();
				//		}

				//		token.literal += input->popLetter();
				//	}
				//	return true;
				//}));

				//registerToken(builder.create("\""), TokenManager<TOKEN_SPACE::USER>::make_token("DOUBLE_QUOTE"));


				//registerToken(builder.create("(_|a-z|A-Z)(_|a-z|A-Z|0-9)*"), TokenManager<TOKEN_SPACE::USER>::make_token("identifier"));

				//registerToken(builder.create("(0(x|X))?(0-9|A-F|a-f)+(((u|U)(l|L|ll|LL)?)|((l|L|ll|LL)(u|U)?))?"), TokenManager<TOKEN_SPACE::USER>::make_token("integer_constant"));
				//registerToken(builder.create("(1-9)(0-9)*(((u|U)(l|L|ll|LL)?)|((l|L|ll|LL)(u|U)?))?"), TokenManager<TOKEN_SPACE::USER>::make_token("integer_constant"));
				//registerToken(builder.create("0(0-7)*(((u|U)(l|L|ll|LL)?)|((l|L|ll|LL)(u|U)?))?"), TokenManager<TOKEN_SPACE::USER>::make_token("integer_constant"));

				//registerToken(builder.create("(0-9)+((E|e)(\\+|\\-)?(0-9)+)(f|F|l|L)?"), TokenManager<TOKEN_SPACE::USER>::make_token("float_constant"));
				//registerToken(builder.create("(0-9)*.(0-9)+((E|e)(\\+|\\-)?(0-9)+)?(f|F|l|L)?"), TokenManager<TOKEN_SPACE::USER>::make_token("float_constant"));
				//registerToken(builder.create("(0-9)+.((E|e)(\\+|\\-)?(0-9)+)?(f|F|l|L)?"), TokenManager<TOKEN_SPACE::USER>::make_token("float_constant"));
				//registerToken(builder.create("(0(x|X))(0-9|A-F|a-f)+((P|p)(\\+|\\-)?(0-9)+)(f|F|l|L)?"), TokenManager<TOKEN_SPACE::USER>::make_token("float_constant"));
				//registerToken(builder.create("(0(x|X))(0-9|A-F|a-f)*.(0-9|A-F|a-f)+((P|p)(\\+|\\-)?(0-9)+)(f|F|l|L)?"), TokenManager<TOKEN_SPACE::USER>::make_token("float_constant"));
				//registerToken(builder.create("(0(x|X))(0-9|A-F|a-f)*.((P|p)(\\+|\\-)?(0-9)+)(f|F|l|L)?"), TokenManager<TOKEN_SPACE::USER>::make_token("float_constant"));

				//registerToken(builder.create("..."), TokenManager<TOKEN_SPACE::USER>::make_token("ELLIPSIS"));
				//registerToken(builder.create(">>="), TokenManager<TOKEN_SPACE::USER>::make_token("RIGHT_SHIFT_ASSIGN"));
				//registerToken(builder.create("<<="), TokenManager<TOKEN_SPACE::USER>::make_token("LEFT_SHIFT_ASSIGN"));
				//registerToken(builder.create("\\+="), TokenManager<TOKEN_SPACE::USER>::make_token("ADD_ASSIGN"));
				//registerToken(builder.create("\\-="), TokenManager<TOKEN_SPACE::USER>::make_token("SUB_ASSIGN"));
				//registerToken(builder.create("\\*="), TokenManager<TOKEN_SPACE::USER>::make_token("MUL_ASSIGN"));
				//registerToken(builder.create("/="), TokenManager<TOKEN_SPACE::USER>::make_token("DIV_ASSIGN"));
				//registerToken(builder.create("%="), TokenManager<TOKEN_SPACE::USER>::make_token("MOD_ASSIGN"));
				//registerToken(builder.create("&="), TokenManager<TOKEN_SPACE::USER>::make_token("AND_ASSIGN"));
				//registerToken(builder.create("^="), TokenManager<TOKEN_SPACE::USER>::make_token("XOR_ASSIGN"));
				//registerToken(builder.create("\\|="), TokenManager<TOKEN_SPACE::USER>::make_token("OR_ASSIGN"));
				//registerToken(builder.create(">>"), TokenManager<TOKEN_SPACE::USER>::make_token("RIGHT_SHIFT"));
				//registerToken(builder.create("<<"), TokenManager<TOKEN_SPACE::USER>::make_token("LEFT_SHIFT"));
				//registerToken(builder.create("\\+\\+"), TokenManager<TOKEN_SPACE::USER>::make_token("INC"));
				//registerToken(builder.create("\\-\\-"), TokenManager<TOKEN_SPACE::USER>::make_token("DEC"));
				//registerToken(builder.create("\\->"), TokenManager<TOKEN_SPACE::USER>::make_token("PTR_ARROW"));
				//registerToken(builder.create("&&"), TokenManager<TOKEN_SPACE::USER>::make_token("AND"));
				//registerToken(builder.create("\\|\\|"), TokenManager<TOKEN_SPACE::USER>::make_token("OR"));
				//registerToken(builder.create("<="), TokenManager<TOKEN_SPACE::USER>::make_token("LESS_EQ"));
				//registerToken(builder.create(">="), TokenManager<TOKEN_SPACE::USER>::make_token("GREATER_EQ"));
				//registerToken(builder.create("=="), TokenManager<TOKEN_SPACE::USER>::make_token("EQUAL"));
				//registerToken(builder.create("!="), TokenManager<TOKEN_SPACE::USER>::make_token("NOT_EQUAL"));
				//registerToken(builder.create(";"), TokenManager<TOKEN_SPACE::USER>::make_token("SEMICOLON"));
				//registerToken(builder.create("{"), TokenManager<TOKEN_SPACE::USER>::make_token("OPEN_CURLY"));
				//registerToken(builder.create("}"), TokenManager<TOKEN_SPACE::USER>::make_token("CLOSE_CURLY"));
				//registerToken(builder.create(","), TokenManager<TOKEN_SPACE::USER>::make_token("COMMA"));
				//registerToken(builder.create(":"), TokenManager<TOKEN_SPACE::USER>::make_token("COLON"));
				//registerToken(builder.create("="), TokenManager<TOKEN_SPACE::USER>::make_token("ASSIGN"));
				//registerToken(builder.create("\\("), TokenManager<TOKEN_SPACE::USER>::make_token("OPEN_PAREN"));
				//registerToken(builder.create("\\)"), TokenManager<TOKEN_SPACE::USER>::make_token("CLOSE_PAREN"));
				//registerToken(builder.create("["), TokenManager<TOKEN_SPACE::USER>::make_token("OPEN_BRACKET"));
				//registerToken(builder.create("]"), TokenManager<TOKEN_SPACE::USER>::make_token("CLOSE_BRACKET"));
				//registerToken(builder.create("."), TokenManager<TOKEN_SPACE::USER>::make_token("DOT"));
				//registerToken(builder.create("&"), TokenManager<TOKEN_SPACE::USER>::make_token("AND_LOGIC"));
				//registerToken(builder.create("!"), TokenManager<TOKEN_SPACE::USER>::make_token("NOT"));
				//registerToken(builder.create("~"), TokenManager<TOKEN_SPACE::USER>::make_token("NOT_LOGIC"));
				//registerToken(builder.create("\\-"), TokenManager<TOKEN_SPACE::USER>::make_token("SUB"));
				//registerToken(builder.create("\\+"), TokenManager<TOKEN_SPACE::USER>::make_token("ADD"));
				//registerToken(builder.create("\\*"), TokenManager<TOKEN_SPACE::USER>::make_token("MUL"));
				//registerToken(builder.create("/"), TokenManager<TOKEN_SPACE::USER>::make_token("DIV"));
				//registerToken(builder.create("%"), TokenManager<TOKEN_SPACE::USER>::make_token("MOD"));
				//registerToken(builder.create("<"), TokenManager<TOKEN_SPACE::USER>::make_token("LESS"));
				//registerToken(builder.create(">"), TokenManager<TOKEN_SPACE::USER>::make_token("GREATER"));
				//registerToken(builder.create("^"), TokenManager<TOKEN_SPACE::USER>::make_token("XOR_LOGIC"));
				//registerToken(builder.create("\\|"), TokenManager<TOKEN_SPACE::USER>::make_token("OR_LOGIC"));
				//registerToken(builder.create("\\?"), TokenManager<TOKEN_SPACE::USER>::make_token("QUESTION"));
			}
		public:
			CPPScanner()
			{
				init();				
			}
		};
	}
}