#ifndef BINARY_H
#define BINARY_H

#include "FileType.h"

class Binary : public FileType {
private:
    vector<uint8_t> f1, f2;
    vector<uint8_t>::iterator it1, it2;

public:
    Binary(FileHandler &h) : FileType(h) {}

    void parseData();

    void addElements(bool valueNotAdded1);

    void deleteElements(bool valueNotAdded2);

    void compare();

    void printOutput();

    friend FileType;
};


#endif //BINARY_H
