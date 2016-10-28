#include "Chalcedony/Parser/IParser.h"
#include <cstring>

CT::Parser::ParsingElement::ParsingElement()
{
	std::memset(this, 0, sizeof(CT::Parser::ParsingElement));
}

CT::Parser::ParsingElement::~ParsingElement()
{
	std::memset(this, 0, sizeof(CT::Parser::ParsingElement));
}

CT::Parser::ParsingElement::ParsingElement(const ParsingElement & element)
{
	std::memcpy(this, &element, sizeof(CT::Parser::ParsingElement));
}
