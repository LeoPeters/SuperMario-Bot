#include "ImageDistributor.h"

PngImage& ImageDistributor::grab_next_mario_Small_img(bool* done){
    return img_grabber(ImgLib_ptr->return_mario_Small_img_count(), 
                                    &tmp_mario_Small_img_count, done,
                                    &ImgLib_ptr->Mario_Small_Images);
}
PngImage& ImageDistributor::grab_next_mario_Shroom_img(bool* done){
    return img_grabber(ImgLib_ptr->return_mario_Shroom_img_count(), 
                                    &tmp_mario_Shroom_img_count, done,
                                    &ImgLib_ptr->Mario_Shroom_Images);
}
PngImage& ImageDistributor::grab_next_mario_Fire_img(bool* done){
    return img_grabber(ImgLib_ptr->return_mario_Fire_img_count(), 
                                    &tmp_mario_Fire_img_count, done,
                                    &ImgLib_ptr->Mario_Fire_Images);
}
PngImage& ImageDistributor::grab_next_enemy_img(bool* done){
    return img_grabber(ImgLib_ptr->return_enemy_img_count(), 
                                    &tmp_enemy_img_count, done, 
                                    &ImgLib_ptr->Enemy_Images);
}

PngImage& ImageDistributor::grab_next_pipe_img(bool* done){
    return img_grabber(ImgLib_ptr->return_pipe_img_count(), 
                                    &tmp_pipe_img_count, done, 
                                    &ImgLib_ptr->Pipe_Images);
}

PngImage& ImageDistributor::grab_next_item_Non_Static_img(bool* done){
    return img_grabber(ImgLib_ptr->return_item_Non_Static_img_count(), 
                                    &tmp_item_Non_Static_img_count, done,
                                    &ImgLib_ptr->Item_Non_Static_Images);
}
PngImage& ImageDistributor::grab_next_item_Static_img(bool* done){
    return img_grabber(ImgLib_ptr->return_item_Static_img_count(),
                                    &tmp_item_Static_img_count, done,
                                    &ImgLib_ptr->Item_Static_Images);
}
PngImage& ImageDistributor::grab_next_block_img(bool* done){
    return img_grabber(ImgLib_ptr->return_block_img_count(), 
                                    &tmp_block_img_count, done,
                                    &ImgLib_ptr->Ground_Images);
}

ImageDistributor::ImageDistributor():tmp_mario_Small_img_count(0), tmp_mario_Shroom_img_count(0),
    tmp_mario_Fire_img_count(0),tmp_enemy_img_count(0),tmp_item_Non_Static_img_count(0),
    tmp_item_Static_img_count(0),tmp_block_img_count(0), tmp_pipe_img_count(0){
    ImgLib_ptr = ImageLibrary::getInstance();
}

ImageDistributor::~ImageDistributor()=default;

PngImage& ImageDistributor::grab_input_img(){
    return ImgLib_ptr->Input_Img;
}

PngImage& ImageDistributor::grab_resized_img(){
    return ImgLib_ptr->Resized_Img;
}

PngImage& ImageDistributor::grab_deathscreen_img(){
    return ImgLib_ptr->Deathscreen_Img;
}

PngImage& ImageDistributor::img_grabber(int max_count, int* counter, bool* done, std::vector<PngImage> *vec){
    if(*counter >= max_count){
            *done = true;
            *counter = 0;
        }
    *counter += 1;
    return vec->at((*counter)-1);
    
}


