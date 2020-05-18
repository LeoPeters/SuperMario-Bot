#include "XMLWriter.h"

bool XMLWriter::exists(const std::string fileName) {
    std::ifstream f(fileName.c_str());
    return f.good();
}

bool XMLWriter::open(const std::string strFile) {

    outFile.open(strFile);
    if (outFile.is_open()) {
        std::cout << "File created successfully.\n";
        outFile << "<!--XML Document-->\n";
        outFile << "<?xml version='1.0' encoding='us-ascii'>\n";
        current_indent = 0;
        return true;
    }
    return false;
}

void XMLWriter::close() {
    if (outFile.is_open()) {
        outFile.close();
    }
    else {
        std::cout << "File already closed.\n";
    }
}

void XMLWriter::writeOpenTag(const std::string openTag) {
        outFile << std::string(current_indent++, '\t');
        outFile << "<" << openTag << ">\n";
        openTags.push(openTag);
}

void XMLWriter::writeCloseTag() {
    if (openTags.empty()) {
        std::cerr << "No tag to close." << std::endl;
        return; // or exit or throw an exception
    }
        outFile << std::string(--current_indent, '\t');
        outFile << "</" << openTags.top() << ">\n";
        openTags.pop();
}

void XMLWriter::writeStartElementTag(const std::string elementTag) {
        outFile << std::string(current_indent, '\t');
        elementTags.push(elementTag);
        outFile << "<" << elementTag;
}

void XMLWriter::writeEndElementTag() {
        outFile << "</" << elementTags.top() << ">\n";
        elementTags.pop();
}

void XMLWriter::writeAttribute(const std::string outAttribute) {
        outFile << " " << outAttribute;
}

void XMLWriter::writeAttribute(int outAttribute) {
    outFile << " " << outAttribute;
}

void XMLWriter::writeValue(const std::string outString) {
        outFile << ">" << outString;
}

void XMLWriter::writeValue(int outInt) {
    outFile << ">" << outInt;
}