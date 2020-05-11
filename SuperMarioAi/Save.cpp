#include <windows.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <iomanip>
#include <string>
#include <array>
#include <vector>
#include "Save.h"
#include "Globals.h"
#include "MemoryFinder.h"
#include "MarioFeature.h"

Save::Save() 
{

}

Save::~Save()
{

}

//TODO Statistiken übergeben (Tode, Wins, Anzahl Durchläufe etc.)
void Save::saveValues(std::array<std::vector<int>, NUMBER_OF_STATES>* features, std::array<State, NUMBER_OF_STATES>* scores, int numberOfCycles, int statesSize)
{
    std::string featureName;
    std::string scoreValues;
    std::ostringstream strStream;
    XMLWriter xml;
    std::string path = "saves/";
    std::string fileName = path + getTimeDate() + ".xml";
    std::replace(fileName.begin(), fileName.end(), ':', '-');

    if (xml.open(fileName)) {

        xml.writeStartElementTag("AnzahlDurchlaeufe");
        xml.writeValue(numberOfCycles);
        xml.writeEndElementTag();
        xml.writeStartElementTag("AnzahlStates");
        xml.writeValue(statesSize);
        xml.writeEndElementTag();

        xml.writeStartElementTag("FeatureNames");
        for (int i = 0; i < MarioFeature::size; i++)
        {
            featureName += MarioFeature::toString(i) + ",";
        }
        featureName.erase(std::remove_if(featureName.begin(), featureName.end(), ::isspace), featureName.end());
        featureName.erase(featureName.size() - 1, featureName.size());
        xml.writeValue(featureName);
        xml.writeEndElementTag();

        for (int i = 1; i < statesSize; i++)
        {
            xml.writeOpenTag("State");

            xml.writeStartElementTag("stateNumber");
            xml.writeValue(i);
            xml.writeEndElementTag();

            xml.writeOpenTag("Features");
            for (int j = 0; j < features->at(i).size(); j++)
            {
                featureName = MarioFeature::toString(j);
                featureName.erase(std::remove_if(featureName.begin(), featureName.end(), ::isspace), featureName.end());
                xml.writeStartElementTag(featureName);
                xml.writeValue(features->at(i)[j]);
                xml.writeEndElementTag();
            }
            xml.writeCloseTag();
            xml.writeStartElementTag("Scores");
            scoreValues = "";
            for (int j = 0; j < MarioAction::size; j++)
            {
            strStream.str(std::string());
            //strStream << std::fixed;
            strStream << std::setprecision(12);
            strStream << scores->at(i).getValue(MarioAction(j));
            scoreValues += strStream.str() + ",";
            }
            scoreValues.erase(scoreValues.size() - 3, scoreValues.size() - 1);
            xml.writeValue(scoreValues);
            xml.writeEndElementTag();
            xml.writeCloseTag();
        }

        /*
        xml.writeOpenTag("testTag");
        xml.writeStartElementTag("testEle1");
        xml.writeValue("This is my first tag string!");
        xml.writeEndElementTag();

        xml.writeOpenTag("testTag2");
        xml.writeStartElementTag("testEle2");
        xml.writeAttribute("testAtt=\"TestAttribute\"");
        xml.writeValue("I sometimes amaze myself.");
        xml.writeEndElementTag();

        xml.writeOpenTag("testTag3");
        xml.writeStartElementTag("testEle3");
        xml.writeAttribute("testAtt2=\"TestAttrib2\"");
        xml.writeValue("Though i'm sure someone can make something even better");
        xml.writeEndElementTag();

        xml.writeCloseTag();
        xml.writeCloseTag();
        xml.writeCloseTag();
        */

        xml.close();
        std::cout << "Success!\n";
    }
    else {
        std::cout << "Error opening file.\n";
    }
}

void Save::loadValues(std::string path, std::array<std::vector<int>, NUMBER_OF_STATES>* featureValues, std::array<State, NUMBER_OF_STATES>* scores, int* numberOfCycles, int* statesSize)
{
    std::string temp;
    std::string item;
    reader.openFile(path);
    temp = reader.readNextElement();
    *numberOfCycles = std::stoi(temp);
    temp = reader.readNextElement();
    *statesSize = std::stoi(temp);
    
    //TODO FeatureNames std::vector<std::string>
    temp = reader.readNextElement();

    for (int i = 1; i < *statesSize; i++) {
        temp = reader.readNextElement(); //TODO Statenumber ist bekannt (i)!
        for (int j = 0; j < MarioFeature::size; j++)
        {
            temp = reader.readNextElement();
            featureValues->at(i).push_back(std::stoi(temp));
        }
        temp = reader.readNextElement();
        std::stringstream ss(temp);
        int k = 0;
        while (std::getline(ss, item, ','))
        {
            scores->at(i).setScore(MarioAction(k++), ::atof(item.c_str()));
        }
    }
}



std::string Save::getTimeDate() 
{
    time_t now = time(0);
    std::string time = ctime(&now);
    return time.erase(time.size()-3,time.size()-1);
}