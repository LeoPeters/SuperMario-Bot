#include <windows.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <iomanip>
#include <string>
#include <array>
#include <vector>
#include "Memory.h"
#include "Globals.h"
#include "MemoryFinder.h"
#include "MarioFeature.h"

Memory::Memory()
{

}

Memory::~Memory()
{

}

std::string Memory::writeFileName(SaveLoad* saveLoad)
{
    std::string fileName = "";

    fileName.append("S" + std::to_string(saveLoad->statesSize) + " ");
    fileName.append("C" + std::to_string(saveLoad->numberOfCycles) + " ");
    fileName.append("W" + std::to_string(saveLoad->numberOfWins) + " ");
    fileName.append("D" + std::to_string(saveLoad->numberOfDeaths) + " F");
    for (int i = 0; i < saveLoad->activeFeatures.size(); i++) {
        fileName.append(std::to_string(saveLoad->activeFeatures[i]) + ",");
    }
    fileName.erase(fileName.size() - 1, fileName.size()); //Delete last comma
    fileName.append("_v");
    return fileName;
}

//TODO Statistiken übergeben (Tode, Wins, Anzahl Durchläufe etc.)
void Memory::saveValues(SaveLoad* saveLoad)
{
    std::string featureName;
    std::string scoreValues;
    std::ostringstream strStream;
    XMLWriter xml;
    std::string path = "saves/";
    std::string fileName = path.append(writeFileName(saveLoad));
    int i = 1;
    while (xml.exists(fileName + std::to_string(i) + ".xml")) {
        i++;
        if (i > 10) {
            break;
        }
    }

    fileName.append(std::to_string(i) + ".xml");


    if (xml.open(fileName)) {

        xml.writeStartElementTag("NumberOfCycles");
        xml.writeValue(saveLoad->numberOfCycles);
        xml.writeEndElementTag();
        xml.writeStartElementTag("NumberOfStates");
        xml.writeValue(saveLoad->statesSize);
        xml.writeEndElementTag();
        xml.writeStartElementTag("NumberOfWins");
        xml.writeValue(saveLoad->numberOfWins);
        xml.writeEndElementTag();
        xml.writeStartElementTag("NumberOfDeaths");
        xml.writeValue(saveLoad->numberOfDeaths);
        xml.writeEndElementTag();

        xml.writeStartElementTag("ActiveFeatures");

        for (int i = 0; i < saveLoad->activeFeatures.size(); i++)
        {
            featureName.append(std::to_string(saveLoad->activeFeatures[i]) + ",");
        }
        featureName.erase(featureName.size() - 1, featureName.size());
        xml.writeValue(featureName);
        xml.writeEndElementTag();

        for (int i = 1; i < saveLoad->statesSize; i++)
        {
            xml.writeOpenTag("State");

            xml.writeStartElementTag("stateNumber");
            xml.writeValue(i);
            xml.writeEndElementTag();

            //Write Features
            xml.writeOpenTag("Features");
            for (int j = 0; j < saveLoad->featureValues.at(i).size(); j++)
            {
                featureName = MarioFeature::toString(j);
                featureName.erase(std::remove_if(featureName.begin(), featureName.end(), ::isspace), featureName.end());
                xml.writeStartElementTag(featureName);
                xml.writeValue(saveLoad->featureValues.at(i)[j]);
                xml.writeEndElementTag();
            }
            xml.writeCloseTag();

            //Write Scores
            xml.writeStartElementTag("Scores");
            scoreValues = "";
            for (int j = 0; j < MarioAction::size; j++)
            {
            strStream.str(std::string());
            //strStream << std::fixed;
            strStream << std::setprecision(12);
            strStream << saveLoad->scores.at(i).getValue(MarioAction(j));
            scoreValues += strStream.str() + ",";
            }
            scoreValues.erase(scoreValues.size() - 3, scoreValues.size() - 1); //Delete the last comma
            xml.writeValue(scoreValues);
            xml.writeEndElementTag();
            xml.writeCloseTag();
        }

        xml.close();
        std::cout << "Success!\n";
    }
    else {
        std::cout << "Error opening file.\n";
    }
}

void Memory::loadValues(std::string path, SaveLoad *saveLoad)
{
    std::string temp;
    std::string item;
    int numberOfActiveFeatures = 0;
    reader.openFile(path);

    temp = reader.readNextElement();
    std::cout << temp << std::endl;
    saveLoad->numberOfCycles = std::stoi(temp);
    temp = reader.readNextElement();
    std::cout << temp << std::endl;
    saveLoad->statesSize = std::stoi(temp);
    temp = reader.readNextElement();
    std::cout << temp << std::endl;
    saveLoad->numberOfWins = std::stoi(temp);
    temp = reader.readNextElement();
    std::cout << temp << std::endl;
    saveLoad->numberOfDeaths = std::stoi(temp);
    
    //TODO FeatureNames std::vector<std::string>
    temp = reader.readNextElement();
    std::stringstream ss(temp);

    while (std::getline(ss, item, ',')) {
        MarioFeature f = MarioFeature(std::stoi(item));
        std::cout << f << std::endl;
        saveLoad->activeFeatures.push_back(MarioFeature(std::stoi(item)));
        numberOfActiveFeatures++;
    }

    for (int i = 1; i < saveLoad->statesSize; i++) {
        temp = reader.readNextElement(); //TODO Statenumber ist bekannt (i)!
        for (int j = 0; j < numberOfActiveFeatures; j++)
        {
            temp = reader.readNextElement();
            saveLoad->featureValues.at(i).push_back(std::stoi(temp));
        }
        temp = reader.readNextElement();
        std::stringstream ss(temp);
        int k = 0;
        while (std::getline(ss, item, ','))
        {
            saveLoad->scores.at(i).setScore(MarioAction(k++), ::atof(item.c_str()));
        }
    }
}

std::string Memory::getTimeDate()
{
    time_t now = time(0);
    std::string time = ctime(&now);
    return time.erase(time.size()-3,time.size()-1);
}