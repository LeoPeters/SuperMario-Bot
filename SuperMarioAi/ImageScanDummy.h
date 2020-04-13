#pragma once
#include "Environment.h"
#include "IImageScan.h"
class ImageScanDummy:public IImageScan
{
public:	
	bool simplifyImage(std::vector <std::vector<int>>* simpleView,HBITMAP image) override;
	ImageScanDummy::ImageScanDummy();
private:
	int calls;
	int pos;
	Environment env;

};

