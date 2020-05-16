 #include "XMLReader.h"
#include <iostream>
#include <istream>
#include <fstream>
#include <string>

XMLReader::XMLReader() :
	reg(">.*</")
{

}

XMLReader::~XMLReader()
{

}


void XMLReader::openFile(const std::string fileName)
{
	std::string temp;
	inFile.open(fileName);
	std::getline(inFile, temp);
	std::getline(inFile, temp);
}

std::string XMLReader::readNextElement()
{
	std::string temp;
	std::smatch match;

	do {
		std::getline(inFile, temp);
		std::regex_search(temp, match, reg);
		if (isFinished())
		{
			return "";
		}
	} while (match.size() == 0);
	temp = match.str();
	temp = temp.substr(1, temp.size() - 3);
	return temp;
}

bool XMLReader::isFinished()
{
	return inFile.eof();
}