#pragma once

#include "OCT/Defines.h"
#include "OCT/CodeGen/IGCodeGeneration.h"
#include "OCT/Parser/GParseTree.h"
#include <tuple>
#include <memory>
#include <ostream>
#include <unordered_map>
#include <map>
#include <string>
#include <vector>
#include <set>

namespace OCT
{
    namespace CodeGen{
        class API LLKSRD: public IGCodeGeneration
        {
        protected:
        public:
            virtual CodeGenOutput generate(OCT::Parser::GParseNodePtr program) override;
		};
    }
}