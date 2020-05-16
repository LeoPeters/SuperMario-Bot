#pragma once

#include "XMLWriter.h"
#include "XMLReader.h"
#include "Globals.h"
#include "State.h"
#include "MarioFeature.h"

struct SaveLoad {
	int numberOfCycles;
	int statesSize;
	int numberOfWins;
	int numberOfDeaths;
	std::vector<MarioFeature> activeFeatures;
	std::array<std::vector<int>, NUMBER_OF_STATES> featureValues;
	std::array<State, NUMBER_OF_STATES> scores;
};

class Memory
{
public:
	Memory();
	~Memory();
	void saveValues(SaveLoad *save);
	void loadValues(std::string path, SaveLoad *load);

private:
	void writeState();
	std::string getTimeDate();

	XMLWriter writer;
	XMLReader reader;
};

