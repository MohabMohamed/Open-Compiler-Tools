#include <iostream>
#include <string>
#include <sstream>
#include <CompilerTools.h>

using namespace std;
int main(){
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
	std::stringstream ss;
	ss << "abaaaaaaaab";
	while (true)
	{
		auto token = scanner.scan(ss);
		if (token == CT::Lexer::Token::eof || token == CT::Lexer::Token::invalid)
			break;
		cout << token.tag << endl;
	}
	std::cout<<CT::Log::getLogText()<<std::endl;
	return 0;
}