#include "TemplateMatcher.h"
#include "Globals.h"


TemplateMatcher::~TemplateMatcher()=default;

int TemplateMatcher::match_tilesize_on_pixel(int x_pos, int y_pos, PngImage sprite){
    return match_tilesize_on_pixel(x_pos,y_pos,sprite,TILESIZE,TILESIZE);
}

int TemplateMatcher::match_tilesize_on_pixel(int x_pos, int y_pos, PngImage sprite, int tilesize_X, int tilesize_Y){
    int matchings = 0;
    for(int y = 0; y < tilesize_Y; y++){
            png_bytep img_row = input_ptr->row_pointers[y_pos+y];
            png_bytep sprite_row = sprite.row_pointers[y];
            for(int x = 0; x < tilesize_X;x++){
                    png_bytep impx = &(img_row[(x_pos+x) * 4]);
                    png_bytep sppx = &(sprite_row[x * 4]);
                    //Compare   
                    /*if(x_pos == 5*TILESIZE && y_pos==11*TILESIZE){
                    printf("A-WITH: %4d, %4d = RGBA(%3d, %3d, %3d, %3d)\n", x_pos+x, y_pos+y, impx[0], impx[1], impx[2], impx[3]);
                    printf("B-WITH: %4d, %4d = RGBA(%3d, %3d, %3d, %3d)\n", x, y, sppx[0], sppx[1], sppx[2], sppx[3]);} */
                    if( ((impx[0])+ABWEICHUNG) >= sppx[0] && sppx[0] >= ((impx[0])-ABWEICHUNG) ){
                        if( ((impx[1])+ABWEICHUNG) >= sppx[1] && sppx[1] >= ((impx[1])-ABWEICHUNG) ){
                            if(((impx[2])+ABWEICHUNG) >= sppx[2] && sppx[2] >= ((impx[2])-ABWEICHUNG)){
                                matchings++;
                            }
                        }
                    }
            }
    }
    return matchings;
}
TemplateMatcher::TemplateMatcher(PngImage& input){
    input_ptr = &input;
}