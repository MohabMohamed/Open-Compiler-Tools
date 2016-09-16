#pragma once
#include "Defines.h"
#include "Position.h"
#include <string>
#include <memory>

namespace CT
{
	class API InputStream
	{
	private:
		std::string m_input;
		std::size_t m_index;
		Position m_position;
		u64 m_lastLineCount;
	public:
		InputStream(const std::string& input);

		std::string getString() const;

		char popLetter();

		char peek();

		void rewindLetter();

		void reset();

		bool eof();

		void append(const std::string& str);

		void push(const std::string& str);

		Position getPosition() const;
	};
	using InputStreamPtr = std::shared_ptr<InputStream>;

	API InputStreamPtr open_file(const std::string& filename);
	API InputStreamPtr read_stream(std::istream& stream);
	API bool write_file(const std::string& filename, const std::string& content);
}