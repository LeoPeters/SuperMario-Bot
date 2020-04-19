#ifndef deathcond_h
#define deathcond_h
#include "PngImage.h"
#include "Globals.h"
#include "ImageDistributor.h"
#include "TemplateMatcher.h"
class Deathcondition{
private:
    ImageDistributor distr;
public:
    Deathcondition();
    bool return_Is_Dead();
    ~Deathcondition();
}; 

#endif 