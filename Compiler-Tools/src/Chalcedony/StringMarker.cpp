#include "Chalcedony/StringMarker.h"
#include "Chalcedony/InputStream.h"
using namespace CT;

const StringMarker StringMarker::invalid = make_string_marker(-1, -1, nullptr);

StringMarker::~StringMarker()
{
	start = -1;
	end = -1;
	inputStream = nullptr;
}

API StringMarker CT::make_string_marker(s64 start, s64 end, InputStreamPtr input)
{
	StringMarker result;
	result.start = start;
	result.end = end;
	result.inputStream = input;
	return result;
}

CT::StringMarker::operator std::string()
{
	return getString();
}

CT::StringMarker::operator std::string() const
{
	return getString();
}

std::string CT::StringMarker::getString() const
{
	if (inputStream) {
		auto koko = inputStream->requestString(*this);
		return koko;
	}
	return "";
}

std::string CT::StringMarker::getString()
{
	if (inputStream) {
		auto koko = inputStream->requestString(*this);
		return koko;
	}
	return "";
}

API std::ostream & CT::operator<<(std::ostream & out, const StringMarker & marker)
{
	out << marker.getString();
	return out;
}

API bool CT::operator==(const StringMarker & a, const StringMarker & b)
{
	return (a.getString() == b.getString());
}

API bool CT::operator!=(const StringMarker & a, const StringMarker & b)
{
	return !(a == b);
}
