#pragma once
#include "Defines.h"
#include <memory>
#include <string>
#include <ostream>
namespace CT
{
	class InputStream;
	struct API StringMarker
	{
		const static StringMarker invalid;
		// [start, end)
		s64 start;
		s64 end;
		std::shared_ptr<InputStream> inputStream;
		operator std::string();
		operator std::string() const;
		std::string getString() const;
		std::string getString();
		~StringMarker();

		API friend std::ostream& operator<<(std::ostream& out, const StringMarker& marker);
	};

	API bool operator==(const StringMarker& a, const StringMarker& b);
	API bool operator!=(const StringMarker& a, const StringMarker& b);

	API StringMarker make_string_marker(s64 start, s64 end, std::shared_ptr<InputStream> inputstream);
}