#ifndef SEMESTERPROJECT_FILETYPEHANDLER_H
#define SEMESTERPROJECT_FILETYPEHANDLER_H

#include "../InputHandling/FileHandler.h"
#include "FileType.h"
#include "Binary.h"
#include "Text.h"
#include "Html.h"

class FileTypeHandler {
private:
    FileHandler H;
public:
    FileTypeHandler(FileHandler &h): H(h) {}
    void ChooseFileType();
};


#endif //SEMESTERPROJECT_FILETYPEHANDLER_H
