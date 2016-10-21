#include "Chalcedony/InputStream.h"
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

void CT::InputStream::advance(u64 value)
{
	while (--value)
		popLetter();
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
	m_position = FilePosition();
	m_lastLineCount = 0;
	m_markerStack.clear();
}

void CT::InputStream::clear()
{
	m_input.clear();
	reset();
}

bool InputStream::eof(){
	return m_index >= m_input.size();
}

bool CT::InputStream::empty()
{
	return m_input.empty();
}

void InputStream::append(const std::string& str)
{
	m_input += str;
}

void InputStream::push(const std::string& str)
{
	m_input.insert(m_index,str);
}

FilePosition InputStream::getPosition() const{
	return m_position;
}

void CT::InputStream::pushMarker(StringMarker marker)
{
	if (marker == StringMarker::invalid) {
		marker.inputStream = shared_from_this();
		marker.start = m_index;
		marker.end = -1;
		m_markerStack.push_back(marker);
	}
	else {
		marker.end = -1;
		m_markerStack.push_back(marker);
	}
}

StringMarker CT::InputStream::popMarker()
{
	auto marker = m_markerStack.back();
	marker.end = m_index;
	m_markerStack.pop_back();
	return marker;
}

StringMarker CT::InputStream::topMarker()
{
	auto marker = m_markerStack.back();
	marker.end = m_index;
	return marker;
}

bool CT::InputStream::moveToMarkerEnd(const StringMarker & marker)
{
	if (marker == StringMarker::invalid)
		return false;

	if (m_index != marker.end)
	{
		m_index = marker.end;
		return true;
	}
	else
		return false;
	return false;
}

bool CT::InputStream::moveToMarkerStart(const StringMarker & marker)
{
	if (marker == StringMarker::invalid)
		return false;

	if (m_index != marker.start)
	{
		m_index = marker.start;
		return true;
	}
	else
		return false;
	return false;
}

std::string CT::InputStream::requestString(StringMarker marker)
{
	if (marker.start < marker.end)
	{
		return m_input.substr(marker.start, marker.end - marker.start);
	}
	return std::string();
}

std::string::iterator CT::InputStream::currentPositionIt()
{
	return m_input.begin()+m_index;
}

std::string::iterator CT::InputStream::end()
{
	return m_input.end();
}

std::string::iterator CT::InputStream::begin()
{
	return m_input.begin();
}

std::string::const_iterator CT::InputStream::currentPositionConstIt() const
{
	return m_input.begin() + m_index;
}

std::string::const_iterator CT::InputStream::cend() const
{
	return m_input.end();
}

std::string::const_iterator CT::InputStream::cbegin() const
{
	return m_input.begin();
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

API bool CT::write_file(const std::string& filename, const std::string& content)
{
	std::ofstream file(filename);
	if(file.is_open())
	{
		file << content;
	}else{
		return false;
	}
	file.close();
	return true;
}