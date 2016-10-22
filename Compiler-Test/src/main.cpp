#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <fstream>
#include <memory>
#include <regex>
#include <Chalcedony/Chalcedony.h>
#include "CLexer.h"
#include "CParser.h"

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
	//test grammar

	//CT::InputStreamPtr file_input = CT::open_file("grammar/c.gr");
	//auto grammar_scanner = std::make_shared<CT::Lexer::GLexer>();
	//CT::Parser::GParser grammar_parser;
	//auto koko = grammar_parser.parse(grammar_scanner, file_input);
	//CT::CodeGen::LLKRD code_generator;
	//code_generator.generate(std::dynamic_pointer_cast<CT::Parser::GParseNode>(koko));

	CT::InputStreamPtr file_input = CT::open_file(input_filename);
	auto lexer_ptr = std::make_shared<C::CLexer>();
	auto token = lexer_ptr->scan(file_input);
	while (token != CT::Lexer::Token::eof && token != CT::Lexer::Token::invalid)
	{
		token = lexer_ptr->scan(file_input);
	}
	return 0;
	auto parser_ptr = std::make_shared<C::CParser>();
	auto program = parser_ptr->parse(lexer_ptr, file_input);
	std::cout << CT::Log::filterLog(CT::LOG_LEVEL::ERROR) << std::endl;
	return 0;
}