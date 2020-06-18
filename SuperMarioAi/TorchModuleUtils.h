#pragma once
#include <torch/torch.h>
#include <string>
class TorchModuleUtils
{
public:
	static void loadstatedict(torch::nn::Module& copy_to_this, torch::nn::Module& copy_from_this);
	static void saveModule(torch::nn::Module& model, std::string filename);
	static void loadModule(torch::nn::Module& model, std::string filename);
};

