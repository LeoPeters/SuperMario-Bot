#ifndef isimplifier_h
#define isimplifier_h
#include <vector>
#include <Windows.h>
class ISimplifier {
public:
	virtual bool simplifyImage(std::vector<std::vector<int>>*,HBITMAP image) = 0;
	virtual void init() = 0;
};

#endif