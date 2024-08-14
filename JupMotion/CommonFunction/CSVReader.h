#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

/*
	–¥»ÎHeader
	CSVReader file("c:/1.csv");
	std::vector<std::string> header = {"1", "2", "3", "4"};
	file.addRow(header);

	std::vector<std::string> oneLine;
	oneLine.push_back("a");
	oneLine.push_back("b");
	oneLine.push_back("c");
	oneLine.push_back("d");
	file.addRow(oneLine);

	// append
	file.writeToFile(eWriteMode::eAppend);

	// eTruncate
	file.writeToFile(eWriteMode::eTruncate);
*/

class CSVReader
{
	enum eWriteMode
	{
		eTruncate = 0,
		eAppend = 1,
	};

public:
	CSVReader(const std::string& filename);
	~CSVReader();
	bool writeToFile(eWriteMode eMode = eTruncate);
	void readFromFile();
	const std::vector<std::vector<std::string>>& getData();
	void addRow(const std::vector<std::string>& row);
private:
	void readCSV();
	bool writeCSV(eWriteMode eMode);
private:
	std::string m_filename;
	std::vector<std::vector<std::string>> m_data;
};