#pragma once

#include "XMLWriter.h"
#include "XMLReader.h"
#include "Globals.h"
#include "State.h"

class Save
{
public:
	Save();
	~Save();
	void Save::saveValues(std::array<std::vector<int>, NUMBER_OF_STATES>* features, std::array<State, NUMBER_OF_STATES>* scores, int numberOfCycles, int statesSize);
	void Save::loadValues(std::string path, std::array<std::vector<int>, NUMBER_OF_STATES>* featureValues, std::array<State, NUMBER_OF_STATES>* scores, int* numberOfCycles, int* statesSize);

private:
	void writeState();
	std::string getTimeDate();

	XMLWriter writer;
	XMLReader reader;
};

