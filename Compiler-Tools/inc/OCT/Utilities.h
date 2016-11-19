#pragma once
#include "OCT/Defines.h"
#include <string>
#include <functional>
#include <algorithm>
#include <cctype>

namespace OCT
{
	class API IDGenerator
	{
	public:
		static s64 generateID();
		static s64 generateIDLib();
		static const u64 invalid = 0xFFFFFFFFFFFFFFFF;
	};

	//for linux g++ because it can't hash the enum
	struct EnumClassHash
	{
		template<typename T>
		std::size_t operator()(T t) const
		{
			return static_cast<std::size_t>(t);
		}
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

	static inline std::string indent(u32 t) {
		return std::string(t, '\t');
	}

}