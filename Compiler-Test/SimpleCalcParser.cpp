#include "SimpleCalcParser.h"
#include <Token.h>
#include <Log.h>
using namespace SimpleCalc;
using namespace CT;
using namespace CT::Parser;

#include <iostream>
#include <memory>

GenericNode::GenericNode(SimpleCalcNodeTypes fType)
:type(fType)
{}

num_value GenericNode::eval()
{
	num_value result;
	result.type = num_value_type::NONE;
	return result;
}

IntNum::IntNum(SimpleCalcNodeTypes fType)
:GenericNode(fType)
{}

num_value IntNum::eval()
{
	num_value result;
	result.type = num_value_type::INT;
	result.value.integer = value;
	return result;
}

RealNum::RealNum(SimpleCalcNodeTypes fType)
:GenericNode(fType)
{}

num_value RealNum::eval()
{
	num_value result;
	result.type = num_value_type::INT;
	result.value.real = value;
	return result;
}

Factor::Factor(SimpleCalcNodeTypes fType)
:GenericNode(fType)
{}

num_value Factor::eval()
{
	return node->eval();
}

Term::Term(SimpleCalcNodeTypes fType)
:GenericNode(fType)
{}

num_value Term::eval()
{
	auto fvalue = factor->eval();
	if(op == "*")
	{
		auto tvalue = term->eval();
		num_value result;

		if (fvalue.type == num_value_type::INT && tvalue.type == num_value_type::INT)
		{
			result.type = num_value_type::INT;
			result.value.integer = fvalue.value.integer * tvalue.value.integer;
		}
		else if (fvalue.type == num_value_type::REAL && tvalue.type == num_value_type::REAL)
		{
			result.type = num_value_type::REAL;
			result.value.real = fvalue.value.real * tvalue.value.real;
		}
		else if (fvalue.type == num_value_type::INT && tvalue.type == num_value_type::REAL)
		{
			result.type = num_value_type::REAL;
			result.value.real = fvalue.value.integer * tvalue.value.real;
		}
		else if (fvalue.type == num_value_type::REAL && tvalue.type == num_value_type::INT)
		{
			result.type = num_value_type::REAL;
			result.value.real = fvalue.value.real * tvalue.value.integer;
		}

		return result;
	}else if(op == "/")
	{
		auto tvalue = term->eval();
		num_value result;

		if (fvalue.type == num_value_type::INT && tvalue.type == num_value_type::INT)
		{
			result.type = num_value_type::INT;
			result.value.integer = fvalue.value.integer / tvalue.value.integer;
		}
		else if (fvalue.type == num_value_type::REAL && tvalue.type == num_value_type::REAL)
		{
			result.type = num_value_type::REAL;
			result.value.real = fvalue.value.real / tvalue.value.real;
		}
		else if (fvalue.type == num_value_type::INT && tvalue.type == num_value_type::REAL)
		{
			result.type = num_value_type::REAL;
			result.value.real = fvalue.value.integer / tvalue.value.real;
		}
		else if (fvalue.type == num_value_type::REAL && tvalue.type == num_value_type::INT)
		{
			result.type = num_value_type::REAL;
			result.value.real = fvalue.value.real / tvalue.value.integer;
		}

		return result;
	}
	return fvalue;
}

Expr::Expr(SimpleCalcNodeTypes fType)
:GenericNode(fType)
{}

num_value Expr::eval()
{
	auto tvalue = term->eval();
	if(op == "+")
	{
		auto evalue = expr->eval();
		num_value result;

		if (tvalue.type == num_value_type::INT && evalue.type == num_value_type::INT) {
			result.type = num_value_type::INT;
			result.value.integer = tvalue.value.integer + evalue.value.integer;
		}
		else if (tvalue.type == num_value_type::REAL && evalue.type == num_value_type::REAL)
		{
			result.type = num_value_type::REAL;
			result.value.real = tvalue.value.real + evalue.value.real;
		}
		else if (tvalue.type == num_value_type::INT && evalue.type == num_value_type::REAL)
		{
			result.type = num_value_type::REAL;
			result.value.real = tvalue.value.integer + evalue.value.real;
		}
		else if (tvalue.type == num_value_type::REAL && evalue.type == num_value_type::INT)
		{
			result.type = num_value_type::REAL;
			result.value.real = tvalue.value.real + evalue.value.integer;
		}

		return result;
	}else if(op == "-")
	{
		auto evalue = expr->eval();
		num_value result;

		if (tvalue.type == num_value_type::INT && evalue.type == num_value_type::INT)
		{
			result.type = num_value_type::INT;
			result.value.integer = tvalue.value.integer - evalue.value.integer;
		}
		else if (tvalue.type == num_value_type::REAL && evalue.type == num_value_type::REAL)
		{
			result.type = num_value_type::REAL;
			result.value.real = tvalue.value.real - evalue.value.real;
		}
		else if (tvalue.type == num_value_type::INT && evalue.type == num_value_type::REAL)
		{
			result.type = num_value_type::REAL;
			result.value.real = tvalue.value.integer - evalue.value.real;
		}
		else if (tvalue.type == num_value_type::REAL && evalue.type == num_value_type::INT)
		{
			result.type = num_value_type::REAL;
			result.value.real = tvalue.value.real - evalue.value.integer;
		}
		return result;
	}
	return tvalue;
}


