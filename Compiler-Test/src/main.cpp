#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <fstream>
#include <memory>
#include <regex>
#include <Chalcedony\Chalcedony.h>
#include <CLexer.h>
#include <CParser.h>

using namespace std;
class InputParser {
public:
	InputParser(int &argc, char **argv) {
		for (int i = 1; i < argc; ++i)
			this->tokens.push_back(std::string(argv[i]));
	}
	/// @author iain
	const std::string& getCmdOption(const std::string &option) const {
		std::vector<std::string>::const_iterator itr;
		itr = std::find(this->tokens.begin(), this->tokens.end(), option);
		if (itr != this->tokens.end() && ++itr != this->tokens.end()) {
			return *itr;
		}
		return "";
	}
	/// @author iain
	bool cmdOptionExists(const std::string &option) const {
		return std::find(this->tokens.begin(), this->tokens.end(), option)
			!= this->tokens.end();
	}
private:
	std::vector <std::string> tokens;
};

int main(int argc, char* argv[]) {
	InputParser input(argc, argv);
	std::string input_filename = "";
	if (input.cmdOptionExists("-in")) {
		input_filename = input.getCmdOption("-in");
	}

	/*
	/*int x = 0;
	x |= 1;
	cout<<"Hello, World!"<<endl;
	CT::Position c = CT::Position::invalid;
	CT::Automata::State<char> s(false);
	CT::RegexBuilder builder;
	auto nfa = builder.create("a+b");
	std::string str = "ab";
	for (auto c : str)
	{
		std::cout << (int)nfa->consume(c) << std::endl;
	}
	nfa.reset();
	CT::Lexer::Scanner scanner;
	scanner.registerToken(builder.create("a+b"), CT::Lexer::make_token_lib("ab"));
	CT::InputStreamPtr ss = std::make_shared<CT::InputStream>("ab aaaaaaaabc");
	while (true)
	{
		if (token == CT::Lexer::Token::eof || token == CT::Lexer::Token::invalid)
			break;
		cout << token.tag << endl;
	}
	std::cout<<CT::Log::getLogText()<<std::endl;
	auto in_stream = CT::read_stream(std::cin);
	std::cout << in_stream->getString() << std::endl;*/
	//for (int i = 0; i < 1; i++)
	//{

	//	auto t = CT::Lexer::Token::eof;
	//	CT::Lexer::IScannerPtr scanner = std::make_shared<CT::Lexer::GLexer>();
	//	CT::InputStreamPtr ss = CT::open_file("..\\test\\calc-rd-ll1-01.gr");
	//	/*while (true)
	//	{
	//		auto token = scanner->scan(ss);
	//		std::cout << CT::Lexer::TokenManager<CT::Lexer::TOKEN_SPACE::USER>::getTokenName(token.tag) << std::endl;
	//		if (token == CT::Lexer::Token::eof)
	//			break;
	//	}
	//	return 0;*/
	//	CT::Parser::IParserPtr parser = std::make_shared<CT::Parser::GParser>();
	//	auto program = parser->parse(scanner, ss);
	//	CT::CodeGen::LLKRD compiler_generator;
	//	auto generated_code = compiler_generator.generate(std::dynamic_pointer_cast<CT::Parser::GParseNode>(program));
	//	if (generated_code != CT::CodeGen::CodeGenOutput::invalid)
	//	{
	//		CT::write_file(generated_code.lexer_h_filename, generated_code.lexer_h);
	//		CT::write_file(generated_code.lexer_cpp_filename, generated_code.lexer_cpp);
	//		CT::write_file(generated_code.parser_h_filename, generated_code.parser_h);
	//		CT::write_file(generated_code.parser_cpp_filename, generated_code.parser_cpp);
	//	}
	//	std::cout << CT::Log::filterLog(CT::LOG_LEVEL::ERROR) << std::endl;
	//}

	//CT::InputStreamPtr ss = std::make_shared<CT::InputStream>("1+99");
	//auto calc_lexer = std::make_shared<SimpleCalc::SimpleCalcLexer>();
	//auto calc_parser = std::make_shared<SimpleCalc::SimpleCalcParser>();
	//while (true) {
	//	ss->clear();
	//	calc_lexer->clear();
	//	std::string input;
	//	int c = '\0';
	//	while ((c = std::getc(stdin)) != 27)
	//	{
	//		if (c == 8) {
	//			if(!input.empty())
	//				input.erase(input.size() - 1, 1);
	//		}
	//		else if (c == '\n')
	//		{
	//			break;
	//		}
	//		else
	//		{
	//			input += c;
	//		}
	//	}
	//	if (c == 27)
	//		break;
	//	//std::getline(std::cin, input);
	//	ss->append(input);
	//	auto program = calc_parser->parse(calc_lexer, ss);
	//	if (program) {
	//		auto generic_node = std::dynamic_pointer_cast<SimpleCalc::GenericNode>(program);
	//		auto result = generic_node->eval();
	//		if (result.type == SimpleCalc::num_value_type::REAL)
	//			std::cout << result.value.real << std::endl;
	//		else if (result.type == SimpleCalc::num_value_type::INT)
	//			std::cout << result.value.integer << std::endl;
	//	}
	//	else
	//	{
	//		std::cout << CT::Log::filterLog(CT::LOG_LEVEL::ERROR) << std::endl;
	//	}
	//}
	//std::cout << CT::Log::filterLog(CT::LOG_LEVEL::ERROR) << std::endl;


	//CT::InputStreamPtr ss = std::make_shared<CT::InputStream>("int");
	/*
	while (true) {
		auto token = scanner->scan(ss);
		if (token == CT::Lexer::Token::eof || token == CT::Lexer::Token::invalid)
			break;
		cout << "<" <<token.tag <<", "<< token.literal << ">" << endl;
	}
	//CT::Log::dumpLogEntriesToFile("log.txt");
	std::cout << CT::Log::filterLog(CT::LOG_LEVEL::ERROR) << std::endl;
	*/
	/*CT::InputStreamPtr ss2 = std::make_shared<CT::InputStream>("int x;");
	CT::Parser::IParserPtr parser = std::make_shared<CT::Parser::GenericParser>();
	parser->parse(scanner, ss2);*/

	//std::string grammar_filename = "grammar/c.gr";
	//CT::Lexer::IScannerPtr scanner = std::make_shared<CT::Lexer::GLexer>();
	//CT::InputStreamPtr ss = CT::open_file(grammar_filename);
	//auto c_token = scanner->scan(ss);
	//while (c_token != CT::Lexer::Token::eof)
	//{
	//	std::cout << c_token.tag << ": <" << c_token.literal.getString() << ">" <<std::endl;
	//	c_token = scanner->scan(ss);
	//}

	//cpp model
	/*string src = "x 334";
	std::regex num("x");
	std::smatch match;
	std::cout << std::regex_search(src, match, num, std::regex_constants::match_continuous) << std::endl;
	std::cout << match.size() << std::endl;
	for (int i = 0; i<match.size(); i++)
	{
		std::cout << match[i].str() << std::endl;
	}*/

	CT::InputStreamPtr file_input = CT::open_file(input_filename);
	auto lexer_ptr = std::make_shared<C::CLexer>();
	//auto c_token = lexer_ptr->scan(file_input);
	//while (c_token != CT::Lexer::Token::eof)
	//{
	//	if (c_token == CT::Lexer::Token::eof)
	//		out << "EOF" << std::endl;
	//	else if (c_token == CT::Lexer::Token::invalid)
	//		out << "invalid" << std::endl;
	//	else {
	//		out << c_token.tag << ": <" << c_token.literal.getString() << ">" << std::endl;
	//	}
	//	c_token = lexer_ptr->scan(file_input);
	//}
	//return 0;
	auto parser_ptr = std::make_shared<C::CParser>();
	auto program = parser_ptr->parse(lexer_ptr, file_input);
	std::cout << CT::Log::filterLog(CT::LOG_LEVEL::ERROR) << std::endl;
	return 0;
}