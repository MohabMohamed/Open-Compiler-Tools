#include "Chalcedony/Regex/RegexUtility.h"
#include "Chalcedony/Regex/Compiler.h"
#include "Chalcedony/Regex/VM.h"
#include "Chalcedony/InputStream.h"
using namespace CT::Regex;

bool CT::Regex::search(const std::string & regex, const std::string & str, Match & match, std::size_t offset)
{
	InputStreamPtr input = std::make_shared<InputStream>(str);
	input->advance(offset);
	Compiler compiler;
	VM vm;
	for (int i = 0; i < str.size(); i++){
		if (i > 0)
			input->advance(1);
		auto result = vm.exec(compiler.compile(regex), input);
		if (result != StringMarker::invalid)
		{
			match.start = result.start;
			match.end = result.end;
			match.str = result.getString();
			return true;
		}
	}
	return false;
}

bool CT::Regex::match(const std::string & regex, const std::string & str, Match & match)
{
	InputStreamPtr input = std::make_shared<InputStream>(str);
	Compiler compiler;
	VM vm;
	auto result = vm.exec(compiler.compile(regex), input);
	if (result != StringMarker::invalid)
	{
		match.start = result.start;
		match.end = result.end;
		match.str = result.getString();
		return true;
	}

	return false;
}

CT::Regex::Match::Match()
{
	start = 0;
	end = 0;
	str = "";
}
