#include "TorchCNN.h"
#include "Globals.h"
TorchCNN::TorchCNN() : distr(), module(), mariofinder() {
    try
    {
        // Deserialize the ScriptModule from a file using torch::jit::load().
        module = torch::jit::load("./pytorch-models/traced_cnn_model__.pt");
    }
    catch (const c10::Error& e)
    {
        std::cerr << "error loading the model\n";
        //return -1;#
        abort();
    }
    std::cout << "loaded cnn model\n";
}

int TorchCNN::returnErgFromGridcoords(int gridx, int gridy)
{
    //get rgb values into an array
    torch::Tensor sizestensor = torch::randn({ 16, 16, 3 });
    //std::cout<< sizestensor.sizes() << std::endl;
    PngImage& resized = distr.grab_resized_img();
    int y_pos = 0;
    int x_pos = 0;
    float array[16][16][3];
    //float array[3][16][16];
    //TESTING
    int xpos = gridx * 16;
    int ypos = gridy * 16;
    for (int y = 0; y < 16; y++) {
        png_bytep img_row = resized.row_pointers[ypos + y];
        for (int x = 0; x < 16; x++) {
            png_bytep impx = &(img_row[(xpos + x) * 4]);
            array[x][y][0] = impx[0];// / 255;
            array[x][y][1] = impx[1];// / 255;
            array[x][y][2] = impx[2];// / 255;
        }
    }

    torch::Tensor tensor = torch::from_blob(array, { 16, 16, 3 });
    tensor = tensor / 255;
    tensor = at::transpose(tensor, 0, 1);
    tensor = at::transpose(tensor, 0, 2);
    tensor = tensor.unsqueeze(0);

    std::vector<torch::jit::IValue> inputs;
    inputs.emplace_back(tensor);

    auto erg = module.forward(inputs);

    auto pred = at::argmax(erg.toTensor(), 1, true).item().toInt();

    switch (pred) {
    case 0: return BLOCK;
    case 1: return ENEMY;
    case 2: return ITEM;
    case 3: //we got mario. Check if its a valid one with the template matcher
        if (mariofinder.search_for_Mario_on_grid(gridx, gridy)) {
            return MARIO;
        }
        return SKY;
    case 4: return SKY;
    case 5: return WINNINGCONDS;
    }

    return SKY;
}

