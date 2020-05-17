#include "Environment.h"
#include "PngImage.h"
#include "ImageLibrary.h"
#include "ImageDistributor.h"
#include "ImageResizer.h"
#include "Mapper.h"
#include "TemplateMatcher.h"
#include "MarioFinder.h"
#include "Deathcondition.h"
#include <iostream>
#include <chrono>
#include <ctime>  


int Environment::environment_interface(const char* filename, int arr[GRIDRADIUS][GRIDRADIUS], int* status){
    PngImage inp(filename);
    //auto start = std::chrono::system_clock::now();
    // Some computation here
    give_Input(inp,arr,status);
  //  auto end = std::chrono::system_clock::now();
    /*
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);

    std::cout << "finished computation at " << std::ctime(&end_time)
        << "elapsed time: " << elapsed_seconds.count() << "s\n";*/
    return 0;
}



//constructor
Environment::Environment(): traindata(), trainingflag(false){
    image_library = ImageLibrary::getInstance(); 
}

Environment::~Environment()=default;

int Environment::give_Input(PngImage& new_input,int arr[GRIDRADIUS][GRIDRADIUS], int* status){
    image_library->set_input_image(new_input);
    if(resize.resize()){
        if(mapper.Map_Mario()){
            mapper.Map_Enemys_Threaded();
            mapper.Map_Blocks_Threaded();
            mapper.Map_Items_Threaded();
            if(mapper.Map_Winning_Conditions_Threaded()){
                *status = GEWONNEN;
            }
            mapper.return_erg_array(arr);
            mem_arr.push_in_memory_array(arr);
            mem_arr.set_first_not_found(true);

            if (trainingflag) {
                if (!traindata.write_array_to_data_file(arr)) {
                    trainingflag = false;
                }
            }

            return 0;
        }
        else{
            if (mem_arr.return_first_not_found()) {
                mem_arr.set_first_not_found(false);
                if (mem_arr.retrieve_last_enemy_memory(arr) == false) {
                    *status = NOT_FOUND;
                    return -1;
                }
                //TODO maybe gib *status als not found, aber unsicher wie es geht bei luis
                return 0;
            }
            else {
                *status = NOT_FOUND;
                mem_arr.set_first_not_found(false);
                return -1;
            }
        }
    }
    else { //IF RESIZING == FALSE
        Deathcondition deathcond;
        bool isdead = deathcond.return_Is_Dead();
        if (isdead) {
            *status = TOT;
        }
        return 0;
    }
    return 0;
}
