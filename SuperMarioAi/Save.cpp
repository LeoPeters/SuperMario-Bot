#include "Save.h"
#include "Globals.h"
#include <iostream>
#include <fstream>
#include <ctime>

Save::Save() 
{

}

Save::~Save()
{

}

void Save::saveValues(std::array<std::vector<int>, NUMBER_OF_STATES> features)
{
    XMLWriter xml;
    std::string path = SAVEFILE_PATH;
    std::string fileName = path.append(getTimeDate());
    if (xml.open(fileName)) {
        xml.writeOpenTag("testTag");
        xml.writeStartElementTag("testEle1");
        xml.writeString("This is my first tag string!");
        xml.writeEndElementTag();

        xml.writeOpenTag("testTag2");
        xml.writeStartElementTag("testEle2");
        xml.writeAttribute("testAtt=\"TestAttribute\"");
        xml.writeString("I sometimes amaze myself.");
        xml.writeEndElementTag();

        xml.writeOpenTag("testTag3");
        xml.writeStartElementTag("testEle3");
        xml.writeAttribute("testAtt2=\"TestAttrib2\"");
        xml.writeString("Though i'm sure someone can make something even better");
        xml.writeEndElementTag();

        xml.writeCloseTag();
        xml.writeCloseTag();
        xml.writeCloseTag();

        xml.close();
        std::cout << "Success!\n";
    }
    else {
        std::cout << "Error opening file.\n";
    }
}

void Save::loadValues() 
{

}

std::string getTimeDate() 
{
    time_t now = time(0);
    return ctime(&now);
}