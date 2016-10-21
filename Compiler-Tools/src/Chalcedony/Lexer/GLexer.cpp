#include "Chalcedony/Lexer/GLexer.h"
#include "Chalcedony/Regex/Program.h"
#include "Chalcedony/Regex/Compiler.h"
#include "Chalcedony/InputStream.h"
#include "Chalcedony/Utilities.h"
#include "Chalcedony/Lexer/Token.h"
using namespace std;
using namespace CT;
using namespace CT::Lexer;

void GLexer::init()
{
	CT::Regex::Compiler compiler;
	registerToken(compiler.compile("\n"), Token::skip);
	registerToken(compiler.compile("\r"), Token::skip);
	registerToken(compiler.compile("\v"), Token::skip);
	registerToken(compiler.compile(" "), Token::skip);
	registerToken(compiler.compile("\t"), Token::skip);
	registerToken(compiler.compile("\f"), Token::skip);
	registerToken(compiler.compile(";"), make_token("semicolon"));
	registerToken(compiler.compile("skip"), make_token("skip"));
	registerToken(compiler.compile("ct_start"), make_token("start_rule"));
	registerToken(compiler.compile("ct_any"), make_token("any_token"));
	registerToken(compiler.compile("\\?"), make_token("regex_op"));
	registerToken(compiler.compile("\\|"), make_token("regex_op"));
	registerToken(compiler.compile("\\+"), make_token("regex_op"));
	registerToken(compiler.compile("\\["), make_token("regex_op"));
	registerToken(compiler.compile("\\]"), make_token("regex_op"));
	registerToken(compiler.compile("\\("), make_token("regex_op"));
	registerToken(compiler.compile("\\)"), make_token("regex_op"));
	registerToken(compiler.compile("\\*"), make_token("regex_op"));
	registerToken(compiler.compile("#name"), make_token("name_directive", [](CT::InputStreamPtr input, Token& token) -> bool {
		//token.literal = "";
		//filter whitespace
		auto whitespace = input->peek();
		while (whitespace == ' ' || whitespace == '\n' || whitespace == '\r' || whitespace == '\v' || whitespace == '\t')
		{
			input->popLetter();
			whitespace = input->peek();
		}
		input->pushMarker();
		char pc = input->peek();
		while (pc != '\n' && pc != ';')
		{
			if (pc == ' ' || pc == '\t' || pc == '\v' || pc == '\f')
			{
				CT::Log::log(CT::LOG_LEVEL::ERROR, "name directive can't contian spaces", input->getPosition());
				return false;
			}
			input->popLetter();
			pc = input->peek();
		}

		token.literal = input->popMarker();
		//trim(token.literal);
		return true;
	}));

	auto code_segment_action = [](CT::InputStreamPtr input, Token& token) -> bool {

	};

	registerToken(compiler.compile("#header"), make_token("header_code", [](CT::InputStreamPtr input, Token& token) -> bool {
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

	registerToken(compiler.compile("#cpp"), make_token("cpp_code", [](CT::InputStreamPtr input, Token& token) -> bool {
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

	registerToken(compiler.compile("[A-Z][A-Z_a-z]*"), make_token("lex_id"));
	registerToken(compiler.compile(":="), make_token("assign"));

	registerToken(compiler.compile("\""), make_token("regex", [](CT::InputStreamPtr input, Token& token) -> bool {
		//token.literal = "";
		input->pushMarker();
		char prev = '\0';
		while (true) {
			char c = input->peek();
			if (c == '"' && prev != '\\')
				break;

			prev = input->popLetter();
		}
		token.literal = input->popMarker();
		//pop last quote
		input->popLetter();
		return true;
	}));

	registerToken(compiler.compile("->"), make_token("action", [](CT::InputStreamPtr input, Token& token) -> bool {
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

	registerToken(compiler.compile("[a-z][a-z_A-Z]*"), make_token("parse_id"));
	registerToken(compiler.compile("\\|"), make_token("or"));
	registerToken(compiler.compile("&&"), make_token("and"));
	registerToken(compiler.compile("[_a-zA-Z][_a-zA-Z0-9]*"), make_token("c_id"));
}

GLexer::GLexer()
{
	init();
}

CT::Lexer::GLexer::~GLexer()
{
}
