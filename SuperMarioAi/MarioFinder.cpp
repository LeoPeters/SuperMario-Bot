#include "MarioFinder.h"
#include "TemplateMatcher.h"
#include "Globals.h"
#include <iostream>
/*class MarioFinder{
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
        bool search_for_Mario(int x_start, int x_end, int y_start, int y_end);
};*/

int MarioFinder::return_x_pos(){
    return x_pos;
}
int MarioFinder::return_y_pos(){
    return y_pos;
}

MarioFinder::MarioFinder(): is_big(false),x_pos(0), y_pos(0), resized(distr.grab_resized_img() ){
}

MarioFinder::~MarioFinder()=default;


bool MarioFinder::search_for_Mario(){
    return (search_for_Mario(0,resized.return_width()-TILESIZE, 0,  resized.return_height()-TILESIZE ));
}

bool MarioFinder::search_for_Mario_in_IMG(int x_start, int x_end, int y_start, int y_end, PngImage& img) {
    TemplateMatcher matcher(img);
    ImageDistributor newdistr;
    bool am_i_done = false;
    int erg = 0;
    int highest = 0;
    //BigMario
    while (true) {
        PngImage& rBlock = newdistr.grab_next_mario_Small_img(&am_i_done);
        if (am_i_done) { break; }
        for (int y = y_start; y < y_end; y++) {// - tilesize_mario_y
            for (int x = x_start; x < x_end ; x++) { //- tilesize_mario_x
                erg = matcher.match_tilesize_on_pixel(x, y, rBlock, tilesize_mario_x, tilesize_mario_y);

                if (IS_A_MARIO_MATCH(erg)) {
                    x_pos = x;
                    y_pos = y;
                    is_big = false;
                    return true;
                }
            }
        }
    }
    //std::cout << max << ",";
    am_i_done = false;
    while (true) {
        PngImage& rBlock = newdistr.grab_next_mario_Shroom_img(&am_i_done);
        if (am_i_done) { break; }
        for (int y = y_start; y < y_end; y++) {// - tilesize_mario_big_y
            for (int x = x_start; x < x_end; x++) {// - tilesize_mario_big_x
                erg = matcher.match_tilesize_on_pixel(x, y, rBlock, tilesize_mario_big_x, tilesize_mario_big_y);

                if (IS_A_BIG_MARIO_MATCH(erg)) {
                    x_pos = x;
                    y_pos = y;
                    is_big = true;
                    return true;
                }
            }
        }
    }
   // std::cout << max << ",";
    am_i_done = false;
    while (true) {
        PngImage& rBlock = newdistr.grab_next_mario_Fire_img(&am_i_done);
        if (am_i_done) { break; }
        for (int y = y_start; y < y_end ; y++) {//- tilesize_mario_big_y
            for (int x = x_start; x < x_end ; x++) {//- tilesize_mario_big_x
                erg = matcher.match_tilesize_on_pixel(x, y, rBlock, tilesize_mario_big_x, tilesize_mario_big_y);
                if (IS_A_BIG_MARIO_MATCH(erg)) {
                    x_pos = x;
                    y_pos = y;
                    is_big = true;
                    return true;
                }
            }
        }
    }

    return false;
}

void MarioFinder::search_for_Mario_threaded(int x_start, int x_end, int y_start, int y_end, bool *boolean){
    *boolean = search_for_Mario(x_start, x_end, y_start, y_end);
}

void MarioFinder::search_for_Mario_threaded_in_input_img(int x_start, int x_end, int y_start, int y_end, bool* boolean) {
    *boolean = search_for_Mario_in_IMG(x_start, x_end, y_start, y_end, distr.grab_input_img());
}

bool MarioFinder::search_for_Mario(int x_start, int x_end, int y_start, int y_end){
    return search_for_Mario_in_IMG(x_start, x_end, y_start, y_end, resized);
}

bool MarioFinder::return_is_big(){
    return is_big;
}