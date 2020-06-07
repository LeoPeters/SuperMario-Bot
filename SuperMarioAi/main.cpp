#include <torch/script.h> // One-stop header.
//#include "TorchCNN.h"
#include <iostream>
#include "AiController.h"
#include <thread>
#include "MemoryFinder.h"
#include <string>
#include <chrono>

#define DEBUG true
FILE* fDummy;
void CreateConsole();

int main(int argc, char* argv[])
{
    if (DEBUG) {
        CreateConsole();
    }

    /*
    ImageLibrary* libptr = ImageLibrary::getInstance();
    PngImage resized("pictures/Resized/resized.png");
    libptr->set_resized_image(resized);

    TorchCNN cnn;
    for (int y = 0; y < 15; y++) {
        for (int x = 0; x < 15; x++) {
            std::cout<<cnn.returnErgFromGridcoords(x, y)<<" ";

        }
        std::cout << std::endl;
    } 
    */

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