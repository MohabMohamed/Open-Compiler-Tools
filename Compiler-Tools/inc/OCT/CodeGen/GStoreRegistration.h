#pragma once

#include "OCT/Defines.h"
#include "OCT/CodeGen/Store.h"
#include "OCT/Parser/GParseTree.h"
#include "OCT/CodeGen/IGCodeGeneration.h"

namespace OCT
{
	namespace CodeGen
	{
		class API GStoreRegistration: public IGrammarProcessor
		{
		public:
			bool process(std::vector<OCT::Parser::GParseNodePtr>& grammar) override;
		};
	}
}