#ifndef simplifierDummy_h
#define simplifierDummy_h
#include "Environment.h"
#include "ISimplifier.h"
class SimplifierDummy:public ISimplifier
{
public:	
	bool simplifyImage(std::vector <std::vector<int>>* simpleView,HBITMAP image) override;
	void init() override;
private:
	int calls;
	int pos;
	Environment* env;

};

#endif
