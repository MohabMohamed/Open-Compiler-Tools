#pragma once
#include "Defines.h"
#include "Scanner.h"
#include "InputStream.h"
#include <memory>
#include <map>
#include <vector>

namespace CT
{
	namespace Parser
	{
		class API IParser
		{
		public:
			virtual void parse(Lexer::IScannerPtr scanner, CT::InputStreamPtr input) = 0;
			virtual void add_rule(const std::string&,const std::string&) = 0;
		};
		using IParserPtr = std::shared_ptr<IParser>;

		class API GenericParser: public IParser
		{
		protected:
			//<rule_name, rule>
			std::multimap<std::string, std::vector<std::string>> m_rules;
		public:
			void parse(Lexer::IScannerPtr scanner, CT::InputStreamPtr input) override;
			void add_rule(const std::string& tmpName,const std::string& rule) override;
		};
	}
}