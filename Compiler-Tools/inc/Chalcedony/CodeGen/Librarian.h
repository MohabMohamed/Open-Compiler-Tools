#pragma once

#include "Chalcedony/Defines.h"
#include <cereal/cereal.hpp>
#include <cereal/types/unordered_map.hpp>
#include <cereal/types/string.hpp>
#include <cereal/types/common.hpp>
#include <unordered_map>
#include <string>

namespace CT
{
	namespace CodeGen
	{
		/*
		* This is a Librarian class which is responsible for answering questions about an id
		* also generates an id per lex rule or parse rule 
		*/
		class API Librarian
		{
		public:
			//a map that has all the ids and names of everything inserted in the library
			static std::unordered_map<u32, std::string> m_library;
			static u32 m_ID;
		//public:
			
			bool isLexRule(u32);
			bool isParseRule(u32);
			std::string getName(u32);
			u32 getID(const std::string&);
			u32 getLexID(const std::string&);
			u32 getParseID(const std::string&);

			void addParseRule(const std::string&);
			void addLexRule(const std::string&);

			bool exists(u32);
			bool exists(const std::string&);

			template<class Archive>
			void save(Archive& ar)
			{
				ar(m_ID, m_library);
			}

			template<class Archive>
			void load(Archive& ar)
			{
				ar(m_ID, m_library);
			}
		};
	}
}