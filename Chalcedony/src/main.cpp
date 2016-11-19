#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <OCT/Chalcedony.h>

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

const std::string VERSION = "1.0";
void printVersion(const std::string& version)
{
	std::cout << "Chalcedony " << VERSION << std::endl;
	std::cout << "A light-weight compiler tools in C++ " << std::endl;
	std::cout << "Author: Moustapha Saad" << std::endl;
	std::cout << "Mail: moustapha.saad.abdelhamed@gmail.com" << std::endl;
}

void printHelp()
{
	std::cout << "Chalcedony [option] [arg]" << std::endl << std::endl;
	std::cout << "\t-h \t\t\t display this message." << std::endl << std::endl;
	std::cout << "\t--help \t\t\t display this message." << std::endl << std::endl;
	std::cout << "\t-v \t\t\t display the version." << std::endl << std::endl;
	std::cout << "\t--version \t\t\t display the version." << std::endl << std::endl;
	std::cout << "\t-in \t\t\t specify the grammar input file." << std::endl << std::endl;
	std::cout << "\t-hout \t\t\t specify the output directory of header files." << std::endl << std::endl;
	std::cout << "\t-cppout \t\t\t specify the output directory of cpp files." << std::endl << std::endl;
	std::cout << "For more help use the above e-mail" << std::endl;
}

int main(int argc, char* argv[]) {
	InputParser input(argc, argv);

	std::string grammar_filename = "", header_path = "", cpp_path = "";

	if (input.cmdOptionExists("-h")) {
		printVersion(VERSION);
		printHelp();
		return 0;
	}
	if (input.cmdOptionExists("--help"))
	{
		printVersion(VERSION);
		printHelp();
		return 0;
	}
	if (input.cmdOptionExists("-v"))
	{
		printVersion(VERSION);
		return 0;
	}
	if (input.cmdOptionExists("--version")) {
		printVersion(VERSION);
		return 0;
	}

	if (input.cmdOptionExists("-in")) {
		grammar_filename = input.getCmdOption("-in");
	}
	if (input.cmdOptionExists("-hout")) {
		header_path = input.getCmdOption("-hout");
	}
	if (input.cmdOptionExists("-cppout")) {
		cpp_path = input.getCmdOption("-cppout");
	}

	if (grammar_filename.empty())
	{
		printVersion(VERSION);
		printHelp();
		return 0;
	}

	OCT::Lexer::IScannerPtr scanner = std::make_shared<OCT::Lexer::GLexer>();
	OCT::InputStreamPtr ss = OCT::open_file(grammar_filename);
	OCT::Parser::IParserPtr parser = std::make_shared<OCT::Parser::GParser>();
	auto program = parser->parse(scanner, ss);
	OCT::CodeGen::LLKSRD compiler_generator;
	auto generated_code = compiler_generator.generate(std::dynamic_pointer_cast<OCT::Parser::GParseNode>(program));
	for (auto module : generated_code.modules)
	{
		OCT::write_file(header_path + "/" + module->filename + ".h", module->header.str());
		OCT::write_file(cpp_path + "/" + module->filename + ".cpp", module->source.str());
	}

	//OCT::CodeGen::LLKRD compiler_generator;
	//auto generated_code = compiler_generator.generate(std::dynamic_pointer_cast<OCT::Parser::GParseNode>(program));
	/*if (generated_code != OCT::CodeGen::CodeGenOutput::invalid)
	{
		if(!header_path.empty())
			OCT::write_file(header_path + "/" + generated_code.lexer_h_filename, generated_code.lexer_h);
		else
			OCT::write_file(generated_code.lexer_h_filename, generated_code.lexer_h);

		if(!cpp_path.empty())
			OCT::write_file(cpp_path + "/" + generated_code.lexer_cpp_filename, generated_code.lexer_cpp);
		else
			OCT::write_file(generated_code.lexer_cpp_filename, generated_code.lexer_cpp);

		if(!header_path.empty())
			OCT::write_file(header_path + "/" + generated_code.parser_h_filename, generated_code.parser_h);
		else
			OCT::write_file(generated_code.parser_h_filename, generated_code.parser_h);

		if(!cpp_path.empty())
			OCT::write_file(cpp_path + "/" + generated_code.parser_cpp_filename, generated_code.parser_cpp);
		else
			OCT::write_file(generated_code.parser_cpp_filename, generated_code.parser_cpp);
	}*/
	std::cout << OCT::Log::filterLog(OCT::LOG_LEVEL::ERROR) << std::endl;
	return 0;
}