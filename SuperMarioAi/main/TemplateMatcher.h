#ifndef templatematcher_h
#define templatematcher_h
#include "PngImage.h"
class TemplateMatcher{
private:
    PngImage* input_ptr;
public:
    TemplateMatcher(PngImage& input);
    int match_tilesize_on_pixel(int x_pos, int y_pos, PngImage sprite);
    int match_tilesize_on_pixel(int x_pos, int y_pos, PngImage sprite, int tilesize_X, int tilesize_Y);
    ~TemplateMatcher();
};

#endif