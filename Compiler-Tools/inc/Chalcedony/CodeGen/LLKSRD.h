#pragma once

#include "Chalcedony/Defines.h"
#include "Chalcedony/CodeGen/IGCodeGeneration.h"
#include "Chalcedony/Parser/GParseTree.h"
#include <tuple>
#include <memory>
#include <ostream>
#include <unordered_map>
#include <map>
#include <string>
#include <vector>
#include <set>

namespace CT
{
    namespace CodeGen{
        class API LLKSRD: public IGCodeGeneration
        {
        protected:
        public:
            virtual CodeGenOutput generate(CT::Parser::GParseNodePtr program) override;
		};
    }
}