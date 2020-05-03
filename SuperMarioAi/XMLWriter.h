#ifndef XMLWriter_H
#define XMLWriter_H

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <stack>

class XMLWriter
{
public:
    bool open(const std::string);
    void close();
    bool exists(const std::string);
    void writeOpenTag(const std::string);
    void writeCloseTag();
    void writeStartElementTag(const std::string);
    void writeEndElementTag();
    void writeAttribute(const std::string);
    void writeAttribute(int outAttribute);
    void writeValue(const std::string);
    void writeValue(int outInt);
private:
    std::ofstream outFile;
    int current_indent;
    std::stack<std::string> openTags;
    std::stack<std::string> elementTags;
};

#endif