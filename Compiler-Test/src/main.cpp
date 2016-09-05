#include <iostream>
#include <string>
#include <sstream>
#include <CompilerTools.h>
#include <CPPScanner.h>
#include <GLexer.h>

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
	scanner.registerToken(builder.create("a+b"), CT::Lexer::make_token("ab"));
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

	CT::Lexer::IScannerPtr scanner = std::make_shared<CT::Lexer::GLexer>();
	CT::InputStreamPtr ss = CT::open_file("E:\\Projects\\Compiler-Tools-v1.0\\test\\calc-rd-ll1-01.gr");
	CT::Parser::IParserPtr parser = std::make_shared<CT::Parser::GParser>();
	auto program = parser->parse(scanner, ss);
	//CT::InputStreamPtr ss = std::make_shared<CT::InputStream>("int");
	while (true) {
		auto token = scanner->scan(ss);
		if (token == CT::Lexer::Token::eof || token == CT::Lexer::Token::invalid)
			break;
		cout << "<" <<token.tag <<", "<< token.literal << ">" << endl;
	}
	CT::Log::dumpLogEntriesToFile("log.txt");
	std::cout << CT::Log::filterLog(CT::LOG_LEVEL::ERROR) << std::endl;
	/*CT::InputStreamPtr ss2 = std::make_shared<CT::InputStream>("int x;");
	CT::Parser::IParserPtr parser = std::make_shared<CT::Parser::GenericParser>();
	parser->parse(scanner, ss2);*/
	return 0;
}