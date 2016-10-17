#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <fstream>
#include <memory>
#include <regex>
#include <Chalcedony/Chalcedony.h>

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

	CT::Regex::Compiler compiler;
	CT::Regex::ProgramPtr regex_program = compiler.compile("( +)");
	CT::Regex::VM vm;
	auto input_stream = std::make_shared<CT::InputStream>("    ");
	CT::Regex::VM::printProgram(regex_program, std::cout);
	auto match = vm.exec(regex_program, input_stream);
	return 0;
	//CT::InputStreamPtr file_input = CT::open_file(input_filename);
	//auto lexer_ptr = std::make_shared<C::CLexer>();
	////auto c_token = lexer_ptr->scan(file_input);
	////while (c_token != CT::Lexer::Token::eof)
	////{
	////	if (c_token == CT::Lexer::Token::eof)
	////		out << "EOF" << std::endl;
	////	else if (c_token == CT::Lexer::Token::invalid)
	////		out << "invalid" << std::endl;
	////	else {
	////		out << c_token.tag << ": <" << c_token.literal.getString() << ">" << std::endl;
	////	}
	////	c_token = lexer_ptr->scan(file_input);
	////}
	////return 0;
	//auto parser_ptr = std::make_shared<C::CParser>();
	//auto program = parser_ptr->parse(lexer_ptr, file_input);
	std::cout << CT::Log::filterLog(CT::LOG_LEVEL::ERROR) << std::endl;
	return 0;
}