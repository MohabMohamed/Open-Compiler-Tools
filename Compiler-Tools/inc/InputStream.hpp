#pragma once
#include "Defines.h"
#include <string>

namespace CT
{
	template<typename letterType>
	class InputStream
	{
	};

	//ASCII char input
	template<>
	class InputStream<char>
	{
	private:
		std::string m_input;
		std::size_t m_index;
	public:
		InputStream(std::string input)
		:m_input(input), m_index(0)
		{

		}

		std::string getString() const
		{
			return m_input;
		}

		char popLetter()
		{
			if(m_index >= m_input.size())
				return '\0';
			return m_input[m_index++];
		}

		void rewindLetter(){
			if(m_index > 0)
				m_index--;
		}

		void reset(){
			m_index=0;
		}

		bool eof(){
			return m_index >= m_input.size();
		}
	};

	//unicode char input
	template<>
	class InputStream<wchar_t>
	{
	private:
		std::wstring m_input;
		std::size_t m_index;
	public:
		InputStream(std::wstring input)
		:m_input(input), m_index(0)
		{

		}

		std::wstring getString() const
		{
			return m_input;
		}

		wchar_t popLetter()
		{
			if(m_index >= m_input.size())
				return '\0';
			return m_input[m_index++];
		}

		void rewindLetter(){
			if(m_index > 0)
				m_index--;
		}

		void reset(){
			m_index=0;
		}

		bool eof(){
			return m_index >= m_input.size();
		}
	};
}