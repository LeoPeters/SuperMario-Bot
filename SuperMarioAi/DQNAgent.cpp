#include "DQNAgent.h"
#include <time.h> 
#include <time.h> 
#include <algorithm>
#include <random>
#include <vector>
#include <math.h>
#include <tuple>
#include "TorchModuleUtils.h"


DQNAgent::DQNAgent(float gamma, float epsilon, float lr, float eps_min, float eps_dec, int mem_size,
	int batch_size, int replace_target, int n_actions, int input_num, int width, int height) :
	gamma(gamma), epsilon(epsilon), learnrate(lr), eps_min(eps_min), eps_dec(eps_dec), mem_size(mem_size), batch_size(batch_size),
	replace_target(replace_target), mem_cntr(0), iter_cntr(0), input_dim(input_num), input_width(width),
	input_height(height), num_actions(n_actions), input_size(height* width* input_num), storage(mem_size)
	
{

	Q_eval = new DeepQNetwork(lr, n_actions);
	Q_next = new DeepQNetwork(lr, n_actions);
	
}

DQNAgent::~DQNAgent()
{
	delete Q_eval;
	delete Q_next;
}

void DQNAgent::store_transition(std::vector<unsigned char> state, int64_t action, float reward, std::vector<unsigned char> state_, bool terminal)
{
	int index = mem_cntr % mem_size;

	float rewards[1] = { reward };
	bool terminals[1] = { terminal };
	int64_t actions[1] = { action };

	torch::Tensor reward_tensor = torch::from_blob(rewards, { 1 }).clone();
	torch::Tensor terminals_tensor = torch::from_blob(terminals, { 1 }, torch::kFloat32).clone();
	//terminals_tensor = terminals_tensor.to(torch::kFloat32).clone();
	torch::Tensor actions_tensor = torch::from_blob(actions, { 1 }).clone();

	storage.push(get_tensor_observation(state), get_tensor_observation(state_), 
		actions_tensor, terminals_tensor, reward_tensor);

	mem_cntr++;

}



int DQNAgent::choose_action(std::vector<unsigned char> observation)
{
	srand(time(NULL));
	int random = rand();
	if (((float)random / (RAND_MAX)) > epsilon) { //int* observation MUSS: [4][15][15]
		auto actions = Q_eval->model.forward(get_tensor_observation(observation));
		return at::argmax(actions).item().toInt();
	}
	return random % (num_actions);
}


void DQNAgent::learn()
{
	if (mem_cntr < batch_size)
		return;

	auto batch = storage.sample_queue(batch_size);

	std::vector<torch::Tensor> states;
	std::vector<torch::Tensor> new_states;
	std::vector<torch::Tensor> actions;
	std::vector<torch::Tensor> rewards;
	std::vector<torch::Tensor> dones;

	for (auto i : batch) {
		states.push_back(std::get<0>(i));
		new_states.push_back(std::get<1>(i));
		actions.push_back(std::get<2>(i));
		rewards.push_back(std::get<3>(i));
		dones.push_back(std::get<4>(i));
	}

	torch::Tensor states_tensor;
	torch::Tensor new_states_tensor;
	torch::Tensor actions_tensor;
	torch::Tensor rewards_tensor;
	torch::Tensor dones_tensor;

	states_tensor = torch::cat(states);
	new_states_tensor = torch::cat(new_states);
	actions_tensor = torch::cat(actions);
	rewards_tensor = torch::cat(rewards);
	dones_tensor = torch::cat(dones);

	auto q_values = Q_eval->model.forward(states_tensor);
	auto next_q_values = Q_eval->model.forward(new_states_tensor);
	auto next_target_q_values = Q_next->model.forward(new_states_tensor);
	
	actions_tensor = actions_tensor.to(torch::kInt64);
	torch::Tensor maximum = std::get<1>(next_q_values.max(1));
	torch::Tensor next_q_value = next_target_q_values.gather(1, maximum.unsqueeze(1)).squeeze(1);
	torch::Tensor expected_q_value = rewards_tensor + gamma * next_q_value * (1 - dones_tensor);
	torch::Tensor q_value = q_values.gather(1, actions_tensor.unsqueeze(1)).squeeze(1);
	auto loss = Q_eval->loss(q_value, expected_q_value);

	Q_eval->model.zero_grad();
	loss.backward();
	Q_eval->optimizer.step();

	iter_cntr++;
	if (epsilon > eps_min) {
		if (iter_cntr % 3000 == 0) {
			std::string path = "pytorch-models/DQNmodels/";
			path += "DQN_" + std::to_string(iter_cntr) + "_iterations.pt";
			TorchModuleUtils::saveModule(Q_eval->model, path);

			epsilon = epsilon - eps_dec;
			//epsilon = epsilon - 0.01;
			//epsilon = eps_min + (epsilon - (double)eps_min) * exp(-1. * iter_cntr / eps_dec);
			std::cout << "Epsilon: " << epsilon << "\n";
		}
	}
	
	if (iter_cntr % replace_target == 0) {
		TorchModuleUtils::loadstatedict(Q_eval->model, Q_next->model);
	}

}



torch::Tensor DQNAgent::get_tensor_observation(std::vector<unsigned char> state)
{
	std::vector<int64_t > state_int;
	for (int i = 0; i < state.size(); i++) {
		state_int.push_back(int64_t(state[i]));
	}
	torch::Tensor state_tensor = torch::from_blob(state_int.data(), { 1, input_dim, input_height, input_width }).clone();
	return state_tensor;
}