#include "Chalcedony/Fluorine/Renderer.h"
#include "Chalcedony/Regex/RegexUtility.h"
#include <iostream>
#include <sstream>
using namespace CT::Fluorine;

void CT::Fluorine::Renderer::subSingles(std::string & str, std::shared_ptr<Data> data)
{
	//init last pos to start the search from
	auto last_pos = 0;
	while (true) {
		//search for single tag
		CT::Regex::Match ms;
		auto single_tag_found = CT::Regex::search("{{[a-zA-Z0-9_]+}}", str, ms, last_pos);
		if (single_tag_found)
		{
			//found single tag
			//update last pos
			auto key = ms.str.substr(2, ms.end - ms.start - 4);
			auto sub_value = data->getSingle(key);
			last_pos = ms.start + sub_value.size();
			//sub the tag
			str.replace(ms.start, ms.end - ms.start, sub_value);
		}
		else {
			break;
		}
	}
}

std::string CT::Fluorine::Renderer::expandMulti(const std::string & str, std::shared_ptr<Data> data, std::size_t index)
{
	std::string result = "";

	//search for multi tag
	CT::Regex::Match ms_start, ms_end;
	auto start_tag_found = CT::Regex::search("{{#[a-zA-Z0-9_]+}}", str, ms_start, index);
	if (start_tag_found)
	{
		//found multi tag and searching for the closing tag
		std::string key = ms_start.str.substr(3, ms_start.end - ms_start.start - 5);
		std::string regex = "{{/" + key + "}}";
		auto end_tag_found = CT::Regex::search(regex, str, ms_end, ms_start.end);
		if (end_tag_found)
		{
			//found a multi region
			//this have splitted the string into 3 regions
			// before multi tag, multi tag region, after multi tag

			//add before multi tag
			result += str.substr(0, ms_start.start);

			//extract the emitted_value
			std::string emitted_value = str.substr(ms_start.end, ms_end.start - ms_start.end);
			//get the sub_data_table
			std::vector<std::shared_ptr<Data>> sub_data_table;
			data->getMulti(key, sub_data_table);
			for (auto sub_data: sub_data_table)
			{
				//add multi tag region
				result += doWork(emitted_value, sub_data);
			}
			//add after multi tag
			result += str.substr(ms_end.end, str.size() - ms_end.end);
		}
	}
	else {
		return str;
	}
	return result;
}

std::string CT::Fluorine::Renderer::doWork(std::string & str, std::shared_ptr<Data> data)
{
	std::string result = expandMulti(str, data, 0);
	subSingles(result, data);
	return result;
}

std::string Renderer::render(const std::string& str, std::shared_ptr<Data> data)
{
	return doWork(const_cast<std::string&>(str), data);
}

void CT::Fluorine::Data::addSingle(const std::string & key, const std::string & value)
{
	m_singleTable[key] = value;
}

void CT::Fluorine::Data::addMulti(const std::string & key, std::shared_ptr<Data> table)
{
	table->m_parent = shared_from_this();
	m_multiTables[key].push_back(table);
}

std::string CT::Fluorine::Data::getSingle(const std::string & key)
{
	auto result_it = m_singleTable.find(key);
	if (result_it != m_singleTable.end())
		return result_it->second;
	if (m_parent)
		return m_parent->getSingle(key);
	return "";
}

void CT::Fluorine::Data::getMulti(const std::string & key, std::vector<std::shared_ptr<Data>>& out)
{
	auto result_it = m_multiTables.find(key);
	if (result_it != m_multiTables.end()) {
		out = result_it->second;
		return;
	}
	if (m_parent)
	{
		m_parent->getMulti(key, out);
		return;
	}
	return;
}
