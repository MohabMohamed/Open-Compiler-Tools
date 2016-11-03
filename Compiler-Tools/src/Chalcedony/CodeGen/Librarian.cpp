#include "Chalcedony/CodeGen/Librarian.h"
using namespace CT;
using namespace CT::CodeGen;

std::unordered_map<u32, std::string> Librarian::m_library;
u32 Librarian::m_ID = 0;

bool Librarian::isLexRule(u32 id)
{
	return 0x40000000 & id;
}

bool Librarian::isParseRule(u32 id)
{
	return 0x80000000 & id;
}

std::string Librarian::getName(u32 id)
{
	auto library_it = m_library.find(id);
	if(library_it != m_library.end())
		return library_it->second;
	return "";
}

u32 Librarian::getID(const std::string& name)
{
	for(auto& entry: m_library)
	{
		if(entry.second == name)
			return entry.first;
	}
	return 0;
}

u32 Librarian::getLexID(const std::string& name)
{
	for (auto& entry : m_library)
	{
		if (entry.second == name && isLexRule(entry.first))
			return entry.first;
	}
	return 0;
}

u32 Librarian::getParseID(const std::string& name)
{
	for (auto& entry : m_library)
	{
		if (entry.second == name && isParseRule(entry.first))
			return entry.first;
	}
	return 0;
}

void Librarian::addParseRule(const std::string& name)
{
	auto id = m_ID;
	m_ID++;
	u32 maskedValue = 0xcFFFFFFF & id;
	maskedValue |= 0x80000000;
	m_library.emplace(maskedValue, name); 
}
void Librarian::addLexRule(const std::string& name)
{
	auto id = m_ID;
	m_ID++;
	u32 maskedValue = 0xcFFFFFFF & id;
	maskedValue |= 0x40000000;
	m_library.emplace(maskedValue, name);
}

bool Librarian::exists(u32 id)
{
	auto result = getName(id);
	return !result.empty();
}

bool Librarian::exists(const std::string& name)
{
	auto result = getID(name);
	return result != 0;
}