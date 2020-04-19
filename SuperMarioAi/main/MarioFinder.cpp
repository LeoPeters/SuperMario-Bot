#include "MarioFinder.h"
#include "TemplateMatcher.h"
#include "Globals.h"
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
    //resized = distr.grab_resized_img();
}

MarioFinder::~MarioFinder()=default;


bool MarioFinder::search_for_Mario(){
    return (search_for_Mario(0,resized.return_width()-TILESIZE, 0,  resized.return_height()-TILESIZE ));
}

void MarioFinder::search_for_Mario_threaded(int x_start, int x_end, int y_start, int y_end, bool *boolean){
    /*if(y_end>=resized.return_height()-tilesize_mario_big_y-1){
        y_end=resized.return_height()-tilesize_mario_big_y-2;
    }
    if(x_end>=resized.return_width()-tilesize_mario_big_x){
        x_end=resized.return_width()-tilesize_mario_big_x-2;
    }*/
    *boolean = search_for_Mario(x_start, x_end, y_start, y_end);
}

bool MarioFinder::search_for_Mario(int x_start, int x_end, int y_start, int y_end){
    TemplateMatcher matcher(resized);
    bool am_i_done = false;
    int erg = 0;
    int highest = 0;
    while(true){
        PngImage& rBlock = distr.grab_next_mario_Small_img(&am_i_done);
        if(am_i_done){break;}
        for(int y = y_start; y < y_end-tilesize_mario_y;y++){
            for(int x = x_start; x < x_end-tilesize_mario_x;x++){
                erg = matcher.match_tilesize_on_pixel(x,y,rBlock, tilesize_mario_x, tilesize_mario_y);
                if(IS_A_MARIO_MATCH(erg)){
                    x_pos=x;
                    y_pos=y;
                    is_big=false;
                    return true;
                }
            }
        }
    }
    //BigMario
    am_i_done=false;
    while(true){
        PngImage& rBlock = distr.grab_next_mario_Shroom_img(&am_i_done);
        if(am_i_done){break;}
        for(int y = y_start; y < y_end-tilesize_mario_big_y;y++){
            for(int x = x_start; x < x_end-tilesize_mario_big_x;x++){
                erg = matcher.match_tilesize_on_pixel(x,y,rBlock, tilesize_mario_big_x, tilesize_mario_big_y);
                if(IS_A_BIG_MARIO_MATCH(erg)){
                    x_pos=x;
                    y_pos=y;
                    is_big=true;
                    return true;
                }
            }
        }
    }
    am_i_done=false;
    while(true){
        PngImage& rBlock = distr.grab_next_mario_Fire_img(&am_i_done);
        if(am_i_done){break;}
        for(int y = y_start; y < y_end-tilesize_mario_big_y;y++){
            for(int x = x_start; x < x_end-tilesize_mario_big_x;x++){
                erg = matcher.match_tilesize_on_pixel(x,y,rBlock, tilesize_mario_big_x, tilesize_mario_big_y);
                if(IS_A_BIG_MARIO_MATCH(erg)){
                    x_pos=x;
                    y_pos=y;
                    is_big=true;
                    return true;
                }
            }
        }
    }
    return false;
}

bool MarioFinder::return_is_big(){
    return is_big;
}