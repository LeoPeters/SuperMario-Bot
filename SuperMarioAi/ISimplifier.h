#ifndef isimplifier_h
#define isimplifier_h
#include <vector>
#include <Windows.h>
#include "GameState.h"
class ISimplifier {
public:
	virtual GameState simplifyImage(std::vector<std::vector<int>>*,HBITMAP image) = 0;
	virtual void init() = 0;
};

#endif