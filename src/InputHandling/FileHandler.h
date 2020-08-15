#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include "File.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <cstdio>
#include <string>
#include "dirent.h"

using namespace std;

class FileHandler {
private:
    int argc = 0;

    bool binary = false;

    bool recursive = false;

    vector<string> arguments;

public:
    vector<File> files;

    FileHandler(int argc, char *argv[]);

    void ErrorMessage(int i) const;

    void DisplayErrorPage() const;

    void DisplayHelp() const;

    void CheckIfEndOfVector(vector<string>::iterator position, const int count) const;

    void CheckIfFileExists(int i);

    bool isDirectory(const string &name) const;

    void addForwardSlash(File &f) const;

    void ArgumentIsRepeated() const;

    void ValidateParameters();

    const vector<File> &getFiles() const;

    bool isBinary() const;

    bool isRecursive() const;

    void deleteOldFile(File &f, string &oldName, string &newName) const;

    void IgnoreString(const string &src, File &f) const;

    void RemoveWhiteSpace(File &f) const;

    void RemoveUrl(File &f) const;

    void EqualString(const string &src1, const string &src2, File &f) const;

    void FixAttributeOrder(File &f) const;

    void UpdateFiles();
};


#endif //FILEHANDLER_H
