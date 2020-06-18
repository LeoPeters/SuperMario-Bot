#pragma once
#include <torch/torch.h>
#include <string>
class TorchModuleUtils
{
public:
	static void loadstatedict(torch::nn::Module& model, torch::nn::Module& target_model);
	static void saveModule(torch::nn::Module& model, std::string filename);
	static void loadModule(torch::nn::Module& model, std::string filename);
};

