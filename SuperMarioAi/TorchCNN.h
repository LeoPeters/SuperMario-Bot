#pragma once
#include <torch/script.h> // One-stop header.
#include "ImageDistributor.h"
class TorchCNN
{
private:
	ImageDistributor distr;
	torch::jit::script::Module module;
public:
	TorchCNN();
	int returnErgFromGridcoords(int gridx, int gridy);
	~TorchCNN() = default;
};
