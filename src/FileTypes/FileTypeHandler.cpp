#include "FileTypeHandler.h"

/* This method will choose the appropriate comparison method for the files and print their results */
void FileTypeHandler::ChooseFileType() {
    vector<File> files = H.getFiles();

    if(H.isBinary()){
        Binary b(H);
        b.compare();
        b.printOutput();
    }
    else if(files[0].IsText() && files[1].IsText()){
        Text t(H);
        t.compare();
        t.printOutput();
    }
    else if(files[0].IsHtml() && files[1].IsHtml()){
        Html h(H);
        h.compare();
        h.printOutput();
    }
    else{
        Binary b(H);
        b.compare();
        b.printOutput();
    }
}
