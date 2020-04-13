#ifndef imageresizer_h
#define imageresizer_h
#include "PngImage.h"
#include "ImageDistributor.h"
#include "TemplateMatcher.h"
#include "Globals.h"

class ImageResizer{
    private:
        ImageDistributor distr;
        int resizing_data[MAPPINGDATA];
        bool find_block(); //setzt den block in resizing data für find mapping data
        bool find_mapping_data(); //findet aufgrund von resizing data die außenstellen von block aus
        bool resize_input_image();
        int height;
        int width;
        void resize_png_file(int x_start, int y_start, int x_end, int y_end);
    public:
        ImageResizer();
        bool resize();
        ~ImageResizer();
        

};

#endif