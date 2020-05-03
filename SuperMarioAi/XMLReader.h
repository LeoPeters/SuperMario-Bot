#pragma once
#include <fstream>
#include <regex>

class XMLReader
{
public:
	XMLReader();
	~XMLReader();
	std::string XMLReader::readNextElement();
	void XMLReader::openFile(const std::string fileName);
	bool XMLReader::isFinished();
private:
	std::ifstream inFile;
	std::regex reg;
};

