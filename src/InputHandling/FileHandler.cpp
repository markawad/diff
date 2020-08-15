#include "FileHandler.h"
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <set>

using namespace std;

/* A constructor that adds the Number of Arguments and the parameters to the FileHandler Object and validates the parameters */
FileHandler::FileHandler(int argc, char *argv[]) : argc(argc) {
    for (int i = 0; i < argc; i++) {
        FileHandler::arguments.emplace_back(argv[i]);
    }
    ValidateParameters();
}

/* Displays the error message and exits from the program */
void FileHandler::ErrorMessage(int i) const {
    cout << "use -help for instructions on how to use the program." << endl;
    exit(i);
}

/* Displays the ErrorOut page and exists the program */
void FileHandler::DisplayErrorPage() const {
    ifstream in("src/HelpPages/ErrorOut.txt");
    cout << in.rdbuf();
    exit(1);
}

/* Displays the help page and exits the program */
void FileHandler::DisplayHelp() const {
    ifstream in("src/HelpPages/help.txt");
    cout << in.rdbuf();
    exit(0);
}

/* Checks if Iterator position + count is greater than the end of argv vector and returns error if it is
 * eg user could be having:
 * ./diff file1 -ig file2
 * since -ig does not have a text to ignore, we show the user error output page */
void FileHandler::CheckIfEndOfVector(vector<string>::iterator position, const int count) const {
    *position += count;
    if (position >= arguments.end()) {
        DisplayErrorPage();
    }
}

/* Checks if the name is actually a directory and marks it as such */
bool FileHandler::isDirectory(const string &name) const {
    DIR *dp;
    const char *cstr = &name[0u];
    dp = opendir(cstr);

    bool res = dp != nullptr;

    delete dp;
    return res;
}

/* Adds a forward slash to the end of the directory to be compared (if '/' was not added yet) */
void FileHandler::addForwardSlash(File &f) const {
    string name = f.getName();
    if (name[name.size() - 1] != '/') {
        name += "/";
        f.setName(name);
        f.setOriginalName(name);
    }
}

/* Checks if the file exists, if not it might be a directory, so check if it is */
void FileHandler::CheckIfFileExists(int i) {
    ifstream in(files[i].getName());
    in.get();
    if (!in) {
        if (isDirectory(files[i].getName())) {
            files[i].setDirectory(true);
            addForwardSlash(files[i]);
        } else {
            cout << files[i].getName() << " Could not be opened or does not exist." << endl;
            ErrorMessage(4);
        }
    }
}

/* Error Message for when an argument is repeated for the same file. */
void FileHandler::ArgumentIsRepeated() const {
    cout << "Cannot repeat arguments for the same file." << endl;
    ErrorMessage(7);
}

