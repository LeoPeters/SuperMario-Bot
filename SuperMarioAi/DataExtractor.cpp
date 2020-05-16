#include "DataExtractor.h"
#define MAX_TRAIN_DATA (1350000/3)
#define STARTZAHL 0
#define STARTINDEX_TRAINDATA_STRING (MAX_TRAIN_DATA*STARTZAHL)
#define ERRORNUM -2
#define filepath "aiTrainingData/pytorchdata.xml"

DataExtractor::DataExtractor(): xml(), filecount(0)
{
    if (!xml.open(filepath)){
        abort();
    }
}


int DataExtractor::filecopy() {
    //COPY
    if (MAX_TRAIN_DATA <= filecount) {
        //exit(1);
        return ERRORNUM;
    }
    std::string path = "aiTrainingData/pictures/";
    path += std::to_string(filecount+STARTINDEX_TRAINDATA_STRING);
    path += ".png";
    std::filesystem::copy("pictures/Resized/resized.png", path); // copy file
    filecount++;
    return filecount - 1;
}


bool DataExtractor::write_array_to_data_file(int ergarray[GRIDRADIUS][GRIDRADIUS])
{
    int num = filecopy();
    if (num == ERRORNUM) {
        return false;
    }
    xml.writeOpenTag("png");
    xml.writeStartElementTag("path");
    std::string filename;
    filename += std::to_string(num + STARTINDEX_TRAINDATA_STRING);
    filename += ".png";
    xml.writeValue(filename);
    xml.writeEndElementTag();
    xml.writeStartElementTag("values");
    std::string temp;
    for (int x = 0; x < GRIDRADIUS; x++) {
        for (int y = 0; y < GRIDRADIUS; y++) {
            temp += std::to_string(ergarray[x][y]) + ",";
        }
    }
    temp.erase(temp.size() - 2, temp.size() - 1);
    xml.writeValue(temp);
    xml.writeEndElementTag();
    xml.writeCloseTag();
	return true;
}
