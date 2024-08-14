#include "CSVReader.h"


CSVReader::CSVReader(const std::string & filename)
{
	m_filename = filename;
}

CSVReader::~CSVReader()
{
}

bool CSVReader::writeToFile(eWriteMode eMode)
{
	return writeCSV(eMode);
}

void CSVReader::readFromFile()
{
	readCSV();
}

const std::vector<std::vector<std::string>>& CSVReader::getData()
{
	return m_data;
}

void CSVReader::readCSV()
{
	std::ifstream file(m_filename);
	std::string line;
	std::vector<std::string> row;
	if (!file.is_open())
		return;

	while (std::getline(file, line))
	{
		std::stringstream ss(line);
		std::string cell;
		row.clear();
		while (std::getline(ss, cell, ',')) 
		{
			row.push_back(cell);
		}
		m_data.push_back(row);
	}
}

bool CSVReader::writeCSV(eWriteMode eMode)
{
	int mode = 0;
	if (eMode == eWriteMode::eAppend)
	{
		mode = std::ofstream::out | std::ofstream::app;
	}
	else
	{
		mode = std::ofstream::out | std::ofstream::trunc;
	}

	std::ofstream file(m_filename, mode);
	if (!file.is_open())
		return false;

	for (const auto& row : m_data)
	{
		for (size_t i = 0; i < row.size(); ++i)
		{
			file << row[i];
			if (i < row.size() - 1) file << ",";
		}
		file << "\n";
	}
}

void CSVReader::addRow(const std::vector<std::string>& row)
{
	m_data.push_back(row);
}
