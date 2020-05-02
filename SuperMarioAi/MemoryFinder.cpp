#include <windows.h>
#include "MemoryFinder.h"

 std::vector<std::string> MemoryFinder::getAllMemoryNames()
{
	WIN32_FIND_DATAA wdf;
	HANDLE handle;
	std::vector<std::string> fileNames;
	handle=FindFirstFileA(searchingString.c_str(),&wdf);
	if(handle!= INVALID_HANDLE_VALUE){
	do {
		fileNames.push_back (wdf.cFileName);
	}while (FindNextFileA(handle, &wdf));
	}
	return fileNames;
}

 std::string MemoryFinder::getDirectoryPath()
 {
	 return directioryPath;
 }
