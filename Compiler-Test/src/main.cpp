#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <Chalcedony\Chalcedony.h>
#include "SimpleCalcLexer.h"
#include "SimpleCalcParser.h"

using namespace std;
int main() {
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
	for (int i = 0; i < 1; i++)
	{

		auto t = CT::Lexer::Token::eof;
		CT::Lexer::IScannerPtr scanner = std::make_shared<CT::Lexer::GLexer>();
		CT::InputStreamPtr ss = CT::open_file("..\\test\\calc-rd-ll1-01.gr");
		/*while (true)
		{
			auto token = scanner->scan(ss);
			std::cout << CT::Lexer::TokenManager<CT::Lexer::TOKEN_SPACE::USER>::getTokenName(token.tag) << std::endl;
			if (token == CT::Lexer::Token::eof)
				break;
		}
		return 0;*/
		CT::Parser::IParserPtr parser = std::make_shared<CT::Parser::GParser>();
		auto program = parser->parse(scanner, ss);
		CT::CodeGen::LLKRD compiler_generator;
		auto generated_code = compiler_generator.generate(std::dynamic_pointer_cast<CT::Parser::GParseNode>(program));
		CT::write_file(generated_code.lexer_h_filename, generated_code.lexer_h);
		CT::write_file(generated_code.lexer_cpp_filename, generated_code.lexer_cpp);
		CT::write_file(generated_code.parser_h_filename, generated_code.parser_h);
		CT::write_file(generated_code.parser_cpp_filename, generated_code.parser_cpp);
		std::cout << CT::Log::filterLog(CT::LOG_LEVEL::ERROR) << std::endl;
	}

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
	std::cout << "end" << std::endl;
	return 0;
}