#pragma once

#include "XMLWriter.h"

class Save
{
public:
	Save();
	~Save();
	void saveValues();
	void loadValues();

private:
	void writeState();
	std::string getTimeDate();

	XMLWriter writer;
};

