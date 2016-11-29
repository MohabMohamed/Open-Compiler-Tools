#include "digitListParser.h"
#include <OCT/Lexer/Token.h>
#include <OCT/Log.h>
#include <OCT/CodeGen/Store.h>
using namespace digitList;
using namespace OCT;
using namespace OCT::Parser;
void digitListParser::initStore()
{
	static bool initialized = false;
	if(!initialized)
	{
		CodeGen::Store store;
		bool result = true;
		result = store.insertLexRule("Comma", 2147483657);
		if(!result)
		{
			throw std::logic_error("[Parser::initStore]: cannot insert same lexer rule entry twice");
		}
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
		result = store.insertLexRule("OpenBrace", 2147483655);
		if(!result)
		{
			throw std::logic_error("[Parser::initStore]: cannot insert same lexer rule entry twice");
		}
		result = store.insertLexRule("CloseBrace", 2147483656);
		if(!result)
		{
			throw std::logic_error("[Parser::initStore]: cannot insert same lexer rule entry twice");
		}
		result = store.insertLexRule("Digit", 2147483658);
		if(!result)
		{
			throw std::logic_error("[Parser::initStore]: cannot insert same lexer rule entry twice");
		}
		result = store.insertLexRule("Int", 2147483659);
		if(!result)
		{
			throw std::logic_error("[Parser::initStore]: cannot insert same lexer rule entry twice");
		}
		result = store.insertLexRule("Real", 2147483660);
		if(!result)
		{
			throw std::logic_error("[Parser::initStore]: cannot insert same lexer rule entry twice");
		}
		result = store.insertParseRule("list", 1073741837);
		if(!result)
		{
			throw std::logic_error("[Parser::initStore]: cannot insert same parser rule entry twice");
		}
		result = store.insertParseRule("elements", 1073741838);
		if(!result)
		{
			throw std::logic_error("[Parser::initStore]: cannot insert same parser rule entry twice");
		}
		result = store.insertParseRule("element", 1073741839);
		if(!result)
		{
			throw std::logic_error("[Parser::initStore]: cannot insert same parser rule entry twice");
		}
		result = store.insertParseRule("list", 1073741840);
		if(!result)
		{
			throw std::logic_error("[Parser::initStore]: cannot insert same parser rule entry twice");
		}
		result = store.insertParseRule("elements", 1073741841);
		if(!result)
		{
			throw std::logic_error("[Parser::initStore]: cannot insert same parser rule entry twice");
		}
		result = store.insertParseRule("element", 1073741842);
		if(!result)
		{
			throw std::logic_error("[Parser::initStore]: cannot insert same parser rule entry twice");
		}
		initialized = true;
	}
}
void digitListParser::init()
{
	initStore();
	OCT::u64 listProgram [7] = {
		0x8000000000000001, 0x4000000080000007, 0x8000000000000002, 
		0x400000004000000e, 0x8000000000000001, 0x4000000080000008, 
		0x8000000000000006
	};
	m_parserVM.addProgram("list", std::make_shared<OCT::Cartridge>(listProgram, 7));
	OCT::u64 elementsProgram [11] = {
		0x8000000000000002, 0x400000004000000f, 0x8000000000000004, 
		0x4000000000000001, 0x4000000000000000, 0x8000000000000006, 
		0x8000000000000001, 0x4000000080000009, 0x8000000000000002, 
		0x400000004000000e, 0x8000000000000006
	};
	m_parserVM.addProgram("elements", std::make_shared<OCT::Cartridge>(elementsProgram, 11));
	OCT::u64 elementProgram [3] = {
		0x8000000000000001, 0x400000008000000a, 0x8000000000000006
		
	};
	m_parserVM.addProgram("element", std::make_shared<OCT::Cartridge>(elementProgram, 3));
	m_parserVM.setStartProgram("list");
}
digitListParser::digitListParser()
{
	init();
}
OCT::Parser::IParseNodePtr digitListParser::parse(OCT::Lexer::IScannerPtr ct_scanner, OCT::InputStreamPtr ct_input)
{
	return m_parserVM.exec(ct_scanner, ct_input);
}
