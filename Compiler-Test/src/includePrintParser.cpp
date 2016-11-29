#include "includePrintParser.h"
#include <OCT/Lexer/Token.h>
#include <OCT/Log.h>
#include <OCT/CodeGen/Store.h>
using namespace includePrint;
using namespace OCT;
using namespace OCT::Parser;
void includePrintParser::initStore()
{
	static bool initialized = false;
	if(!initialized)
	{
		CodeGen::Store store;
		bool result = true;
		result = store.insertLexRule("Newline", 2147483649);
		if(!result)
		{
			throw std::logic_error("[Parser::initStore]: cannot insert same lexer rule entry twice");
		}
		result = store.insertLexRule("CarrReturn", 2147483650);
		if(!result)
		{
			throw std::logic_error("[Parser::initStore]: cannot insert same lexer rule entry twice");
		}
		result = store.insertLexRule("Space", 2147483651);
		if(!result)
		{
			throw std::logic_error("[Parser::initStore]: cannot insert same lexer rule entry twice");
		}
		result = store.insertLexRule("Tab", 2147483652);
		if(!result)
		{
			throw std::logic_error("[Parser::initStore]: cannot insert same lexer rule entry twice");
		}
		result = store.insertLexRule("VerticalSpace", 2147483653);
		if(!result)
		{
			throw std::logic_error("[Parser::initStore]: cannot insert same lexer rule entry twice");
		}
		result = store.insertLexRule("FThing", 2147483654);
		if(!result)
		{
			throw std::logic_error("[Parser::initStore]: cannot insert same lexer rule entry twice");
		}
		result = store.insertLexRule("Unidentified", 2147483655);
		if(!result)
		{
			throw std::logic_error("[Parser::initStore]: cannot insert same lexer rule entry twice");
		}
		result = store.insertParseRule("start", 1073741832);
		if(!result)
		{
			throw std::logic_error("[Parser::initStore]: cannot insert same parser rule entry twice");
		}
		result = store.insertParseRule("start", 1073741833);
		if(!result)
		{
			throw std::logic_error("[Parser::initStore]: cannot insert same parser rule entry twice");
		}
		initialized = true;
	}
}
void includePrintParser::init()
{
	initStore();
	OCT::u64 startProgram [9] = {
		0x8000000000000001, 0x8000000000000003, 0x8000000000000004, 
		0x4000000000000001, 0x4000000000000000, 0x8000000000000006, 
		0x8000000000000002, 0x4000000040000008, 0x8000000000000006
		
	};
	m_parserVM.addProgram("start", std::make_shared<OCT::Cartridge>(startProgram, 9));
	m_parserVM.setStartProgram("start");
}
includePrintParser::includePrintParser()
{
	init();
}
OCT::Parser::IParseNodePtr includePrintParser::parse(OCT::Lexer::IScannerPtr ct_scanner, OCT::InputStreamPtr ct_input)
{
	return m_parserVM.exec(ct_scanner, ct_input);
}
