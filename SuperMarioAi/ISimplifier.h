#pragma once
#include <vector>
#include <Windows.h>
class ISimplifier {
public:
	virtual bool simplifyImage(std::vector<std::vector<int>>*,HBITMAP image) = 0;
};
