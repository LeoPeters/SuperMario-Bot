#include "TorchModuleUtils.h"


void TorchModuleUtils::loadstatedict(torch::nn::Module& model,
	torch::nn::Module& target_model) {
	torch::autograd::GradMode::set_enabled(false);  // make parameters copying possible
	auto new_params = target_model.named_parameters(); // implement this
	auto params = model.named_parameters(true /*recurse*/);
	auto buffers = model.named_buffers(true /*recurse*/);
	for (auto& val : new_params) {
		auto name = val.key();
		auto* t = params.find(name);
		if (t != nullptr) {
			t->copy_(val.value());
		}
		else {
			t = buffers.find(name);
			if (t != nullptr) {
				t->copy_(val.value());
			}
		}
	}
	torch::autograd::GradMode::set_enabled(true);
}

void TorchModuleUtils::saveModule(torch::nn::Module& model, std::string filename)
{
	torch::serialize::OutputArchive output_archive;
	model.save(output_archive);
	output_archive.save_to(filename);
}

void TorchModuleUtils::loadModule(torch::nn::Module& model, std::string filename)
{
	torch::serialize::InputArchive input_archive;
	input_archive.load_from(filename);
	model.load(input_archive);
}
