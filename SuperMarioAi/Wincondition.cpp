#include "Wincondition.h"
/*
private:
    ImageLibrary* image_library; // = ImageLibrary::getInstance()
public:
    DeathCond();
    bool return_Is_Dead();
    ~DeathCond();*/

Wincondition::Wincondition():flag_top_x(0),flag_top_y(0){
}

Wincondition::~Wincondition() = default;

bool Wincondition::search_for_wincond(){
    TemplateMatcher matcher(distr.grab_resized_img());
    PngImage& flagpole = distr.grab_flagpole_img();
    int height = distr.grab_resized_img().return_height();
    int width = distr.grab_resized_img().return_width();
    int erg = 0;
    int max = 0;
    for(int y = 32; y<42;y++){
        for(int x = 90; x < width-TILESIZE;x++){ //war vorher 120 das x
            erg = matcher.match_tilesize_on_pixel(x,y,flagpole
                ,flagpole.return_width(),flagpole.return_height());
            if(max<erg){
                max=erg;
                if(IS_A_FLAGPOLE(max)){
                    flag_top_x=x;
                    flag_top_y=y;
                    return true;
                }
            }
        }
    }
    return false;
    
}

int Wincondition::return_flag_top_x(){
    return flag_top_x;
}

int Wincondition::return_flag_top_y(){
    return flag_top_y;
}