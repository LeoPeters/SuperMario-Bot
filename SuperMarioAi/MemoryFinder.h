#pragma once
#include <string>
#include <vector>
class MemoryFinder
{
public:

	 std::vector<std::string> getAllMemoryNames();
	 std::string getDirectoryPath();
private:
	 std::string directioryPath = ".\\memory\\";
	 std::string searchingString = directioryPath + "*.xml";
};

