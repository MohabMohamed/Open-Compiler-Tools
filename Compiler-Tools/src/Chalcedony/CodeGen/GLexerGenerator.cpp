#include "Chalcedony/CodeGen/GLexerGenerator.h"
#include "Chalcedony/CodeGen/Librarian.h"
#include <cereal/cereal.hpp>
#include <cereal/archives/binary.hpp>

using namespace CT;
using namespace CT::CodeGen;
using namespace CT::Parser;

void GLexerGenerator::generate(const std::vector<GParseNodePtr>& parse_nodes, std::ostream& out)
{
	Librarian librarian;

	//populating the librarian
	for (auto node : parse_nodes)
	{
		switch (node->type)
		{
		case CT::Parser::GParseNodeTypes::LEX_RULE:
			{
				auto lex_rule_node = std::dynamic_pointer_cast<GLexRule>(node);
				librarian.addLexRule(lex_rule_node->tokenName.getString());
			}
			break;
		case CT::Parser::GParseNodeTypes::PARSE_RULE:
			{
				auto parse_rule_node = std::dynamic_pointer_cast<GParseRule>(node);
				librarian.addParseRule(parse_rule_node->name.getString());
			}
			break;
		default:
			break;
		}
	}

	out << "const char* librarian_memory = \"";
	//serializaing the librarian in a string and writing it
	cereal::BinaryOutputArchive archive(out);
	librarian.save(archive);
	out << ";";
	return;
}