/* Checks Parameters and stores them in bool variables */
void FileHandler::ValidateParameters() {
    File tmp;

    if (argc < 3) {
        FileHandler::DisplayHelp();
    }

    for (auto it = arguments.begin() + 1; it < arguments.end(); it++) {
        // Validates the last elements in the parameters after entering the second file
        if (files.size() == 2) {
            // If files are added, and there are more than one arguments left, then there is an error
            if ((long) arguments.size() > (it - arguments.begin()) + 1) {
                cout << "Too many arguments" << endl;
                ErrorMessage(2);
            } else if (*it == "-out=binary" || *it == "-out=bin") {
                binary = true;
                return;
            }
        }
        if (*it == "-help" || *it == "-h") {
            DisplayHelp();
        }
        else if (*it == "-ignore" || *it == "-ig") {
            if (tmp.IgnoreText()) { ArgumentIsRepeated(); }

            tmp.setIgnoreText(true);
            CheckIfEndOfVector(it, 1);

            // Value incremented to add the next string in the textIgnored variable;
            tmp.setTextIgnored(*++it);
        }
        else if (*it == "-equal" || *it == "-eq") {
            if (tmp.EqualText()) { ArgumentIsRepeated(); }

            tmp.setEqualText(true);
            CheckIfEndOfVector(it, 2);

            // Value incremented to the next two strings that are the same
            tmp.setSameText(make_pair(*++it, *++it));
        }
        else if (*it == "-w") {
            if (tmp.RemoveWhitespace()) { ArgumentIsRepeated(); }
            tmp.setRemoveWhitespace(true);
        }
        else if (*it == "-u") {
            if (tmp.RemoveUrl()) { ArgumentIsRepeated(); }
            tmp.setRemoveUrl(true);
        }
        else if (*it == "-out=binary" || *it == "-out=bin") {
            cout << "Cannot explicitly set output before adding both files." << endl;
            ErrorMessage(6);
        }
        else if (*it == "-r") {
            recursive = true;
        }
        else {
            // Storing the file in the vector and reinitialzing the tmp File
            tmp.setName(*it);
            tmp.setOriginalName(*it);
            files.push_back(tmp);
            tmp = File();

            // Check if file actually exists
            CheckIfFileExists(files.size() - 1);

            // Check if more than two files were added
            if (files.size() > 2) {
                cout << "More than two files were added." << endl;
                ErrorMessage(3);
            }
            if (files.size() == 2) {
                // Check if files are the same
                if (files[0].getName() == files[1].getName()) {
                    cout << "Cannot compare if the Directories/files are the same." << endl;
                    ErrorMessage(5);
                }
                // Check if One is a directory and the other is a file
                if ((files[0].isDirectory() && !files[1].isDirectory()) ||
                    (!files[0].isDirectory() && files[1].isDirectory())) {
                    cout << "Cannot compare a Directory with a file." << endl;
                    ErrorMessage(8);
                }
            }
        }
    }
    if(files.size() != 2){
        cout << "Too few arguments." << endl;
        DisplayErrorPage();
    }

    if (isRecursive() && !files[0].isDirectory()) {
        cout << "Cannot be in a recursive mode on a file." << endl;
        ErrorMessage(9);
    }
}

const vector<File> &FileHandler::getFiles() const {
    return files;
}

bool FileHandler::isBinary() const {
    return binary;
}

bool FileHandler::isRecursive() const {
    return recursive;
}

/* The next set of methods would be used according to the parameters of the file, so when the actual comparison
 * occurs, I do not have to worry about all the parameters and just have the file ready to be compared. */

/* This method deletes the old modified file but not the original file
 * There will always be a copy in the end with all the recorded changes.
 *
 * eg: file -> IgnoreString
 *     newName = file.
 *     file. -> RemoveUrl
 *     newName = file..
 *     rm file. and rename file.. to file.
 * Final file changes would not be deleted so that the user can see the changes if they want */
void FileHandler::deleteOldFile(File &f, string &oldName, string &newName) const {
    if (oldName[oldName.size() - 1] == '.') {
        const char *cstr1 = &oldName[0u];
        const char *cstr2 = &newName[0u];

        remove(cstr1);
        rename(cstr2, cstr1);

        f.setName(oldName);
    }
}

/* This method goes through the input file and removes every occurrence of the string src */
void FileHandler::IgnoreString(const string &src, File &f) const {
    // Input Stream
    string fileName = f.getName();
    ifstream in;
    in.open(fileName);

    // Output Stream
    string outputFileName = fileName + '.';
    f.setName(outputFileName);
    ofstream out;
    out.open(outputFileName);

    char tmp;
    auto it = src.begin();

    /* appending matching chars not stored in the output, just in case the ignored word is not
     * a complete match which in this case we would add the tmpWord to output. */
    string tmpWord;

    while (!in.eof()) {
        tmp = in.get();
        if (in.fail()) {
            return;
        }
        if (tmp == *it) {
            tmpWord += *it++;
        } else {
            it = src.begin();
            out << tmpWord;
            tmpWord = "";
            out << tmp;
        }
        if (it == src.end()) {
            it = src.begin();
            tmpWord = "";
        }
    }
    deleteOldFile(f, fileName, outputFileName);
}

/* A method to remove all whitespaces from the file if it was a text file, or
 * if explicitly specified with the parameter -w */
