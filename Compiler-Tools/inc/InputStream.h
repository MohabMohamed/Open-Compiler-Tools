#pragma once
#include "Defines.h"
#include <string>

namespace CT
{
	class InputStream
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
}