#include "OCT/Parser/IParser.h"
#include <cstring>

OCT::Parser::ParsingElement::ParsingElement()
{
	std::memset(this, 0, sizeof(OCT::Parser::ParsingElement));
}

OCT::Parser::ParsingElement::~ParsingElement()
{
	std::memset(this, 0, sizeof(OCT::Parser::ParsingElement));
}

OCT::Parser::ParsingElement::ParsingElement(const ParsingElement & element)
{
	std::memcpy(this, &element, sizeof(OCT::Parser::ParsingElement));
}