void FileHandler::RemoveWhiteSpace(File &f) const {
    // Input Stream
    string fileName = f.getName();
    ifstream in;
    in.open(fileName);

    // Output Stream
    string outputFileName = fileName + '.';
    f.setName(outputFileName);
    ofstream out;
    out.open(outputFileName);

    char tmpChar;
    short counter = 0;

    while (!in.fail()) {
        tmpChar = in.get();
        if (in.fail()) {
            deleteOldFile(f, fileName, outputFileName);
            return;
        }
        if (tmpChar != ' ' && tmpChar != '\t' && tmpChar != '\n') {
            out << tmpChar;
        } else if (tmpChar == '\n') {
            counter++;
            while (true) {
                tmpChar = in.get();
                if (in.fail()) {
                    deleteOldFile(f, fileName, outputFileName);
                    return;
                }
                if (tmpChar == '\n') {
                    counter++;
                    if (counter == 2) {
                        counter = 0;
                        out << "\n\n";
                    }
                } else if (tmpChar == ' ' || tmpChar == '\t') {
                    counter = 0;
                    break;
                } else {
                    out << tmpChar;
                    counter = 0;
                    break;
                }
            }
        }
    }
    deleteOldFile(f, fileName, outputFileName);
}

/* This method removes all of the links starting with http* from the file */
void FileHandler::RemoveUrl(File &f) const {
    // Input Stream
    string fileName = f.getName();
    ifstream in;
    in.open(fileName);

    // Output Stream
    string outputFileName = fileName + '.';
    f.setName(outputFileName);
    ofstream out;
    out.open(outputFileName);

    char tmpChar;
    string tmpWord, http = "http";
    bool found = true;

    while (!in.eof()) {
        tmpWord = "";
        tmpChar = in.get();
        if (in.fail()) {
            deleteOldFile(f, fileName, outputFileName);
            return;
        }
        tmpWord += tmpChar;
        if (tmpChar == http[0]) {
            found = true;
            for (int i = 1; i < 4; i++) {
                tmpChar = in.get();
                tmpWord += tmpChar;
                if (tmpChar != http[i]) {
                    out << tmpWord;
                    found = false;
                    break;
                }
            }
            if (found) {
                in >> tmpWord;
            }
        } else {
            out << tmpChar;
        }
    }
    deleteOldFile(f, fileName, outputFileName);
}

/* This method will replace second string with the first one of the file f */
void FileHandler::EqualString(const string &src1, const string &src2, File &f) const {
    // Input Stream
    string fileName = f.getName();
    ifstream in;
    in.open(fileName);

    // Output Stream
    string outputFileName = fileName + '.';
    f.setName(outputFileName);
    ofstream out;
    out.open(outputFileName);

    auto it = src2.begin();
    char tmpChar;
    string tmpWord;

    while (!in.eof()) {
        tmpChar = in.get();
        if (in.fail()) {
            deleteOldFile(f, fileName, outputFileName);
            return;
        }
        if (tmpChar == *it) {
            tmpWord += *it++;
        } else {
            out << tmpWord;
            out << tmpChar;
            tmpWord = "";
            it = src2.begin();
        }
        if (it == src2.end()) {
            it = src2.begin();
            out << src1;
            tmpWord = "";
        }
    }
    deleteOldFile(f, fileName, outputFileName);
}

/* This method will adjust the attribute order of an HTML file so that the attributes start
 * from ascending order It will be used to match the attribute order of the other file */
