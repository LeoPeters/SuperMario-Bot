#include "Environment.h"
#include "PngImage.h"
#include "ImageLibrary.h"
#include "ImageDistributor.h"
#include "ImageResizer.h"
#include "Mapper.h"
#include "TemplateMatcher.h"
#include "MarioFinder.h"
#include <iostream>
#include <chrono>
#include <ctime>  


int Environment::environment_interface(const char* filename, int arr[GRIDRADIUS][GRIDRADIUS]){
    PngImage inp(filename);
    give_Input(inp,arr);
    return 0;
}

//constructor
Environment::Environment(){
    image_library = ImageLibrary::getInstance(); 
}

Environment::~Environment(){

}

int Environment::give_Input(PngImage& new_input,int arr[GRIDRADIUS][GRIDRADIUS]){
    image_library->set_input_image(new_input);
    auto start = std::chrono::system_clock::now();
    if(resize.resize()){
        
        if(mapper.Map_Mario()){
            //printf("mario found\n");
            
            mapper.Map_Enemys_Threaded();
            mapper.Map_Blocks_Threaded();
            mapper.Map_Items_Threaded();
            //mapper.print_erg_radius();

            //return array test
            mapper.return_erg_array(arr);
            //printf("\n");
            //for(int y = 0; y<GRIDRADIUS;y++){
            //    for(int x= 0; x<GRIDRADIUS;x++){
            //        printf("%d ",arr[x][y]);
            //    }
            //    printf("\n");
            //}
            //printf("\n");
            auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);
    std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";
        }
        else{
            return -1;
        }
    
    }
    return -1;
}
