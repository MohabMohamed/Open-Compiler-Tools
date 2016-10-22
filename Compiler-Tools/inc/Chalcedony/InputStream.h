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
	public:
		std::string m_input;
		std::size_t m_index;
		FilePosition m_position;
		u64 m_lastLineCount;
		std::stack<StringMarker> m_markerStack;

	public:
		InputStream(const std::string& input);

		std::string getString() const;

		char popLetter();

		void advance(u64 value);

		char peek();

		void rewindLetter();

		void reset();

		void clear();

		bool eof();

		bool empty();

		void append(const std::string& str);

		void push(const std::string& str);

		FilePosition getPosition() const;

		void pushMarker(StringMarker marker = StringMarker::invalid);

		StringMarker popMarker();

		StringMarker topMarker();

		bool moveToMarkerEnd(const StringMarker& marker);

		bool moveToMarkerStart(const StringMarker& marker);

		std::string requestString(StringMarker marker);

		std::string::iterator currentPositionIt();

		std::string::iterator end();

		std::string::iterator begin();

		std::string::const_iterator currentPositionConstIt() const;

		std::string::const_iterator cend() const;

		std::string::const_iterator cbegin() const;
	};
	using InputStreamPtr = std::shared_ptr<InputStream>;

	API InputStreamPtr open_file(const std::string& filename);
	API InputStreamPtr read_stream(std::istream& stream);
	API bool write_file(const std::string& filename, const std::string& content);
}