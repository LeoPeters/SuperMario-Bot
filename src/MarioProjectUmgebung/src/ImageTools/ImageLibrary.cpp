#include "header/ImageLibrary.h"
#include <string>
#include <iostream>
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;

int ImageLibrary::return_mario_img_count(){
    return mario_img_count;
}
int ImageLibrary::return_enemy_img_count(){
    return enemy_img_count;
}
int ImageLibrary::return_item_img_count(){
    return item_img_count;
}
int ImageLibrary::return_block_img_count(){
    return block_img_count;
}

int ImageLibrary::set_input_image(PngImage input){;}

int ImageLibrary::set_resized_image(PngImage resized){;}

//    PngImage Input_Img;
//    PngImage Resized_Img;

ImageLibrary::ImageLibrary() : mario_img_count(0), 
                enemy_img_count(0), item_img_count(0), block_img_count(0){
    const char *path_to_input = "pictures/Input/input.png";
    Input_Img = PngImage(path_to_input);

    std::string path = "pictures/Enemys";
    for (const auto & entry : fs::directory_iterator(path))
        std::cout << entry.path() << std::endl;
}

ImageLibrary::~ImageLibrary(){

}