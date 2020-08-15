#ifndef SEMESTERPROJECT_OUTPUTHANDLER_H
#define SEMESTERPROJECT_OUTPUTHANDLER_H

#include "../InputHandling/FileHandler.h"

class OutputHandler {
private:
    FileHandler H;

public:
    OutputHandler(FileHandler &h);

    void DecideOutputTypes(const string &dir1, const string &dir2);
};


#endif //SEMESTERPROJECT_OUTPUTHANDLER_H
