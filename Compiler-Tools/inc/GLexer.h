#pragma once

#include "Defines.h"
#include "Token.h"
#include "Scanner.h"
#include "RegexBuilder.h"
#include "InputStream.h"
#include "Utilities.h"
namespace CT
{
	namespace Lexer
	{
		class GLexer: public Scanner
		{
		protected:
			void init()
			{
				CT::RegexBuilder builder;

				registerToken(builder.create("#name"), make_token("name_directive", [](CT::InputStreamPtr input, Token& token) -> bool{
					token.literal = "";
					while (input->peek() != '\n')
					{
						token.literal += input->popLetter();
					}
					trim(token.literal);
					return true;
				}));

				registerToken(builder.create("(A-Z)+"), make_token("lex_id"));
				registerToken(builder.create(":="), make_token("assign"));

				registerToken(builder.create("\""), make_token("regex", [](CT::InputStreamPtr input, Token& token) -> bool {
					token.literal = "";
					char prev = '\0';
					while (true) {
						char c = input->peek();
						if (c == '"' && prev == '\\')
							token.literal += c;
						else if(c == '"')
							break;

						token.literal += c;

						prev = input->popLetter();
					}
					//pop last quote
					input->popLetter();
					return true;
				}));

				registerToken(builder.create("{"), make_token("action", [](CT::InputStreamPtr input, Token& token) -> bool {
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

				registerToken(builder.create("(a-z)+"), make_token("parse_id"));
				registerToken(builder.create(";"), make_token("semicolon"));
				registerToken(builder.create("\\|"), make_token("or"));
			}

		public:
			GLexer(){
				init();
			}
		};
	}
}