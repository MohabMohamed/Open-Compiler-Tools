#pragma once
#include "Defines.h"
#include <unordered_map>
#include <string>
#include <vector>
#include "Position.h"

namespace CT
{
	enum class LOG_LEVEL: u8 {COUT, LOG, ERROR};

	struct API LogEntry
	{
		LOG_LEVEL level;
		std::string message;
		Position position;
	};

	class API Log
	{
	private:
		static std::unordered_map<LOG_LEVEL, std::vector<LogEntry>> m_logEntries;
	public:

		static std::unordered_map<LOG_LEVEL, std::vector<LogEntry>> getLogEntries();

		static std::string getLogText();

		static void dumpLogEntriesToFile(std::string filename);

		static void log(LOG_LEVEL,const std::string& message, Position position);
	};
}
