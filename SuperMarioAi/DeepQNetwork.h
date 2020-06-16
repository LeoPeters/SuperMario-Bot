#pragma once

#include<iostream>
#include<torch/torch.h>
#include <vector>
// build a neural network similar to how you would do it with Pytorch 

struct Model : torch::nn::Module {
    // Constructor
    Model() {
        conv1 = register_module("conv1", torch::nn::Conv2d(4, 16, 3));
        bn1 = register_module("bn1", torch::nn::BatchNorm2d(16));
        conv2 = register_module("conv2", torch::nn::Conv2d(16, 32, 3));
        bn2 = register_module("bn2", torch::nn::BatchNorm2d(32));
        hidden = register_module("hidden", torch::nn::Linear(32 * 11 * 11, 1000));
        output = register_module("output", torch::nn::Linear(1000, 12));
    }
    // the forward operation (how data will flow from layer to layer)
    torch::Tensor forward(torch::Tensor X) {
        //std::cout << X.sizes() << std::endl;
        X = torch::relu(conv1->forward(X));
        //std::cout << X.sizes() << std::endl;
        X = bn1->forward(X);
        //std::cout << X.sizes() << std::endl;
        X = torch::relu(conv2->forward(X));
        //std::cout << X.sizes() << std::endl;
        X = bn2->forward(X);
        //std::cout << X.sizes() << std::endl;
        X = X.view({ X.size(0), -1 });
        //std::cout << X.sizes() << std::endl;
        X = torch::relu(hidden->forward(X));
        //std::cout << X.sizes() << std::endl;
        X = torch::sigmoid(output->forward(X));
        //std::cout << X.sizes() << std::endl;
        return X;
    }

    torch::nn::Conv2d conv1{ nullptr }, conv2{ nullptr };
    torch::nn::BatchNorm2d bn1{ nullptr }, bn2{ nullptr };
    torch::nn::Linear hidden{ nullptr }, output{ nullptr };
};


class DeepQNetwork
{
private:

public:
    float learnrate;
    int n_actions;
    Model model;
    torch::optim::Adam optimizer;
    torch::nn::MSELoss loss;
    

    DeepQNetwork(float lr, int actions);
    ~DeepQNetwork();
};

