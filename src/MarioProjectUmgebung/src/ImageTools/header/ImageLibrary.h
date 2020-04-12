#ifndef imagelibrary_h
#define imagelibrary_h

#include "header/PngImage.h"

class ImageLibrary{
private:
    int mario_img_count;
    int enemy_img_count;
    int item_img_count;
    int block_img_count;
public:
    PngImage *Mario_Images;
    PngImage *Enemy_Images;
    PngImage *Item_Images;
    PngImage *Ground_Images;
    PngImage Input_Img;
    PngImage Resized_Img;
    int return_mario_img_count();
    int return_enemy_img_count();
    int return_item_img_count();
    int return_block_img_count();
    int set_input_image(PngImage input);
    int set_resized_image(PngImage resized);
    ImageLibrary();
    ~ImageLibrary();
};


#endif