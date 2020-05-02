#include "XMLWriter.h"

//=============================================================================
//== Function Name  :   XmlWriter::exists
//==
//== Perameters
//== Name       Type                Description
//== ---------- -----------         --------------------
//== fileName   const std::string   The name of the file that is in use
//==
//== Description
//== --------------------------------------------------------------------------
//== This function is used to check if the XML file exists
//=============================================================================
bool XMLWriter::exists(const std::string fileName) {
    std::ofstream checkFile(fileName);
    return checkFile.is_open();
}

//=============================================================================
//== Function Name  :   XmlWriter::open
//==
//== Perameters
//== Name       Type                Description
//== ---------- -----------         --------------------
//== strFile    const std::string   The name of the file that the user passes
//==                                in the code
//==
//== Description
//== --------------------------------------------------------------------------
//== This function is used to open the XML file, first checking to see if it
//== exists first
//=============================================================================
bool XMLWriter::open(const std::string strFile) {

    if (exists(strFile)) {
        std::cout << "Error: File alread exists.\n";
        return false;
    }

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

//=============================================================================
//== Function Name  :   XmlWriter::close
//==
//== Perameters
//== Name       Type                Description
//== ---------- -----------         --------------------
//== N/a        N/a                 N/a
//==
//== Description
//== --------------------------------------------------------------------------
//== This function is used to close the XML file
//=============================================================================
void XMLWriter::close() {
    if (outFile.is_open()) {
        outFile.close();
    }
    else {
        std::cout << "File already closed.\n";
    }
}

//=============================================================================
//== Function Name  :   XmlWriter::writeOpenTag
//==
//== Perameters
//== Name       Type                Description
//== ---------- -----------         --------------------
//== openTag    const std::string   The name of the tag being created
//==
//== Description
//== --------------------------------------------------------------------------
//== This function creates a new tag, checking that the file is open, and saves
//== the tag name in a vector to keep track of it
//=============================================================================
void XMLWriter::writeOpenTag(const std::string openTag) {
        outFile << std::string(current_indent++, '\t');
        outFile << "<" << openTag << ">\n";
        openTags.push(openTag);
}

//=============================================================================
//== Function Name  :   XmlWriter::writeCloseTag
//==
//== Perameters
//== Name       Type                Description
//== ---------- -----------         --------------------
//== N/a        N/a                 N/a
//==
//== Description
//== --------------------------------------------------------------------------
//== This function closes the currently open tag
//=============================================================================
void XMLWriter::writeCloseTag() {
    if (openTags.empty()) {
        std::cerr << "No tag to close." << std::endl;
        return; // or exit or throw an exception
    }
        outFile << std::string(--current_indent, '\t');
        outFile << "</" << openTags.top() << ">\n";
        openTags.pop();
}

//=============================================================================
//== Function Name  :   XmlWriter::writeStartElementTag
//==
//== Perameters
//== Name       Type                Description
//== ---------- -----------         --------------------
//== elementTag const std::string   The name of the element being created
//==
//== Description
//== --------------------------------------------------------------------------
//== This function creates a new element tag and saves the name to a vector
//=============================================================================
void XMLWriter::writeStartElementTag(const std::string elementTag) {
        outFile << std::string(current_indent, '\t');
        elementTags.push(elementTag);
        outFile << "<" << elementTag;
}

//=============================================================================
//== Function Name  :   XmlWriter::writeEndElementTag
//==
//== Perameters
//== Name       Type                Description
//== ---------- -----------         --------------------
//== N/a        N/a                 N/a
//==
//== Description
//== --------------------------------------------------------------------------
//== This function closed the currently opened element tag
//=============================================================================
void XMLWriter::writeEndElementTag() {
        outFile << "</" << elementTags.top() << ">\n";
        elementTags.pop();
}

//=============================================================================
//== Function Name  :   XmlWriter::writeAttribute
//==
//== Perameters
//== Name           Type                Description
//== ----------     -----------         --------------------
//== outAttribute   const std::string   The attribute being written out
//==
//== Description
//== --------------------------------------------------------------------------
//== This function writes an attribute (if any) after the element tag is first
//== opened and before the output for the element is written
//=============================================================================
void XMLWriter::writeAttribute(const std::string outAttribute) {
        outFile << " " << outAttribute;
}

//=============================================================================
//== Function Name  :   XmlWriter::writeString
//==
//== Perameters
//== Name           Type                Description
//== ----------     -----------         --------------------
//== writeString    const std::string   The string to be written to the element
//==
//== Description
//== --------------------------------------------------------------------------
//=============================================================================
void XMLWriter::writeString(const std::string outString) {
        outFile << ">" << outString;
}