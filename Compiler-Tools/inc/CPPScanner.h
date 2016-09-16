#pragma once
#include "Defines.h"
#include "Token.h"
#include "InputStream.h"
#include "RegexBuilder.h"
#include "Scanner.h"

namespace CT
{
	namespace Lexer
	{
		class CPPScanner: public Scanner
		{
		protected:
			void init()
			{
				CT::RegexBuilder builder;

				registerToken(builder.create("auto"), make_token_lib("auto"));
				registerToken(builder.create("break"), make_token_lib("break"));
				registerToken(builder.create("case"), make_token_lib("case"));
				registerToken(builder.create("char"), make_token_lib("char"));
				registerToken(builder.create("const"), make_token_lib("const"));
				registerToken(builder.create("continue"), make_token_lib("continue"));
				registerToken(builder.create("default"), make_token_lib("default"));
				registerToken(builder.create("using"), make_token_lib("using"));
				registerToken(builder.create("namespace"), make_token_lib("namespace"));
				registerToken(builder.create("double"), make_token_lib("double"));
				registerToken(builder.create("do"), make_token_lib("do"));
				registerToken(builder.create("else"), make_token_lib("else"));
				registerToken(builder.create("enum"), make_token_lib("enum"));
				registerToken(builder.create("extern"), make_token_lib("extern"));
				registerToken(builder.create("float"), make_token_lib("float"));
				registerToken(builder.create("for"), make_token_lib("for"));
				registerToken(builder.create("goto"), make_token_lib("goto"));
				registerToken(builder.create("if"), make_token_lib("if"));
				registerToken(builder.create("include"), make_token_lib("include"));
				registerToken(builder.create("inline"), make_token_lib("inline"));
				registerToken(builder.create("int"), make_token_lib("int"));
				registerToken(builder.create("long"), make_token_lib("long"));
				registerToken(builder.create("register"), make_token_lib("register"));
				registerToken(builder.create("restrict"), make_token_lib("restrict"));
				registerToken(builder.create("return"), make_token_lib("return"));
				registerToken(builder.create("short"), make_token_lib("short"));
				registerToken(builder.create("signed"), make_token_lib("signed"));
				registerToken(builder.create("sizeof"), make_token_lib("sizeof"));
				registerToken(builder.create("static"), make_token_lib("static"));
				registerToken(builder.create("struct"), make_token_lib("struct"));
				registerToken(builder.create("class"), make_token_lib("class"));
				registerToken(builder.create("switch"), make_token_lib("switch"));
				registerToken(builder.create("typedef"), make_token_lib("typedef"));
				registerToken(builder.create("union"), make_token_lib("union"));
				registerToken(builder.create("unsigned"), make_token_lib("unsigned"));
				registerToken(builder.create("void"), make_token_lib("void"));
				registerToken(builder.create("volatile"), make_token_lib("volatile"));
				registerToken(builder.create("while"), make_token_lib("while"));
				registerToken(builder.create("_Alignas"), make_token_lib("_Alignas"));
				registerToken(builder.create("_Alignof"), make_token_lib("_Alignof"));
				registerToken(builder.create("_Atomic"), make_token_lib("_Atomic"));
				registerToken(builder.create("_Bool"), make_token_lib("_Bool"));
				registerToken(builder.create("_Complex"), make_token_lib("_Complex"));
				registerToken(builder.create("_Generic"), make_token_lib("_Generic"));
				registerToken(builder.create("_Imaginary"), make_token_lib("_Imaginary"));
				registerToken(builder.create("_Noreturn"), make_token_lib("_Noreturn"));
				registerToken(builder.create("_Static_assert"), make_token_lib("_Static_assert"));
				registerToken(builder.create("_Thread_local"), make_token_lib("_Thread_local"));
				registerToken(builder.create("__func__"), make_token_lib("__func__"));
				registerToken(builder.create("#"), make_token_lib("HASH"));

				registerToken(builder.create("'"), make_token_lib("char_literal", [](CT::InputStreamPtr input, CT::Lexer::Token& token) -> bool {
					token.literal = "";
					bool ignore = false;
					auto char_c = input->popLetter();
					auto end_quote = input->popLetter();

					if (end_quote == '\'')
					{
						token.literal += char_c;
					}
					else if (char_c == '\\')
					{
						auto new_end_quote = input->popLetter();
						token.literal += char_c;
						token.literal += end_quote;
					}
					else {
						if (char_c != '\0')
							input->rewindLetter();
						if (end_quote != '\0')
							input->rewindLetter();
					}
					return true;
				}));
				registerToken(builder.create("'"), make_token_lib("SINGLE_QUOTE"));

				registerToken(builder.create("\""), make_token_lib("string_literal", [](CT::InputStreamPtr input, CT::Lexer::Token& token) -> bool {
					token.literal = "";
					bool ignore = false;
					while (true)
					{
						if (input->peek() == '\\')
						{
							ignore = true;
							//consume the ignore char
							input->popLetter();
						}

						if (input->peek() == '"')
						{
							if (!ignore)
							{
								//on the way out remove the closing "
								input->popLetter();
								break;
							}
						}

						if (ignore)
							ignore = false;

						token.literal += input->popLetter();
					}
					return true;
				}));

				registerToken(builder.create("//"), make_token_lib("singleline_comment", [](CT::InputStreamPtr input, CT::Lexer::Token& token) -> bool {
					token.literal = "";
					while (input->peek() != '\n')
					{
						token.literal += input->popLetter();
					}
					return true;
				}));

				registerToken(builder.create("/\\*"), make_token_lib("multiline_comment", [](CT::InputStreamPtr input, CT::Lexer::Token& token) -> bool {
					token.literal = "";
					while (true)
					{
						auto mul = input->popLetter();
						auto slash = input->popLetter();
						if (mul == '*' && slash == '/')
						{
							break;
						}
						else
						{
							if (mul != '\0')
								input->rewindLetter();
							if (slash != '\0')
								input->rewindLetter();
						}

						token.literal += input->popLetter();
					}
					return true;
				}));

				registerToken(builder.create("\""), make_token_lib("DOUBLE_QUOTE"));


				registerToken(builder.create("(_|a-z|A-Z)(_|a-z|A-Z|0-9)*"), make_token_lib("identifier"));

				registerToken(builder.create("(0(x|X))?(0-9|A-F|a-f)+(((u|U)(l|L|ll|LL)?)|((l|L|ll|LL)(u|U)?))?"), make_token_lib("integer_constant"));
				registerToken(builder.create("(1-9)(0-9)*(((u|U)(l|L|ll|LL)?)|((l|L|ll|LL)(u|U)?))?"), make_token_lib("integer_constant"));
				registerToken(builder.create("0(0-7)*(((u|U)(l|L|ll|LL)?)|((l|L|ll|LL)(u|U)?))?"), make_token_lib("integer_constant"));

				registerToken(builder.create("(0-9)+((E|e)(\\+|\\-)?(0-9)+)(f|F|l|L)?"), make_token_lib("float_constant"));
				registerToken(builder.create("(0-9)*.(0-9)+((E|e)(\\+|\\-)?(0-9)+)?(f|F|l|L)?"), make_token_lib("float_constant"));
				registerToken(builder.create("(0-9)+.((E|e)(\\+|\\-)?(0-9)+)?(f|F|l|L)?"), make_token_lib("float_constant"));
				registerToken(builder.create("(0(x|X))(0-9|A-F|a-f)+((P|p)(\\+|\\-)?(0-9)+)(f|F|l|L)?"), make_token_lib("float_constant"));
				registerToken(builder.create("(0(x|X))(0-9|A-F|a-f)*.(0-9|A-F|a-f)+((P|p)(\\+|\\-)?(0-9)+)(f|F|l|L)?"), make_token_lib("float_constant"));
				registerToken(builder.create("(0(x|X))(0-9|A-F|a-f)*.((P|p)(\\+|\\-)?(0-9)+)(f|F|l|L)?"), make_token_lib("float_constant"));

				registerToken(builder.create("..."), make_token_lib("ELLIPSIS"));
				registerToken(builder.create(">>="), make_token_lib("RIGHT_SHIFT_ASSIGN"));
				registerToken(builder.create("<<="), make_token_lib("LEFT_SHIFT_ASSIGN"));
				registerToken(builder.create("\\+="), make_token_lib("ADD_ASSIGN"));
				registerToken(builder.create("\\-="), make_token_lib("SUB_ASSIGN"));
				registerToken(builder.create("\\*="), make_token_lib("MUL_ASSIGN"));
				registerToken(builder.create("/="), make_token_lib("DIV_ASSIGN"));
				registerToken(builder.create("%="), make_token_lib("MOD_ASSIGN"));
				registerToken(builder.create("&="), make_token_lib("AND_ASSIGN"));
				registerToken(builder.create("^="), make_token_lib("XOR_ASSIGN"));
				registerToken(builder.create("\\|="), make_token_lib("OR_ASSIGN"));
				registerToken(builder.create(">>"), make_token_lib("RIGHT_SHIFT"));
				registerToken(builder.create("<<"), make_token_lib("LEFT_SHIFT"));
				registerToken(builder.create("\\+\\+"), make_token_lib("INC"));
				registerToken(builder.create("\\-\\-"), make_token_lib("DEC"));
				registerToken(builder.create("\\->"), make_token_lib("PTR_ARROW"));
				registerToken(builder.create("&&"), make_token_lib("AND"));
				registerToken(builder.create("\\|\\|"), make_token_lib("OR"));
				registerToken(builder.create("<="), make_token_lib("LESS_EQ"));
				registerToken(builder.create(">="), make_token_lib("GREATER_EQ"));
				registerToken(builder.create("=="), make_token_lib("EQUAL"));
				registerToken(builder.create("!="), make_token_lib("NOT_EQUAL"));
				registerToken(builder.create(";"), make_token_lib("SEMICOLON"));
				registerToken(builder.create("{"), make_token_lib("OPEN_CURLY"));
				registerToken(builder.create("}"), make_token_lib("CLOSE_CURLY"));
				registerToken(builder.create(","), make_token_lib("COMMA"));
				registerToken(builder.create(":"), make_token_lib("COLON"));
				registerToken(builder.create("="), make_token_lib("ASSIGN"));
				registerToken(builder.create("\\("), make_token_lib("OPEN_PAREN"));
				registerToken(builder.create("\\)"), make_token_lib("CLOSE_PAREN"));
				registerToken(builder.create("["), make_token_lib("OPEN_BRACKET"));
				registerToken(builder.create("]"), make_token_lib("CLOSE_BRACKET"));
				registerToken(builder.create("."), make_token_lib("DOT"));
				registerToken(builder.create("&"), make_token_lib("AND_LOGIC"));
				registerToken(builder.create("!"), make_token_lib("NOT"));
				registerToken(builder.create("~"), make_token_lib("NOT_LOGIC"));
				registerToken(builder.create("\\-"), make_token_lib("SUB"));
				registerToken(builder.create("\\+"), make_token_lib("ADD"));
				registerToken(builder.create("\\*"), make_token_lib("MUL"));
				registerToken(builder.create("/"), make_token_lib("DIV"));
				registerToken(builder.create("%"), make_token_lib("MOD"));
				registerToken(builder.create("<"), make_token_lib("LESS"));
				registerToken(builder.create(">"), make_token_lib("GREATER"));
				registerToken(builder.create("^"), make_token_lib("XOR_LOGIC"));
				registerToken(builder.create("\\|"), make_token_lib("OR_LOGIC"));
				registerToken(builder.create("\\?"), make_token_lib("QUESTION"));
			}
		public:
			CPPScanner()
			{
				init();				
			}
		};
	}
}