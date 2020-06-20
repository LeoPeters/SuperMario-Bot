#include "EnvironmentDQN.h"
#include "Globals.h"
#include <iostream>
#include "MarioObject.h"
EnvironmentDQN::EnvironmentDQN():
	delay(false)
{
	initDQNInput();
}
void EnvironmentDQN::calculateEnv(std::vector<std::vector<int>> vec,  GameState gameState)
{
	simpleVec = vec;
	this->gameState = gameState;
	generateDQNInput(flattingVector(vec));
	calculateReward();
	lastSimpleVec = vec;
}
std::vector<unsigned char> EnvironmentDQN::flattingVector(std::vector<std::vector<int>> vec)
{
	std::vector<unsigned char> flatVec;
	for (int i = 0; i < vec.size(); i++) {
		for (int j = 0; j < vec.at(i).size(); j++) {
			flatVec.push_back(vec.at(i).at(j));
		}
	}
	return flatVec;
}

void EnvironmentDQN::generateDQNInput(std::vector<unsigned char> flatVec)
{
	dqnInput.erase(dqnInput.begin(), dqnInput.begin() + GRIDRADIUS * GRIDRADIUS);
	dqnInput.insert(dqnInput.end(), flatVec.begin(), flatVec.end());
}

void EnvironmentDQN::calculateReward()
{
	done = false;
	reward=0.0;
	if (progressStep()) {
		//reward += REWARDMOVERIGHT;
		reward += 1;
		return;
	}
	if (gameState == GameState::Win) {
		reward += REWARDWIN;
		done = true;
		return;
	}
	if (gameState == GameState::GameOver) {
		//reward += REWARDLOSE;
		reward -= 10;
		done = true;
		return;
	}
	reward -= 0.2;
}

void EnvironmentDQN::initDQNInput() {
	dqnInput.clear();
	for (int i = 0; i < GRIDRADIUS * GRIDRADIUS * INPUT_DIM; i++) {
		dqnInput.push_back(0);
	}
}

double EnvironmentDQN::getReward()
{
	return reward;
}

std::vector<unsigned char> EnvironmentDQN::getInputDQN()
{
	return dqnInput;
}

bool EnvironmentDQN::getDone()
{
	return done;
}

bool EnvironmentDQN::calcualateCanJump()
{
	if (!marioOnGround(simpleVec) && !marioOnGround(lastSimpleVec) ) {
		delay = true;
		return false;
	}
	
	if (delay) {
		delay = false;
		return false;
	}


	return true;
}
MarioAction EnvironmentDQN::filterJump(MarioAction action) {
	switch (action)
	{
	case MarioAction::jump:
		return MarioAction::idle;
	case MarioAction::jumpLeft:
		return MarioAction::left ;
	case MarioAction::jumpLeftB:
		return MarioAction::leftB;
	case MarioAction::jumpRight:
		return MarioAction::right  ;
	case MarioAction::jumpRightB:
		return MarioAction::rightB;
	default:
		return action;
	}
}
bool EnvironmentDQN::marioOnGround(std::vector<std::vector<int>> vec)
{
	bool marioFound = false;
	int y = 0;
	int x = 0;


	for (y = 0; y < simpleVec.size(); y++) {
		for (x = 0; x< simpleVec.at(y).size(); x++) {
			if (simpleVec.at(y).at(x)==(int)MarioObject::mario ){
				marioFound = true;
				break;
			}
		}
		if (marioFound == true) {
			break;
		}
	}
	if (marioFound && y < GRIDRADIUS - 1 && simpleVec.at(y + 1).at(x) == (int)MarioObject::ground) {
		return true;
	}
	return false;
}

bool EnvironmentDQN::progressStep() {
	bool isProgress = false;
	if (simpleVec.size() == lastSimpleVec.size()) {

	for (int y = 0; y < simpleVec.size();y++) {
		for (int x = 0; x < simpleVec.at(y).size(); x++) {
			if (isStaticObject(simpleVec.at(y).at(x))&& simpleVec.at(y).at(x)!= lastSimpleVec.at(y).at(x)){
				return true;
			}
		}
	}
	}
	return false;
}

bool EnvironmentDQN::isStaticObject(int i) {
	MarioObject object = MarioObject(i);
	bool isStatic;
	switch (object)
	{
	case MarioObject::empty:
		isStatic = false;
		break;
	case MarioObject::mario:
		isStatic = false;
		break;
	case MarioObject::ground:
		isStatic = true;
		break;
	case MarioObject::enemy:
		isStatic = false;
		break;
	case MarioObject::item:
		isStatic = false;
		break;
	case MarioObject::flag:
		isStatic = true;
		break;
	default:
		isStatic = false;
		break;
	}
	return isStatic;
}