IParseNodePtr SimpleCalcParser::parsenum(CT::Lexer::CachedScannerPtr scanner, CT::InputStreamPtr input)
{
	std::vector<CT::Parser::ParsingElement> ct_elements;
	auto INTToken = scanner->scan(input);
	if(INTToken.tag == "INT")
	{
		CT::Parser::ParsingElement tokenElement; tokenElement.token = INTToken;
		ct_elements.push_back(tokenElement);
		{ 
					auto int_node = std::make_shared<IntNum>();
					int_node->value = std::stoi(ct_elements[0].token.literal.getString());
					return int_node;
				}
		return std::make_shared<IParseNode>();
	}
	scanner->rewindToken();
	auto REALToken = scanner->scan(input);
	if(REALToken.tag == "REAL")
	{
		CT::Parser::ParsingElement tokenElement; tokenElement.token = REALToken;
		ct_elements.push_back(tokenElement);
		{ 
					auto real_node = std::make_shared<RealNum>();
					real_node->value = std::stod(ct_elements[0].token.literal.getString());
					return real_node;
				}
		return std::make_shared<IParseNode>();
	}
	scanner->rewindToken();
	CT::Log::commitEntry(CT::LOG_LEVEL::ERROR, "parser was expecting one of this nodes {INT, REAL} but found none", input->getPosition());
	return nullptr;
}
IParseNodePtr SimpleCalcParser::parsefactor(CT::Lexer::CachedScannerPtr scanner, CT::InputStreamPtr input)
{
	std::vector<CT::Parser::ParsingElement> ct_elements;
	auto nodenum = parsenum(scanner, input);
	if(nodenum != nullptr)
	{
		CT::Parser::ParsingElement nodeElement; nodeElement.node = nodenum;
		ct_elements.push_back(nodeElement);
		{
					auto factor_node = std::make_shared<Factor>();
					factor_node->node = std::dynamic_pointer_cast<GenericNode>(ct_elements[0].node);
					return factor_node;
				}
		return std::make_shared<IParseNode>();
	}
	auto LPARENToken = scanner->scan(input);
	if(LPARENToken.tag == "LPAREN")
	{
		CT::Parser::ParsingElement tokenElement; tokenElement.token = LPARENToken;
		ct_elements.push_back(tokenElement);
		auto nodeexpr = parseexpr(scanner, input);
		if(nodeexpr != nullptr)
		{
			CT::Parser::ParsingElement nodeElement; nodeElement.node = nodeexpr;
			ct_elements.push_back(nodeElement);
			auto RPARENToken = scanner->scan(input);
			if(RPARENToken.tag == "RPAREN")
			{
				CT::Parser::ParsingElement tokenElement; tokenElement.token = RPARENToken;
				ct_elements.push_back(tokenElement);
				{
			auto factor_node = std::make_shared<Factor>();
			factor_node->node = std::dynamic_pointer_cast<GenericNode>(ct_elements[1].node);
			return factor_node;
		}
				return std::make_shared<IParseNode>();
			}
			scanner->rewindToken();
			CT::Log::commitEntry(CT::LOG_LEVEL::ERROR, "parser was expecting one of this nodes {RPAREN} but found none", input->getPosition());
			return nullptr;
		}
		CT::Log::commitEntry(CT::LOG_LEVEL::ERROR, "parser was expecting one of this nodes {expr} but found none", input->getPosition());
		return nullptr;
	}
	scanner->rewindToken();
	CT::Log::commitEntry(CT::LOG_LEVEL::ERROR, "parser was expecting one of this nodes {num, LPAREN} but found none", input->getPosition());
	return nullptr;
}
IParseNodePtr SimpleCalcParser::parseterm(CT::Lexer::CachedScannerPtr scanner, CT::InputStreamPtr input)
{
	std::vector<CT::Parser::ParsingElement> ct_elements;
	auto nodefactor = parsefactor(scanner, input);
	if(nodefactor != nullptr)
	{
		CT::Parser::ParsingElement nodeElement; nodeElement.node = nodefactor;
		ct_elements.push_back(nodeElement);
		auto MULToken = scanner->scan(input);
		if(MULToken.tag == "MUL")
		{
			CT::Parser::ParsingElement tokenElement; tokenElement.token = MULToken;
			ct_elements.push_back(tokenElement);
			auto nodeterm = parseterm(scanner, input);
			if(nodeterm != nullptr)
			{
				CT::Parser::ParsingElement nodeElement; nodeElement.node = nodeterm;
				ct_elements.push_back(nodeElement);
				{
			auto term_node = std::make_shared<Term>();
			term_node->factor = std::dynamic_pointer_cast<GenericNode>(ct_elements[0].node);
			term_node->term = std::dynamic_pointer_cast<GenericNode>(ct_elements[2].node);
			term_node->op = "*";
			return term_node;
		}
				return std::make_shared<IParseNode>();
			}
			CT::Log::commitEntry(CT::LOG_LEVEL::ERROR, "parser was expecting one of this nodes {term} but found none", input->getPosition());
			return nullptr;
		}
		scanner->rewindToken();
		auto DIVToken = scanner->scan(input);
		if(DIVToken.tag == "DIV")
		{
			CT::Parser::ParsingElement tokenElement; tokenElement.token = DIVToken;
			ct_elements.push_back(tokenElement);
			auto nodeterm = parseterm(scanner, input);
			if(nodeterm != nullptr)
			{
				CT::Parser::ParsingElement nodeElement; nodeElement.node = nodeterm;
				ct_elements.push_back(nodeElement);
				{
			auto term_node = std::make_shared<Term>();
			term_node->factor = std::dynamic_pointer_cast<GenericNode>(ct_elements[0].node);
			term_node->term = std::dynamic_pointer_cast<GenericNode>(ct_elements[2].node);
			term_node->op = "/";
			return term_node;
		}
				return std::make_shared<IParseNode>();
			}
			CT::Log::commitEntry(CT::LOG_LEVEL::ERROR, "parser was expecting one of this nodes {term} but found none", input->getPosition());
			return nullptr;
		}
		scanner->rewindToken();
		{
			auto term_node = std::make_shared<Term>();
			term_node->factor = std::dynamic_pointer_cast<GenericNode>(ct_elements[0].node);
			return term_node;
		}
		return std::make_shared<IParseNode>();
	}
	CT::Log::commitEntry(CT::LOG_LEVEL::ERROR, "parser was expecting one of this nodes {factor} but found none", input->getPosition());
	return nullptr;
}
IParseNodePtr SimpleCalcParser::parseexpr(CT::Lexer::CachedScannerPtr scanner, CT::InputStreamPtr input)
{
	std::vector<CT::Parser::ParsingElement> ct_elements;
	auto nodeterm = parseterm(scanner, input);
	if(nodeterm != nullptr)
	{
		CT::Parser::ParsingElement nodeElement; nodeElement.node = nodeterm;
		ct_elements.push_back(nodeElement);
		auto PLUSToken = scanner->scan(input);
		if(PLUSToken.tag == "PLUS")
		{
			CT::Parser::ParsingElement tokenElement; tokenElement.token = PLUSToken;
			ct_elements.push_back(tokenElement);
			auto nodeexpr = parseexpr(scanner, input);
			if(nodeexpr != nullptr)
			{
				CT::Parser::ParsingElement nodeElement; nodeElement.node = nodeexpr;
				ct_elements.push_back(nodeElement);
				{
			auto expr_node = std::make_shared<Expr>();
			expr_node->term = std::dynamic_pointer_cast<GenericNode>(ct_elements[0].node);
			expr_node->expr = std::dynamic_pointer_cast<GenericNode>(ct_elements[2].node);
			expr_node->op = "+";
			return expr_node;
		}
				return std::make_shared<IParseNode>();
			}
			CT::Log::commitEntry(CT::LOG_LEVEL::ERROR, "parser was expecting one of this nodes {expr} but found none", input->getPosition());
			return nullptr;
		}
		scanner->rewindToken();
		auto SUBToken = scanner->scan(input);
		if(SUBToken.tag == "SUB")
		{
			CT::Parser::ParsingElement tokenElement; tokenElement.token = SUBToken;
			ct_elements.push_back(tokenElement);
			auto nodeexpr = parseexpr(scanner, input);
			if(nodeexpr != nullptr)
			{
				CT::Parser::ParsingElement nodeElement; nodeElement.node = nodeexpr;
				ct_elements.push_back(nodeElement);
				{
			auto expr_node = std::make_shared<Expr>();
			expr_node->term = std::dynamic_pointer_cast<GenericNode>(ct_elements[0].node);
			expr_node->expr = std::dynamic_pointer_cast<GenericNode>(ct_elements[2].node);
			expr_node->op = "-";
			return expr_node;
		}
				return std::make_shared<IParseNode>();
			}
			CT::Log::commitEntry(CT::LOG_LEVEL::ERROR, "parser was expecting one of this nodes {expr} but found none", input->getPosition());
			return nullptr;
		}
		scanner->rewindToken();
		{
			auto expr_node = std::make_shared<Expr>();
			expr_node->term = std::dynamic_pointer_cast<GenericNode>(ct_elements[0].node);
			return expr_node;
		}
		return std::make_shared<IParseNode>();
	}
	CT::Log::commitEntry(CT::LOG_LEVEL::ERROR, "parser was expecting one of this nodes {term} but found none", input->getPosition());
	return nullptr;
}
IParseNodePtr SimpleCalcParser::parse(CT::Lexer::IScannerPtr scanner, CT::InputStreamPtr input)
{
	auto cached_scanner = std::dynamic_pointer_cast<CT::Lexer::CachedScanner>(scanner);
	if(cached_scanner == nullptr)
		return nullptr;
	auto result =  parseexpr(cached_scanner, input);
	if (result == nullptr)
		CT::Log::pushEntries();
	else
		CT::Log::discardCommittedEntries();
	return result;
}
