#pragma once
#include <vector>
#include <Windows.h>

class IImageScan {
public:
	virtual bool simplifyImage(std::vector<std::vector<int>>*, HBITMAP image) = 0;
};