void FileHandler::FixAttributeOrder(File &f) const {
    // with every '<' bracketCounter increments and with '>' it decrements
    int bracketCounter = 0;

    int singleQuotations = 0, doubleQuotaions = 0;

    string fileName = f.getName();

    ifstream in;
    in.open(fileName);

    string outputFileName = f.getName() + '.';
    f.setName(outputFileName);
    ofstream out;
    out.open(outputFileName);

    char c;
    string tmpAttribute;

    // A compare function that will also add the repeated arguments just in case need be.
    auto compare = [](const string &lhs, const string &rhs) { return lhs <= rhs; };
    set<string, decltype(compare)> attributes(compare);
    while (!in.eof()) {
        c = in.get();
        if (in.fail()) {
            deleteOldFile(f, fileName, outputFileName);
            return;
        }

        singleQuotations = c == '\'' ? singleQuotations + 1 : singleQuotations;
        doubleQuotaions = c == '\"' ? doubleQuotaions + 1 : doubleQuotaions;

        if (c == '<') {
            // odd number of quotations so '<' is considered as part of text
            if (singleQuotations % 2 == 1 || doubleQuotaions % 2 == 1) {
                out << c;
            } else {
                if (bracketCounter == 0) {
                    out << c;
                }
                bracketCounter++;
                tmpAttribute = "<";
            }
        } else if (c == '>') {
            // If it is between quotations then it is part of the text
            if (singleQuotations % 2 == 1 || doubleQuotaions % 2 == 1) {
                out << c;
            } else {
                bracketCounter--;
            }
            // found an attribute in the middle, added to the set
            if (bracketCounter > 0) {
                tmpAttribute += '>';
                attributes.emplace(tmpAttribute);
            }
                // it is the last bracket that holds all the attributes
            else {
                for (auto &attr : attributes) {
                    out << attr;
                }
                attributes.clear();
                out << c;
            }
        } else {
            // print the char if it is not in the attributes bracket
            if (bracketCounter == 0) {
                out << c;
            }// If attributes inside the bracket, whitespaces do not matter
            else if (bracketCounter == 1) {
                if (c != ' ' && c != '\t' && c != '\n') {
                    out << c;
                }
            } else {
                tmpAttribute += c;
            }
        }
    }
    deleteOldFile(f, fileName, outputFileName);
}

/* This method will check and apply all of the changes in the parameters for both files */
void FileHandler::UpdateFiles() {
    // A for loop to go through both files
    for (auto &file : files) {
        if (file.IgnoreText()) {
            IgnoreString(file.getTextIgnored(), file);
        }
        if (file.RemoveUrl()) {
            RemoveUrl(file);
        }
        if (file.RemoveWhitespace() || file.IsText()) {
            RemoveWhiteSpace(file);
        }
        if (file.IsHtml()) {
            FixAttributeOrder(file);
        }
    }
    /* Switch is being added to check if the file2 has the same -equal parameter strings as file1 but
     * in different order, so I will switch the order up.
     * eg: -eq "hey" "hello" file1 -eq "hello" "hey" file2
     * will be treated as:
     *     -eq "hey" "hello" file1 -eq "hey" "hello" file2 */
    if (files[0].EqualText() || files[1].EqualText()) {
        pair<string, string> s1 = files[0].getSameText();
        pair<string, string> s2 = files[1].getSameText();

        // Ignore the -eq parameter if the text is the same
        bool ignoreF1 = s1.first == s1.second || !files[0].EqualText();
        bool ignoreF2 = s2.first == s2.second || !files[1].EqualText();
        int i;
        i = !ignoreF1 && ignoreF2 ? 0 : ignoreF1 && !ignoreF2 ? 1 : s1.first == s2.second ? 2 :
        s1.second == s2.first ? 3 : s1.second == s2.second ? 4 : 5;

        switch (i) {
            case 0:
                // Equal Strings on first file only
                EqualString(s1.first, s1.second, files[0]);
                break;
            case 1:
                // Equal Strings on second file only
                EqualString(s2.first, s2.second, files[1]);
                break;
                // Equal Strings on both files, where first parameters are the same word
            case 2:
                EqualString(s1.first, s1.second, files[0]);
                EqualString(s2.second, s2.first, files[1]);
                break;
            case 3:
                EqualString(s1.second, s1.first, files[0]);
                EqualString(s2.first, s2.second, files[1]);
                break;
            case 4:
                EqualString(s1.second, s1.first, files[0]);
                EqualString(s2.second, s2.first, files[1]);
                break;
            case 5:
                EqualString(s1.first, s1.second, files[0]);
                EqualString(s2.first, s2.second, files[1]);
                break;
        }
    }
}
