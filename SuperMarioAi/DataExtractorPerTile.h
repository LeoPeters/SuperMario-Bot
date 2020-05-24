#pragma once

#define LABELS 6
#include "Globals.h"
#include <string>
#include "ImageResizer.h"
#include "ImageDistributor.h"

class DataExtractorPerTile
{
private:
	int counts[LABELS];
	int returnDirCount(const char* directory);
	std::string return_name(int num);
	ImageResizer resizer;
	ImageDistributor distr;
	bool is_finished();
public:
	DataExtractorPerTile();
	~DataExtractorPerTile() = default;
	bool createTrainDataFromArray(int ergarray[GRIDRADIUS][GRIDRADIUS]);

	
	
};

