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
#include <ratio>
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


namespace my
{
	
}

int main(int argc, char* argv[]) {
	InputParser input(argc, argv);
	std::string input_filename = "";
	if (input.cmdOptionExists("-in")) {
		input_filename = input.getCmdOption("-in");
	}
	if (input_filename.empty())
		input_filename = "test/c_test_02.c";

	//testing the new vm execute algorithm
	//std::chrono::duration<double, std::micro> mine_duration;
	//for (int i = 0; i < 1; i++)
	//{
	//	auto start = std::chrono::high_resolution_clock::now();
	//	OCT::InputStreamPtr regex_input = std::make_shared<OCT::InputStream>("MoustaphaSaad_343");
	//	OCT::Regex::Compiler regex_compiler;
	//	OCT::Regex::VM vm;
	//	auto regex_result = vm.exec(regex_compiler.compile("[_a-zA-Z][_a-zA-Z0-9]*"), regex_input);
	//	auto end = std::chrono::high_resolution_clock::now();
	//	mine_duration += end - start;
	//}
	//std::cout << "avg mine: " << (mine_duration/1).count() << "ms" << std::endl;

	//std::string inputstr;
	//std::cin >> inputstr;
	//std::chrono::duration<double, std::micro> std_duration;
	//for (int i = 0; i < 1; i++)
	//{
	//	auto start = std::chrono::high_resolution_clock::now();

	//	std::regex pattern("[_a-zA-Z][_a-zA-Z0-9]*");
	//	std::smatch match_obj;
	//	std::regex_search(inputstr, match_obj, pattern, regex_constants::match_continuous);
	//	auto end = std::chrono::high_resolution_clock::now();
	//	std_duration += end - start;
	//}
	//std::cout << "avg std: " << (std_duration/1).count() << "ms" << std::endl;

	//if(mine_duration.count()>std_duration.count())
	//{
	//	std::cout << "you lose" << std::endl;
	//}else
	//{
	//	std::cout << "you win" << std::endl;
	//}
	//return 0;

	input_filename = "test/list_test01.list";
	//include example
	OCT::InputStreamPtr file_input = OCT::open_file(input_filename);
	if (file_input == nullptr) {
		std::cout << "error didn't find the file" << std::endl;
		return 0;
	}

	/*std::stack<int> std_stack;
	for (int i = 0; i<100000000; i++)
	{
		if (i % 2 == 0 && !std_stack.empty())
			std_stack.pop();
		std_stack.push(i);
	}*/
	
	
	//my::stack<int> mine_stack;
	//for(int i=0;i<100000000;i++)
	//{
	//	if(i%2==0 && !mine_stack.empty())
	//		mine_stack.pop();
	//	mine_stack.push(i);
	//}
	//mine_stack.clear();
	
	//return 0;

	//std::shared_ptr<includePrint::includePrintLexer> scanner = std::make_shared<includePrint::includePrintLexer>();
	//auto token = scanner->scan(file_input);
	//while(token != OCT::Lexer::Token::eof && token != OCT::Lexer::Token::invalid)
	//{
	//	//std::cout << token.tag << "<" << token.literal.getString() << ">" << std::endl;
	//	token = scanner->scan(file_input);
	//}
	//return 0;
	/*std::shared_ptr<includePrint::includePrintParser> parser = std::make_shared<includePrint::includePrintParser>();
	auto result = parser->parse(scanner, file_input);
	std::cout << scanner->getIndex() << std::endl;*/
	//return 0;

	//test VM Parser
	//OCT::InputStreamPtr file_input = OCT::open_file("test/list_test01.list");
	std::shared_ptr<digitList::digitListLexer> scanner = std::make_shared<digitList::digitListLexer>();
	std::shared_ptr<digitList::digitListParser> parser = std::make_shared<digitList::digitListParser>();
	auto result = parser->parse(scanner, file_input);
	return 0;

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