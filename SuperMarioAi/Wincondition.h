#ifndef wincond_h
#define wincond_h
#include "PngImage.h"
#include "Globals.h"
#include "ImageDistributor.h"
#include "TemplateMatcher.h"
class Wincondition{
private:
    ImageDistributor distr;
    int flag_top_x;
    int flag_top_y;
public:
    Wincondition();
    bool search_for_wincond();
    ~Wincondition();
    int return_flag_top_x();
    int return_flag_top_y();
}; 

#endif 