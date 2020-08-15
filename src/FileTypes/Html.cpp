#include "Html.h"
#include <fstream>

/* This method is an adjustment on Text::parseData, as it will not take into consideration the extra '\n'
 * from the paragraph */
void Html::parseData() {
    vector<File> files = H.getFiles();

    string f1name = files[0].getName();
    string f2name = files[1].getName();

    string temp;

    ifstream in1, in2;
    in1.open(f1name);
    in2.open(f2name);

    // Add file1 contents to f1 vector, newline delimiter
    while (!in1.eof()) {
        if (in1.fail()) {
            break;
        }
        getline(in1, temp);
        f1.emplace_back(temp);
    }
    if (f1.rbegin()->empty()) {
        f1.pop_back();
    }
    // Add file2 contents to f2 vector, newline delimiter
    while (!in2.eof()) {
        if (in2.fail()) {
            break;
        }
        getline(in2, temp, '\n');
        f2.emplace_back(temp);
    }
    if (f2.rbegin()->empty()) {
        f2.pop_back();
    }
}