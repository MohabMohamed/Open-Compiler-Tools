#include "Chalcedony/Lexer/GLexer.h"
#include "Chalcedony/Automata/RegexBuilder.h"
#include "Chalcedony/InputStream.h"
#include "Chalcedony/Utilities.h"
#include "Chalcedony/Lexer/Token.h"
using namespace std;
using namespace CT;
using namespace CT::Lexer;

void GLexer::init()
{
	CT::RegexBuilder builder;
	registerToken(builder.create(";"), make_token("semicolon"));
	registerToken(builder.create("#name"), make_token("name_directive", [](CT::InputStreamPtr input, Token& token) -> bool {
		//token.literal = "";
		input->pushMarker();
		char pc = input->peek();
		while (pc != '\n' && pc != ';')
		{
			input->popLetter();
			pc = input->peek();
		}

		token.literal = input->popMarker();
		//trim(token.literal);
		return true;
	}));

	auto code_segment_action = [](CT::InputStreamPtr input, Token& token) -> bool {

	};

	registerToken(builder.create("#header"), make_token("header_code", [](CT::InputStreamPtr input, Token& token) -> bool {
		//token.literal = "";
		int i = 0;
		while (true)
		{
			auto c = input->popLetter();
			if (c == '{')
			{
				i++;
				break;
			}
		}

		input->pushMarker();
		while (true)
		{
			auto c = input->popLetter();
			if (c == '{')
			{
				i++;
			}
			else if (c == '}')
			{
				i--;
			}
			//else {
			//	token.literal += c;
			//}

			if (i == 0) {
				//back this last }
				input->rewindLetter();
				//pop the literal
				token.literal = input->popMarker();
				//consume the } back
				input->popLetter();
				break;
			}
		}
		return true;
	}));

	registerToken(builder.create("#cpp"), make_token("cpp_code", [](CT::InputStreamPtr input, Token& token) -> bool {
		//token.literal = "";
		int i = 0;
		while (true)
		{
			auto c = input->popLetter();
			if (c == '{')
			{
				i++;
				break;
			}
		}

		input->pushMarker();
		while (true)
		{
			auto c = input->popLetter();
			if (c == '{')
			{
				i++;
			}
			else if (c == '}')
			{
				i--;
			}
			/*else {
				token.literal += c;
			}*/

			if (i == 0)
			{
				//back this last }
				input->rewindLetter();
				//pop the literal
				token.literal = input->popMarker();
				//consume the } back
				input->popLetter();
				break;
			}
		}
		return true;
	}));

	registerToken(builder.create("(A-Z)(A-Z|_|a-z)+"), make_token("lex_id"));
	registerToken(builder.create(":="), make_token("assign"));

	registerToken(builder.create("\""), make_token("regex", [](CT::InputStreamPtr input, Token& token) -> bool {
		//token.literal = "";
		input->pushMarker();
		char prev = '\0';
		while (true) {
			char c = input->peek();
			//if (c == '"' && prev == '\\')
			//	token.literal += c;
			if (c == '"')
				break;

			//token.literal += c;

			prev = input->popLetter();
		}
		token.literal = input->popMarker();
		//pop last quote
		input->popLetter();
		return true;
	}));

	registerToken(builder.create("->"), make_token("action", [](CT::InputStreamPtr input, Token& token) -> bool {
		while (true)
		{
			auto c = input->popLetter();
			if (c == '{') {
				input->rewindLetter();
				break;
			}
			if (input->eof())
			{
				CT::Log::log(CT::LOG_LEVEL::ERROR, "error expected to find an action but found none", input->getPosition());
				return false;
			}
		}
		token.literal = CT::StringMarker::invalid;
		input->pushMarker();
		//pop the first {
		input->popLetter();
		int counter = 1;
		while (counter != 0)
		{
			char c = input->peek();
			if (c == '{')
				counter++;
			else if (c == '}')
				counter--;

			//token.literal += c;
			input->popLetter();
		}
		token.literal = input->popMarker();
		return true;
	}));

	registerToken(builder.create("(a-z)(a-z|_|A-Z)+"), make_token("parse_id"));
	registerToken(builder.create("\\|"), make_token("or"));
	registerToken(builder.create("&&"), make_token("and"));
	registerToken(builder.create("_start_"), make_token("start_rule"));
	registerToken(builder.create("(_|a-z|A-Z)(_|a-z|A-Z|0-9)*"), make_token("c_id"));
}

GLexer::GLexer()
{
	init();
}

CT::Lexer::GLexer::~GLexer()
{
}
