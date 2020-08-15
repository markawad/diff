#ifndef DIRECTORY_H
#define DIRECTORY_H

#include "../InputHandling/FileHandler.h"
#include "OutputHandler.h"
#include <set>

class Directory {
private:
    FileHandler H;
    string name;
    set<string> files;
    set<string> directories;

public:
    Directory(FileHandler &h, const string &name);

    const string &getName() const;

    void setName(const string &name);

    void StoreFilesAndDirectories();

    friend OutputHandler;
};


#endif //DIRECTORY_H
