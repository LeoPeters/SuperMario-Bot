#pragma once
#include <vector>
#include "DeepQNetwork.h"
#include "ExperienceReplay.h"

class DQNAgent
{
private:
	float gamma;
	float epsilon;
	float eps_min;
	float eps_dec;
	float learnrate;
	int mem_size;
	int batch_size;
	int mem_cntr;
	int iter_cntr;
	int replace_target;
	const int input_size;
	const int input_dim;
	const int input_width;
	const int input_height;
	const int num_actions;
	
	DeepQNetwork* Q_eval;
	DeepQNetwork* Q_next;
	ExperienceReplay storage;
	/*std::vector<int> action_space;

	std::vector<std::vector<int>> vec_state_memory;
	std::vector<std::vector<int>> vec_new_state_memory;

	std::vector<float> vec_reward_memory;
	std::vector<int> vec_action_memory;
	std::vector<bool> vec_terminal_memory;

	std::vector<int> get_random_indexes(int max);*/
	torch::Tensor get_tensor_observation(std::vector<unsigned char> state);
public:
	DQNAgent(float gamma, float epsilon, float lr, float eps_min, float eps_dec, int mem_size, 
		int batch_size, int replace_target,int n_actions, int input_num, int width, int height);
	~DQNAgent();
	void store_transition(std::vector<unsigned char> state, int64_t action, float reward, std::vector<unsigned char> state_, bool terminal);
	int choose_action(std::vector<unsigned char>  observation);
	void learn();
	

};

