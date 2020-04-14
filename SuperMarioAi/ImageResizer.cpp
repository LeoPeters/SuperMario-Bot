#include "ImageResizer.h"
#include <iostream>
   /*     ImageDistributor distr;
        int resizing_data[MAPPINGDATA];
        int find_block(); //setzt den block in resizing data für find mapping data
        int find_mapping_data(); //findet aufgrund von resizing data die außenstellen von block aus
        int resize_input_image(int *mapping);

    public:
        ImageResizer();
        bool resize();*/

/*//unten links bis oben rechts
    for(int y = height-1; y >= 0; y--){
        png_bytep row = resized.row_pointers[y];
        for(int x = 0; x < width ;x++){
            png_bytep px = &(row[(x) * 4]);
            
        }
    }*/

bool ImageResizer::resize(){
    if(find_block()){
        //std::cout<<"FOUND";
        find_mapping_data();
        ImageLibrary* image_library = ImageLibrary::getInstance(); 
        PngImage resizedImage("pictures/Resized/resized.png");
        image_library->set_resized_image(resizedImage);
        return true;
    }
    else{
        std::cout<<"NOTFOUND";
        return false;
        //abort();
    }
}

ImageResizer::ImageResizer(){
    
}

ImageResizer::~ImageResizer(){

}

bool ImageResizer::find_mapping_data(){
    while( resizing_data[X_Start] - TILESIZE >= 0 ){
        resizing_data[X_Start]-=TILESIZE;
    }
    while( resizing_data[Y_Start] - TILESIZE >= 0 ){
        resizing_data[Y_Start]-=TILESIZE;
    }
    while( resizing_data[X_End] + TILESIZE < width ){
        resizing_data[X_End] += TILESIZE;
    }
    while( resizing_data[Y_End] + TILESIZE < height ){
        resizing_data[Y_End] += TILESIZE;
    }
    resize_input_image();
    return false;

}

bool ImageResizer::find_block(){
    PngImage resized = distr.grab_input_img();
    ImageDistributor newdistr;
    TemplateMatcher matcher(resized);
    bool am_i_done = false;
    height = resized.return_height();
    width = resized.return_width();
    int erg = 0;
    int biggest = 0;
    while(true){
        PngImage& rBlock = newdistr.grab_next_block_img(&am_i_done);
        if(am_i_done){break;}
        for(int y = height-TILESIZE; y > 0 ;y--){
            for(int x = 0; x<= width-TILESIZE;x++){
                erg = matcher.match_tilesize_on_pixel(x,y,rBlock);
                if(IS_A_MATCH(erg)){
                    resizing_data[X_Start]=x;
                    resizing_data[Y_Start]=y;
                    resizing_data[X_End]=x+TILESIZE-1;
                    resizing_data[Y_End]=y+TILESIZE-1;
                    return true;
                }
            }
        }
    }
    return false;
}

bool ImageResizer::resize_input_image(){
    resize_png_file(resizing_data[X_Start],resizing_data[Y_Start],resizing_data[X_End],resizing_data[Y_End]);
    return false;
}

void ImageResizer::resize_png_file(int x_start, int y_start, int x_end, int y_end) {
    PngImage input = distr.grab_input_img();
    int new_width = x_end-x_start +1;
    int new_height = y_end-y_start +1;

    //IO Operations
    FILE *fp = fopen("pictures/Resized/resized.png", "wb");
    if(!fp) abort();

    png_structp png = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!png) abort();
    png_infop info = png_create_info_struct(png);
    if (!info) abort();
    if (setjmp(png_jmpbuf(png))) abort();
    png_init_io(png, fp);

    // Output is 8bit depth, RGBA format.
    png_set_IHDR(
        png,
        info,
        new_width, new_height,
        8,
        PNG_COLOR_TYPE_RGBA,
        PNG_INTERLACE_NONE,
        PNG_COMPRESSION_TYPE_DEFAULT,
        PNG_FILTER_TYPE_DEFAULT
    );
    png_write_info(png, info);

    // Init new row pointers
    png_bytep *new_row_pointers = (png_bytep*)malloc(sizeof(png_bytep) * new_height);
    for(int y = 0; y < new_height; y++) {
        new_row_pointers[y] = (png_byte*)malloc(png_get_rowbytes(png,info));
    }
    if (!new_row_pointers) abort();

    //resizing, copy Pixels in Scope
    for(int y = y_start; y <= y_end; y++) {
        png_bytep row = input.row_pointers[y];
        png_bytep new_row = new_row_pointers[y - y_start];
        for(int x = x_start; x <= x_end; x++) {
            png_bytep px = &(row[x * 4]);
            png_bytep new_px = &(new_row[(x - x_start) * 4]);
            // Do something awesome for each pixel here...
            new_px[0] = px[0];
            new_px[1] = px[1];
            new_px[2] = px[2];
            new_px[3] = px[3];
            } 
        }
    //Write
    png_write_image(png, new_row_pointers);
    png_write_end(png, NULL);
    //Clean
    for(int y = 0; y < new_height; y++) {
        free(new_row_pointers[y]); //NOT WORKING?
    }
    free(new_row_pointers);

    png_destroy_write_struct(&png, &info);
    fclose(fp);
}