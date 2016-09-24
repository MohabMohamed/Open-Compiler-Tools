#pragma once
#include "Chalcedony/Defines.h"
#include "Chalcedony/FilePosition.h"
#include "Chalcedony/StringMarker.h"
#include <string>
#include <memory>
#include <stack>

namespace CT
{
	class API InputStream: public std::enable_shared_from_this<InputStream>
	{
	private:
		std::string m_input;
		std::size_t m_index;
		FilePosition m_position;
		u64 m_lastLineCount;
		std::stack<StringMarker> m_markerStack;

	public:
		InputStream(const std::string& input);

		std::string getString() const;

		char popLetter();

		char peek();

		void rewindLetter();

		void reset();

		void clear();

		bool eof();

		void append(const std::string& str);

		void push(const std::string& str);

		FilePosition getPosition() const;

		void pushMarker(StringMarker marker = StringMarker::invalid);

		StringMarker popMarker();

		StringMarker topMarker();

		std::string requestString(StringMarker marker);
	};
	using InputStreamPtr = std::shared_ptr<InputStream>;

	API InputStreamPtr open_file(const std::string& filename);
	API InputStreamPtr read_stream(std::istream& stream);
	API bool write_file(const std::string& filename, const std::string& content);
}