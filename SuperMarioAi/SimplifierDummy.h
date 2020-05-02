#ifndef simplifierDummy_h
#define simplifierDummy_h
#include "Environment.h"
#include "ISimplifier.h"
class SimplifierDummy:public ISimplifier
{
public:	
	GameState simplifyImage(std::vector <std::vector<int>>* simpleView) override;
	void init() override;
private:
	int calls;
	int pos;
	Environment* env;

};

#endif
