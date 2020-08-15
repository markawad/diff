#ifndef TEXT_H
#define TEXT_H

#include "FileType.h"

class Text : public FileType {
protected:
    vector<string> f1, f2;
    vector<string>::iterator it1, it2;

public:
    Text(FileHandler &h) : FileType(h) {}

    void parseData();

    void addElements(bool valueNotAdded1);

    void deleteElements(bool valueNotAdded2);

    void compare();

    void printOutput();

    friend FileType;
};


#endif //TEXT_H
