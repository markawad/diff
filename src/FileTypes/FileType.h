#ifndef FILETYPE_H
#define FILETYPE_H

#include "../InputHandling/FileHandler.h"
#include <tuple>

class FileType {
protected:
    FileHandler H;

    // f1 line number, add/change/delete, f2 line number
    vector<tuple<int, char, int>> changes;

public:
    FileType(FileHandler &h);

    virtual void parseData() = 0;

    virtual void addElements(bool valueNotAdded1) = 0;

    virtual void deleteElements(bool valueNotAdded2) = 0;

    virtual void compare() = 0;

    virtual void printOutput() = 0;
};

#endif //FILETYPE_H
