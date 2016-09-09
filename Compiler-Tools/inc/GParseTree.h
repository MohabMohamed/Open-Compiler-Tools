#pragma once

#include "Defines.h"
#include "Token.h"
#include <string>
#include <vector>
#include <memory>

namespace CT
{
	namespace Parser
	{

		enum class GParseNodeTypes : u8 {
			GENERIC, DIRECTIVE, NAME_DIRECTIVE, LEX_RULE, PARSE_RULE
		};

		class API GParseNode
		{
		public:
			std::vector<std::shared_ptr<GParseNode>> children;
			GParseNodeTypes type;

			GParseNode(GParseNodeTypes fType = GParseNodeTypes::GENERIC);
			virtual ~GParseNode();
		};
		using GParseNodePtr = std::shared_ptr<GParseNode>;

		class API GDirectiveNode: public GParseNode
		{
		public:
			std::string directiveValue;

			GDirectiveNode(GParseNodeTypes fType = GParseNodeTypes::DIRECTIVE);
			virtual ~GDirectiveNode();
		};

		class API GNameDirective: public GDirectiveNode
		{
		public:
			GNameDirective(GParseNodeTypes fType = GParseNodeTypes::NAME_DIRECTIVE);
		};

		class API GLexRule: public GParseNode
		{
		public:
			std::string tokenName;
			std::string regex;
			std::string action;

			GLexRule(GParseNodeTypes fType = GParseNodeTypes::LEX_RULE);
			virtual ~GLexRule();
		};

		class API GParseRule: public GParseNode
		{
		public:
			std::string name;
			std::vector<std::vector<CT::Lexer::Token>> rules;

			GParseRule(GParseNodeTypes fType = GParseNodeTypes::PARSE_RULE);
			virtual ~GParseRule();
		};

	}
}