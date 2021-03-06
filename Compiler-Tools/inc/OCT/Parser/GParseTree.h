#pragma once

#include "OCT/Defines.h"
#include "OCT/Lexer/Token.h"
#include "OCT/Parser/IParser.h"
#include <string>
#include <vector>
#include <memory>

namespace OCT
{
	namespace Parser
	{

		enum class GParseNodeTypes : u8 {
			GENERIC, DIRECTIVE, NAME_DIRECTIVE, LEX_RULE, PARSE_RULE, START_RULE, CPP_SEGMENT, HEADER_SEGMENT,
			PREDICATE
		};

		class API GParseNode: public IParseNode
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
			StringMarker directiveValue;

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
			StringMarker tokenName;
			std::vector<Lexer::Token> regex;
			StringMarker action;
			bool isSkip;

			GLexRule(GParseNodeTypes fType = GParseNodeTypes::LEX_RULE);
			virtual ~GLexRule();
		};

		class API GParseRulesTreeNode
		{
		public:
			//next nodes is a vector because it can branch
			std::vector<std::shared_ptr<GParseRulesTreeNode>> next;
			OCT::Lexer::Token token;
			StringMarker predicate;
			std::vector<StringMarker> immediateActions;
			StringMarker action;
			u32 immediateActionsCounter;
			bool isRoot;
			bool isLeaf;

			GParseRulesTreeNode(bool root = false);
			~GParseRulesTreeNode();

			StringMarker getImmediateAction();
			void resetImmediateActionCounter();

			std::shared_ptr<GParseRulesTreeNode> insertNode(const OCT::Lexer::Token& token);
		};
		using GParseRulesTreeNodePtr = std::shared_ptr<GParseRulesTreeNode>;

		class API GParseRule: public GParseNode
		{
		public:
			StringMarker name;
			std::shared_ptr<GParseRulesTreeNode> rules;

			GParseRule(GParseNodeTypes fType = GParseNodeTypes::PARSE_RULE);
			virtual ~GParseRule();
		};

		class API GStartRule : public GParseNode
		{
		public:
			StringMarker startRule;

			GStartRule(GParseNodeTypes fType = GParseNodeTypes::START_RULE);
			virtual ~GStartRule();
		};

		class API GCPPSegment : public GParseNode
		{
		public:
			StringMarker code;

			GCPPSegment(GParseNodeTypes fType = GParseNodeTypes::CPP_SEGMENT);
			virtual ~GCPPSegment();
		};

		class API GHeaderSegment : public GParseNode
		{
		public:
			StringMarker code;

			GHeaderSegment(GParseNodeTypes fType = GParseNodeTypes::HEADER_SEGMENT);
			virtual ~GHeaderSegment();
		};

		class API GPredicate : public GParseNode
		{
		public:
			StringMarker name;
			StringMarker code;

			GPredicate(GParseNodeTypes fType = GParseNodeTypes::PREDICATE);
			virtual ~GPredicate();
		};
	}
}