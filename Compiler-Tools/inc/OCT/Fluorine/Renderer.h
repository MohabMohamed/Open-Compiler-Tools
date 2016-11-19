#pragma once

#include "OCT/Defines.h"
#include <vector>
#include <map>
#include <string>
#include <memory>

namespace OCT
{
	namespace Fluorine
	{
		class API Data: public std::enable_shared_from_this<Data> {
		public:

			void addSingle(const std::string& key, const std::string& value);
			void addMulti(const std::string& key, std::shared_ptr<Data> table);

			std::string getSingle(const std::string& key);
			void getMulti(const std::string& key, std::vector<std::shared_ptr<Data>>& out);
		private:
			std::map<std::string, std::string> m_singleTable;
			std::map<std::string, std::vector<std::shared_ptr<Data>>> m_multiTables;
			std::shared_ptr<Data> m_parent = nullptr;
		};
		using DataPtr = std::shared_ptr<Data>;

		class API Renderer
		{
			void subSingles(std::string& str, std::shared_ptr<Data> data);
			std::string expandMulti(const std::string& str, std::shared_ptr<Data> data, std::size_t index);
			std::string doWork(std::string& str, std::shared_ptr<Data> data);
		public:
			std::string render(const std::string& str, std::shared_ptr<Data> data);
		};
	}
}