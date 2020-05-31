#include <torch/script.h> // One-stop header.

#include <iostream>
#include "AiController.h"
#include <thread>
#include "MemoryFinder.h"
#include <string>
#define DEBUG true
FILE* fDummy;
void CreateConsole();

int main(int argc, char* argv[])
{
    if (DEBUG) {
        CreateConsole();
    }

    torch::jit::script::Module module;
    try
    {
        // Deserialize the ScriptModule from a file using torch::jit::load().
        module = torch::jit::load("./pytorch-models/traced_cnn_model.pt");
    }
    catch (const c10::Error& e)
    {
        std::cerr << "error loading the model\n";
        return -1;
    }
    std::cout << "ok\n";

    
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