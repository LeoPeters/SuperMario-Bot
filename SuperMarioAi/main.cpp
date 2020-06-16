#include <torch/script.h> // One-stop header.
//#include "TorchCNN.h"
#include <iostream>
#include "AiController.h"
#include <thread>
#include "MemoryFinder.h"
#include <string>
#include <chrono>
#include "DeepQNetwork.h"
#include "DQNAgent.h"
#include <time.h> 
#include <algorithm>
#include <random>
#include <vector>
#define DEBUG true
FILE* fDummy;
void CreateConsole();


static std::vector<unsigned char> getEnvDataDummy() {
    std::vector<unsigned char> v(4 * 15 * 15);
    std::generate(v.begin(), v.end(), std::rand);
    return v;
}

int main(int argc, char* argv[])
{
    if (DEBUG) {
        CreateConsole();
    }

    DQNAgent agent( /*gamma*/0.999, /*epsilon*/0.1, /*learnrate*/0.001, 
                    /*eps_min*/0.001, /*eps_dec*/0.0001, /*mem_size*/10000, 
                    /*batch_size*/16, /*update_target*/10, /*actions*/12, 
                    /*input_shape: DIM, HEIGHT, WIDTH*/4, 15, 15 );

    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 80; i++) {
    srand(time(NULL));
    int random = rand();

    //ABLAUF:
    //GET INPUT 4 15 15 => v
    auto state = getEnvDataDummy();
    //act
    int action = agent.choose_action(state);
    //std::cout <<"action: "<< action << std::endl;
    //GET NEW ENV AFTER ACTION
    //DO ( ACTION ) 
    auto nextstate = getEnvDataDummy();
    // REWARD = GET REWARD()
    float reward = (float)random / (RAND_MAX); /*DUMMY*/
    // AM I DONE = GET DONE?()
    bool done = false; /*DUMMY*/
    //jetzt: store transition
    agent.store_transition(/*state*/state, /*action*/action, /*reward*/reward, /*newstate*/nextstate, /*done*/done);
    agent.learn(); //hier wird er nicht lernen, da memory size < batchsize ( 1 < 2)
    }
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    std::cout << duration.count() << "ms for inputting 80* 4*15*15 pictures and learning after the 8th" << std::endl;


    char x;
    std::cin >> x;
    return 0;

    AiController controller(argc, argv);
    std::thread controllerThread(&AiController::run, &controller);
    controller.runGui();
    controllerThread.join();
    if (DEBUG) {
        fclose(fDummy);
        FreeConsole();
    }
    
    
    return 0;
}
void CreateConsole()
{
    if (!AllocConsole()) {
        // Add some error handling here.
        // You can call GetLastError() to get more info about the error.
        return;
    }
    // std::cout, std::clog, std::cerr, std::cin
    freopen_s(&fDummy, "CONOUT$", "w", stdout);
    freopen_s(&fDummy, "CONOUT$", "w", stderr);
    freopen_s(&fDummy, "CONIN$", "r", stdin);
    std::cout.clear();
    std::clog.clear();
    std::cerr.clear();
    std::cin.clear();
    std::wcout.clear();
    std::wclog.clear();
    std::wcerr.clear();
    std::wcin.clear();
}