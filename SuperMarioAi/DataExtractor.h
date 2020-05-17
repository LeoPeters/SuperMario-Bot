#ifndef dataextractor_h
#define dataextractor_h

#include <string>
#include "XMLReader.h"
#include "XMLWriter.h"
#include "Globals.h"

class DataExtractor {
private:
    int filecount;
    XMLWriter xml;
    int filecopy();
public:
    DataExtractor();
    bool write_array_to_data_file(int ergarray[GRIDRADIUS][GRIDRADIUS]);
    ~DataExtractor() {
        xml.close();
    }
};

#endif 