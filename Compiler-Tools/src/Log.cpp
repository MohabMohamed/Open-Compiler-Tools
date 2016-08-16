#include "Log.h"
#include <fstream>
#include <sstream>
using namespace CT;

std::unordered_map<LOG_LEVEL, std::vector<LogEntry>> Log::m_logEntries;

std::unordered_map<LOG_LEVEL, std::vector<LogEntry>> Log::getLogEntries()
{
	return m_logEntries;
}

std::string Log::getLogText()
{
	std::stringstream stream;

	for(auto item: m_logEntries)
	{
		switch (item.first)
		{
		case LOG_LEVEL::COUT:
			for (auto entry : item.second)
				stream << entry.message << std::endl;
			break;
		case LOG_LEVEL::LOG: 
			for (auto entry : item.second)
			{
				stream << "[Log";
				if (entry.position.isValid)
					stream << ", " << entry.position.col << ", " << entry.position.row;
				stream << "]: ";
				stream << entry.message << std::endl;
			}
			break;
		case LOG_LEVEL::ERROR:
			for (auto entry : item.second)
			{
				stream << "[Error";
				if (entry.position.isValid)
					stream << ", " << entry.position.col << ", " << entry.position.row;
				stream << "]: ";
				stream << entry.message << std::endl;
			}
			break;
		default: 
		break;
		}
	}
	return stream.str();
}

void Log::dumpLogEntriesToFile(std::string filename)
{
	std::ofstream file(filename);
	if(file.is_open())
	{
		file << getLogText();
		file.close();
	}
}

void Log::log(LOG_LEVEL level,const std::string& message, Position position)
{
	LogEntry entry;
	entry.message = message;
	entry.level = level;
	entry.position = position;
	m_logEntries[level].push_back(entry);
}