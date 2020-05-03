#pragma once
#include <string>
#include <vector>

const static std::string directoryPath = ".\\saves\\";

class MemoryFinder
{
public:
	 std::vector<std::string> getAllMemoryNames();
	 static std::string getDirectoryPath();
private:
	
	 std::string searchingString = directoryPath + "*.xml";
};

