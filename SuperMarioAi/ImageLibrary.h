#ifndef imagelibrary_h
#define imagelibrary_h
#include <vector>
#include "PngImage.h"

class ImageLibrary{
private:
    
    int mario_Small_img_count;
    int mario_Shroom_img_count;
    int mario_Fire_img_count;
    int enemy_img_count;
    int item_Non_Static_img_count;
    int item_Static_img_count;
    int block_img_count;
    int pipes_img_count;
    int init_vector(const char* pathchar, int* imgcounter, std::vector<PngImage> *vec);

    //For Singleton Desing Pattern
    ImageLibrary();  // Private so that it can  not be called
	ImageLibrary(ImageLibrary const&){};             // copy constructor is private
	ImageLibrary& operator=(ImageLibrary const&){};  // assignment operator is private
	static ImageLibrary* m_pInstance;
    ~ImageLibrary();

public:
    //For Singleton Desing Pattern
    static ImageLibrary* getInstance();

    //PngImage *Mario_Small_Images;
    std::vector <PngImage> Mario_Small_Images;
    //PngImage *Mario_Shroom_Images;
    std::vector <PngImage> Mario_Shroom_Images;
    //PngImage *Mario_Fire_Images;
    std::vector <PngImage> Mario_Fire_Images;
    //PngImage *Enemy_Images;
    std::vector <PngImage> Enemy_Images;
    //PngImage *Item_Static_Images;
    std::vector <PngImage> Item_Static_Images;
    //PngImage *Item_Non_Static_Images;
    std::vector <PngImage> Item_Non_Static_Images;
    //PngImage *Ground_Images;
    std::vector <PngImage> Ground_Images;
    std::vector <PngImage> Pipe_Images;

    PngImage Input_Img;
    PngImage Resized_Img;
    PngImage Deathscreen_Img;

    int return_mario_Small_img_count();
    int return_mario_Shroom_img_count();
    int return_mario_Fire_img_count();
    int return_item_Static_img_count();
    int return_enemy_img_count();
    int return_item_Non_Static_img_count();
    int return_block_img_count();
    int return_pipe_img_count();
    int set_input_image(PngImage input);
    int set_resized_image(PngImage resized);
    //ImageLibrary();
    //~ImageLibrary();
};


#endif