#pragma once
#include "OCT/Defines.h"
#include "OCT/Utilities.h"
#include "OCT/FilePosition.h"
#include <unordered_map>
#include <string>
#include <vector>

namespace OCT
{
	enum class LOG_LEVEL: u8 {COUT, LOG, ERROR, LDEBUG};

	struct API LogEntry
	{
		LOG_LEVEL level;
		std::string message;
		FilePosition position;
	};

	class API Log
	{
	private:
		static std::unordered_map<LOG_LEVEL, std::vector<LogEntry>, EnumClassHash> m_logEntries;
		static std::unordered_map<LOG_LEVEL, std::vector<LogEntry>, EnumClassHash> m_commitedEntries;
	public:

		static std::unordered_map<LOG_LEVEL, std::vector<LogEntry>, EnumClassHash> getLogEntries();

		static std::string getLogText();

		static std::string filterLog(LOG_LEVEL level);

		static void dumpLogEntriesToFile(std::string filename);

		static void log(LOG_LEVEL,const std::string& message, FilePosition position);

		static void commitEntry(LOG_LEVEL, const std::string& message, FilePosition position);

		static void pushEntries();

		static void discardCommittedEntries();
	};
}
