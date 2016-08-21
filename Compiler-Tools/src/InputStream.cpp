#include "InputStream.h"
#include <fstream>
using namespace CT;

InputStream::InputStream(const std::string& input)
:m_input(input), m_index(0), m_lastLineCount(0)
{}

std::string InputStream::getString() const
{
	return m_input;
}

char InputStream::popLetter()
{
	if(m_index >= m_input.size())
		return '\0';
	if(m_input[m_index] == '\n'){
		m_position.row++;
		m_lastLineCount = m_position.col;
		m_position.col = 0;
	}else{
		m_position.col++;
	}
	return m_input[m_index++];
}

char InputStream::peek()
{
	if(m_index >= m_input.size())
		return '\0';
	return m_input[m_index];
}

void InputStream::rewindLetter(){
	if(m_index > 0){
		if(m_input[m_index] == '\n')
		{
			m_position.row--;
			m_position.col = m_lastLineCount;
		}else{
			m_position.col--;
		}
		m_index--;
	}
}

void InputStream::reset(){
	m_index=0;
	m_position = Position();
	m_lastLineCount = 0;
}

bool InputStream::eof(){
	return m_index >= m_input.size();
}

void InputStream::append(const std::string& str)
{
	m_input += str;
}

void InputStream::push(const std::string& str)
{
	m_input.insert(m_index,str);
}

Position InputStream::getPosition() const{
	return m_position;
}

API InputStreamPtr CT::open_file(const std::string& filename)
{
	std::ifstream file(filename, std::ios_base::in | std::ios_base::ate);
	auto size = file.tellg();
	file.seekg(0, std::ios_base::beg);
	file.clear();
	std::string str(size, '\0');
	file.read(&str[0], size);
	file.close();
	return std::make_shared<InputStream>(str);
}

API InputStreamPtr CT::read_stream(std::istream& stream)
{
	auto result = std::make_shared<InputStream>("");
	std::string line(1024, '\0');
	bool addNewLine = false;
	while(std::getline(stream, line))
	{
		if (addNewLine)
			result->append("\n" + line);
		else
		{
			result->append(line);
			addNewLine = true;
		}
	}
	return result;
}