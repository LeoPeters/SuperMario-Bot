#include "TorchCNN.h"

TorchCNN::TorchCNN(): distr(), module() {
    try
    {
    // Deserialize the ScriptModule from a file using torch::jit::load().
        module = torch::jit::load("./pytorch-models/traced_cnn_model.pt");
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
   // PngImage resized("pictures/Resized/pic0.png");
            //std::cout << "cnn start\n";
        
            for (int y = 0; y < 16; y++) {
                png_bytep img_row = resized.row_pointers[ypos + y];
                for (int x = 0; x < 16; x++) {
                    png_bytep impx = &(img_row[(xpos + x) * 4]);
                    array[x][y][0] = impx[0];// / 255;
                    array[x][y][1] = impx[1];// / 255;
                    array[x][y][2] = impx[2];// / 255;
                   // std::cout << (int)impx[0] << " " << (int)impx[1] << " " << (int)impx[2] << " ";
                }
               // std::cout << std::endl;
            }
    /*
    for (int i = 0; i < 3; i++) {
        for (int y = 0; y < 16; y++) {
            png_bytep img_row = resized.row_pointers[ypos + y];
            for (int x = 0; x < 16; x++) {
                png_bytep impx = &(img_row[(xpos + x) * 4]);
                array[i][y][x] = (float)(impx[i]);
                array[i][y][x] = array[i][y][x] / 255;
                // std::cout << (int)impx[0] << " " << (int)impx[1] << " " << (int)impx[2] << " ";
            }
            // std::cout << std::endl;
        }

    }*/
            //std::cout << array[0][0];

            //torch::scalar_to_tensor(array);
            //
            //auto options = torch::TensorOptions().dtype(torch::kInt32);
            //torch::Tensor tensor = torch::from_blob(array, { 3, 16, 16 } );//, options);
    torch::Tensor tensor = torch::from_blob(array, { 16, 16, 3 });
            tensor = tensor / 255;
            tensor = at::transpose(tensor, 0, 1);
            tensor = at::transpose(tensor, 0, 2);
    tensor = tensor.unsqueeze(0);
           //std::cout.precision(6);
            //torch::print(tensor,100000); //WORKING 100& CORRECTLY!!!!
           // std::cout << tensor.data();
            //std::cout << tensor.data()[0][1];
            //std::cout << tensor.data()[0][2];
            //std::cout << tensor.sizes() << std::endl;
    std::vector<torch::jit::IValue> inputs;
    inputs.emplace_back(tensor);
           // std::cout << tensor.sizes();
            //std::cout << tensor.index({ 0 });
            //return 0;    
    auto erg = module.forward(inputs);
            //torch::Tensor classification = erg.argmax(1);
            //int32_t classificationWinner = classification.item().toInt();
    auto pred = at::argmax(erg.toTensor(), 1, true).item().toInt();

    return pred;// erg.slice(/*dim=*/1, /*start=*/0, /*end=*/5).max().item().toInt();
}