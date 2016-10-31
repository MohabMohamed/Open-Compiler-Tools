#pragma once

#include "Chalcedony/Defines.h"
#include "Chalcedony/Lexer/Token.h"
#include "Chalcedony/Cartridge.h"
#include "Chalcedony/FilePosition.h"
#include "Chalcedony/InputStream.h"
#include <istream>
#include <vector>
#include <memory>
#include <stack>
#include <functional>

namespace CT
{
	namespace Lexer{

		class API IScanner
		{
		protected:
			std::function<void(InputStreamPtr)> m_errorFunction;
			void callErrorFunction(InputStreamPtr input) {
				if (m_errorFunction != nullptr)
					m_errorFunction(input);
			}
		public:
			virtual ~IScanner()
			{
			}
			virtual Token scan(InputStreamPtr input) = 0;
			virtual void registerToken(CartridgePtr regexProgram,const Token& token) = 0;
			virtual bool isDefinedToken(const std::string&) = 0;
			void setErrorFunction(std::function<void(InputStreamPtr)> errorFunction){m_errorFunction = errorFunction;}
		};
		using IScannerPtr = std::shared_ptr<IScanner>;
	}
}