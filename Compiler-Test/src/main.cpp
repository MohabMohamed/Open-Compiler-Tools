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
	auto nfa = builder.Create("a*b");
	std::string str = "aaab";
	for (auto c : str)
	{
		std::cout << (int) nfa.consume(CT::Automata::StateToken<char>(c)) << std::endl;
	}
	return 0;
}