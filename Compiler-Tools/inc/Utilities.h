#pragma once
#include "Defines.h"
#include <string>
#include <functional>
#include <algorithm>
#include <cctype>

namespace CT
{
	class API IDGenerator
	{
	public:
		static u64 generateID();
		static const u64 invalid = 0xFFFFFFFFFFFFFFFF;
	};

	// trim from start
	static inline std::string &ltrim(std::string &s) {
		s.erase(s.begin(), std::find_if(s.begin(), s.end(),
			std::not1(std::ptr_fun<int, int>(std::isspace))));
		return s;
	}

	// trim from end
	static inline std::string &rtrim(std::string &s) {
		s.erase(std::find_if(s.rbegin(), s.rend(),
			std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
		return s;
	}

	// trim from both ends
	static inline std::string &trim(std::string &s) {
		return ltrim(rtrim(s));
	}

}