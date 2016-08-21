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

				registerToken(builder.create("include"), make_token("include"));
				registerToken(builder.create("namespace"), make_token("namespace"));
				registerToken(builder.create("class"), make_token("class"));
				registerToken(builder.create("struct"), make_token("struct"));
				//types
				registerToken(builder.create("void"), make_token("void"));
				registerToken(builder.create("int"), make_token("int"));
				registerToken(builder.create("float"), make_token("float"));
				registerToken(builder.create("double"), make_token("double"));
				registerToken(builder.create("char"), make_token("char"));
				//access modifiers
				registerToken(builder.create("public"), make_token("public"));
				registerToken(builder.create("protected"), make_token("protected"));
				registerToken(builder.create("private"), make_token("private"));
				registerToken(builder.create("const"), make_token("const"));
				registerToken(builder.create("override"), make_token("override"));
				registerToken(builder.create("virtual"), make_token("virtual"));

				registerToken(builder.create("(0-9)*.(0-9)+f"), make_token("float"));
				registerToken(builder.create("(0-9)*.(0-9)+"), make_token("real"));
				registerToken(builder.create("(0-9)+L"), make_token("long"));
				registerToken(builder.create("(0-9)+"), make_token("integer"));
				registerToken(builder.create("(a-z|_)(a-z|_|0-9)*"), make_token("id"));

				//operators
				registerToken(builder.create("<="), make_token("less_equal"));
				registerToken(builder.create(">="), make_token("greater_equal"));
				registerToken(builder.create("<<"), make_token("shift_left"));
				registerToken(builder.create(">>"), make_token("shift_right"));
				registerToken(builder.create("<"), make_token("less"));
				registerToken(builder.create(">"), make_token("greater"));
				registerToken(builder.create("=="), make_token("equal"));
				registerToken(builder.create("!="), make_token("not_equal"));
				registerToken(builder.create("!"), make_token("not"));
				registerToken(builder.create("\\+="), make_token("plus_equal"));
				registerToken(builder.create("\\*="), make_token("multiply_equal"));
				registerToken(builder.create("/="), make_token("devide_equal"));
				registerToken(builder.create("%="), make_token("mod_equal"));
				registerToken(builder.create("-="), make_token("minus_equal"));
				registerToken(builder.create("->"), make_token("arrow"));
				registerToken(builder.create("-"), make_token("minus"));
				registerToken(builder.create("\\+"), make_token("plus"));
				registerToken(builder.create("/"), make_token("devide"));
				registerToken(builder.create("\\*"), make_token("multiply"));
				registerToken(builder.create("%"), make_token("mod"));
				registerToken(builder.create("\\|\\|"), make_token("or"));
				registerToken(builder.create("&&"), make_token("and"));
				registerToken(builder.create("\\|="), make_token("logic_or_equal"));
				registerToken(builder.create("^="), make_token("xor_equal"));
				registerToken(builder.create("~="), make_token("logic_not_equal"));
				registerToken(builder.create("&="), make_token("logic_and_equal"));

				registerToken(builder.create("\\|"), make_token("logic_or"));
				registerToken(builder.create("&"), make_token("logic_and"));
				registerToken(builder.create("~"), make_token("logic_not"));
				registerToken(builder.create("^"), make_token("xor"));
				registerToken(builder.create("="), make_token("assign"));
				
				registerToken(builder.create(";"), make_token("semicolon"));
				registerToken(builder.create("::"), make_token("access"));
				registerToken(builder.create(":"), make_token("colon"));
				registerToken(builder.create(","), make_token("comma"));
				registerToken(builder.create("."), make_token("dot"));
				registerToken(builder.create("\\("), make_token("open_paren"));
				registerToken(builder.create("\\)"), make_token("close_paren"));
				registerToken(builder.create("{"), make_token("open_bracket"));
				registerToken(builder.create("}"), make_token("close_bracket"));
				registerToken(builder.create("["), make_token("open_sbracket"));
				registerToken(builder.create("]"), make_token("close_sbracket"));
			}
		public:
			CPPScanner()
			{
				init();				
			}
		};
	}
}