#include <iostream>
#include <string>
#include <Position.h>
#include <State.hpp>
#include <NFA.hpp>
#include <RegexBuilder.h>

using namespace std;
int main(){
	cout<<"Hello, World!"<<endl;
	CT::Position c;
	CT::Automata::State<char> s(false);
	CT::RegexBuilder builder;
	// auto nfa = builder.Create("a*b");
	// std::string str = "aaab";
	// for (auto c : str)
	// {
	// 	std::cout << (int) nfa.consume(CT::Automata::StateToken<char>(c)) << std::endl;
	// }
	// cout << "new nfa" << endl;
	// auto nfa2 = builder.Create("aba");
	// for(auto c : str)
	// {
	// 	std::cout<< (int)nfa2.consume(CT::Automata::StateToken<char>(c)) << std::endl;
	// }
	cout << "new nfa" << endl;
	auto nfa2 = builder.Create("a+b*");
	std::string str = "aaaaaaaaaabbbbbbbbbbbb";
	for (auto c : str)
	{
		std::cout << (int)nfa2.consume(CT::Automata::StateToken<char>(c)) << std::endl;
	}
	return 0;
}