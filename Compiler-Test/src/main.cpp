#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <fstream>
#include <memory>
#include <regex>
#include <OCT/Chalcedony.h>
#include <OCT/Fluorine/Renderer.h>
#include <chrono>
#include "digitListLexer.h"
#include "digitListParser.h"
#include "includePrintLexer.h"
#include "includePrintParser.h"

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
	if (input_filename.empty())
		input_filename = "test/c_test_02.c";

	//include example
	OCT::InputStreamPtr file_input = OCT::open_file(input_filename);
	if (file_input == nullptr) {
		std::cout << "error didn't find the file" << std::endl;
		return 0;
	}

	std::shared_ptr<includePrint::includePrintLexer> scanner = std::make_shared<includePrint::includePrintLexer>();
	std::shared_ptr<includePrint::includePrintParser> parser = std::make_shared<includePrint::includePrintParser>();
	auto result = parser->parse(scanner, file_input);
	std::cout << scanner->getIndex() << std::endl;
	return 0;
	//test VM Parser
	//OCT::InputStreamPtr file_input = OCT::open_file("test/list_test01.list");
	//std::shared_ptr<digitList::digitListLexer> scanner = std::make_shared<digitList::digitListLexer>();
	//std::shared_ptr<digitList::digitListParser> parser = std::make_shared<digitList::digitListParser>();
	//auto result = parser->parse(scanner, file_input);
	//return 0;
	//auto token = scanner->scan(file_input);
	//while(token != OCT::Lexer::Token::invalid && token != OCT::Lexer::Token::eof)
	//{
	//	std::cout << token.tag << "<" << token.literal.getString() << ">" << std::endl;
	//	token = scanner->scan(file_input);
	//}

	//test code

	//OCT::InputStreamPtr file_input = OCT::open_file("grammar/digit_list.gr");
	//auto grammar_scanner = std::make_shared<OCT::Lexer::GLexer>();
	//OCT::Parser::GParser grammar_parser;
	//auto koko = grammar_parser.parse(grammar_scanner, file_input);
	//OCT::CodeGen::LLKSRD code_generator;
	//code_generator.generate(std::dynamic_pointer_cast<OCT::Parser::GParseNode>(koko));
	//std::cout << OCT::Log::filterLog(OCT::LOG_LEVEL::ERROR) << std::endl;
	//test grammar

	//OCT::InputStreamPtr file_input = OCT::open_file("grammar/c.gr");
	//auto grammar_scanner = std::make_shared<OCT::Lexer::GLexer>();
	//OCT::Parser::GParser grammar_parser;
	//auto koko = grammar_parser.parse(grammar_scanner, file_input);
	//OCT::CodeGen::LLKRD code_generator;
	//code_generator.generate(std::dynamic_pointer_cast<OCT::Parser::GParseNode>(koko));

	//actual c program
	/*OCT::InputStreamPtr file_input = OCT::open_file(input_filename);
	auto lexer_ptr = std::make_shared<C::CLexer>();
	auto token = lexer_ptr->scan(file_input);
	while (token != OCT::Lexer::Token::eof && token != OCT::Lexer::Token::invalid)
	{
		token = lexer_ptr->scan(file_input);
	}
	return 0;
	auto parser_ptr = std::make_shared<C::CParser>();
	auto program = parser_ptr->parse(lexer_ptr, file_input);
	std::cout << OCT::Log::filterLog(OCT::LOG_LEVEL::ERROR) << std::endl;*/
	return 0;
}