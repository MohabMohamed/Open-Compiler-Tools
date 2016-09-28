#pragma once
#include <Defines.h>
#include <IParser.h>
#include <IScanner.h>
#include <CachedScanner.h>
#include <InputStream.h>
namespace SimpleCalc
{

	enum class SimpleCalcNodeTypes { GENERIC, INT_NUM, REAL_NUM, FACTOR, TERM, EXPR};

	union num_value_union{
		int integer;
		double real;
	};

	enum class num_value_type {NONE, REAL, INT};

	struct num_value{
		num_value_type type;
		num_value_union value;
	};

	class GenericNode: public CT::Parser::IParseNode
	{
	public:
		SimpleCalcNodeTypes type;
		GenericNode(SimpleCalcNodeTypes fType = SimpleCalcNodeTypes::GENERIC);

		virtual num_value eval();
	};

	class IntNum: public GenericNode
	{
	public:
		int value;
		IntNum(SimpleCalcNodeTypes fType = SimpleCalcNodeTypes::INT_NUM);

		num_value eval() override;
	};

	class RealNum: public GenericNode
	{
	public:
		double value;
		RealNum(SimpleCalcNodeTypes fType = SimpleCalcNodeTypes::REAL_NUM);

		num_value eval() override;
	};

	class Factor: public GenericNode
	{
	public:
		std::shared_ptr<GenericNode> node;
		Factor(SimpleCalcNodeTypes fType = SimpleCalcNodeTypes::FACTOR);

		num_value eval() override;
	};

	class Term: public GenericNode
	{
	public:
		std::shared_ptr<GenericNode> factor;
		std::string op;
		std::shared_ptr<GenericNode> term;
		Term(SimpleCalcNodeTypes fType = SimpleCalcNodeTypes::TERM);

		num_value eval() override;
	};

	class Expr: public GenericNode
	{
	public:
		std::shared_ptr<GenericNode> term;
		std::string op;
		std::shared_ptr<GenericNode> expr;
		Expr(SimpleCalcNodeTypes fType = SimpleCalcNodeTypes::EXPR);

		num_value eval() override;
	};

	class SimpleCalcParser: public CT::Parser::IParser
	{
	private:
		CT::Parser::IParseNodePtr parsenum(CT::Lexer::CachedScannerPtr scanner, CT::InputStreamPtr input);
		CT::Parser::IParseNodePtr parsefactor(CT::Lexer::CachedScannerPtr scanner, CT::InputStreamPtr input);
		CT::Parser::IParseNodePtr parseterm(CT::Lexer::CachedScannerPtr scanner, CT::InputStreamPtr input);
		CT::Parser::IParseNodePtr parseexpr(CT::Lexer::CachedScannerPtr scanner, CT::InputStreamPtr input);
	public:
		CT::Parser::IParseNodePtr parse(CT::Lexer::IScannerPtr scanner, CT::InputStreamPtr input) override;
	};
}