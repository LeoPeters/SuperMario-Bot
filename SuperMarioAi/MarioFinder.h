#ifndef MarioFinder_h
#define MarioFinder_h
#include "PngImage.h"
#include "ImageDistributor.h"

class MarioFinder {
private:
    ImageDistributor distr;
    PngImage& resized;
    int x_pos;
    int y_pos;
    bool is_big;
public:
    MarioFinder();
    ~MarioFinder();
    bool search_for_Mario();
    bool search_for_Mario_in_IMG(int x_start, int x_end, int y_start, int y_end, PngImage& img);
    bool search_for_Mario(int x_start, int x_end, int y_start, int y_end);
    void search_for_Mario_threaded(int x_start, int x_end, int y_start, int y_end, bool* boolean);
    void search_for_Mario_threaded_in_input_img(int x_start, int x_end, int y_start, int y_end, bool* boolean);
    int return_x_pos();
    int return_y_pos();
    bool return_is_big();
    bool search_for_Mario_on_grid(int gridx, int gridy);
};

#endif