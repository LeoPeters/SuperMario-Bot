#include "Deathcondition.h"
/*
private:
    ImageLibrary* image_library; // = ImageLibrary::getInstance()
public:
    DeathCond();
    bool return_Is_Dead();
    ~DeathCond();*/

Deathcondition::Deathcondition(){
}

Deathcondition::~Deathcondition() = default;

bool Deathcondition::return_Is_Dead(){
    TemplateMatcher matcher(distr.grab_input_img());
    PngImage& deathscreen = distr.grab_deathscreen_img();
    int erg = matcher.match_tilesize_on_pixel(190,0,deathscreen
                ,deathscreen.return_width(),deathscreen.return_height());
    return IS_A_DEATHSCREEN(erg);
    
}