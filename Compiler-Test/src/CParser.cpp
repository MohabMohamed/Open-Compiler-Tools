#include "CParser.h"
#include <Chalcedony/Lexer/Token.h>
#include <Chalcedony/Log.h>
using namespace C;
using namespace CT;
using namespace CT::Parser;
IParseNodePtr CParser::parseprogram(CT::Lexer::CachedScannerPtr ct_scanner, CT::InputStreamPtr ct_input)
{
	std::vector<CT::Parser::ParsingElement> ct_elements;
	auto MULTI_LINE_COMMENTToken = ct_scanner->scan(ct_input);
	if(MULTI_LINE_COMMENTToken.tag == "MULTI_LINE_COMMENT")
	{
		CT::Parser::ParsingElement tokenElement; tokenElement.token = MULTI_LINE_COMMENTToken;
		ct_elements.push_back(tokenElement);
		return std::make_shared<IParseNode>();
	}
	ct_scanner->rewindToken();
	CT::Log::commitEntry(CT::LOG_LEVEL::ERROR, "parser was expecting one of this nodes {MULTI_LINE_COMMENT} but found none", ct_input->getPosition());
	return nullptr;
}
IParseNodePtr CParser::parse(CT::Lexer::IScannerPtr ct_scanner, CT::InputStreamPtr ct_input)
{
	auto cached_scanner = std::dynamic_pointer_cast<CT::Lexer::CachedScanner>(ct_scanner);
	if(cached_scanner == nullptr)
		return nullptr;
	auto result =  parseprogram(cached_scanner, ct_input);
	if (result == nullptr)
		CT::Log::pushEntries();
	else
		CT::Log::discardCommittedEntries();
	return result;
}
