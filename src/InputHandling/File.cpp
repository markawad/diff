#include "File.h"

File::File() {
    name = "";
    ignoreText = false, equalText = false;
    removeWhitespace = false, removeUrl = false;
    textIgnored = "";
}

/* Getters and Setters for the private variables */
const string &File::getName() const {
    return name;
}

void File::setName(const string &name) {
    File::name = name;
}

const string &File::getOriginalName() const {
    return originalName;
}

void File::setOriginalName(const string &originalName) {
    File::originalName = originalName;
}

bool File::isDirectory() const {
    return directory;
}

void File::setDirectory(bool directory) {
    File::directory = directory;
}

bool File::IgnoreText() const {
    return ignoreText;
}

void File::setIgnoreText(bool ignoreText) {
    File::ignoreText = ignoreText;
}

bool File::EqualText() const {
    return equalText;
}

void File::setEqualText(bool equalText) {
    File::equalText = equalText;
}

bool File::RemoveWhitespace() const {
    return removeWhitespace;
}

void File::setRemoveWhitespace(bool removeWhitespace) {
    File::removeWhitespace = removeWhitespace;
}

bool File::RemoveUrl() const {
    return removeUrl;
}

void File::setRemoveUrl(bool removeUrl) {
    File::removeUrl = removeUrl;
}

const string &File::getTextIgnored() const {
    return textIgnored;
}

void File::setTextIgnored(const string &textIgnored) {
    File::textIgnored = textIgnored;
}

const pair<string, string> &File::getSameText() const {
    return sameText;
}

void File::setSameText(const pair<string, string> &p) {
    sameText = p;
}

/* A method that will check if the file is text */
bool File::IsText() const {
    const string txt = ".txt";

    auto it = originalName.rbegin();
    auto itTxt = txt.rbegin();

    // Check if file name has '.', if not found then it is treated as a text file
    if (originalName.find('.') == string::npos) {
        return true;
    }

    while (itTxt < txt.rend()) {
        if (*it++ != *itTxt++) {
            return false;
        }
    }
    return true;
}

/* A method that checks if the File is Html */
bool File::IsHtml() const {
    const string html = ".html";

    auto it = originalName.rbegin();
    auto itHtml = html.rbegin();

    // Check if last char is 'l', if it's not then it might end with .htm
    if (*it != *itHtml) {
        itHtml++;
    }

    while (itHtml < html.rend()) {
        if (*it++ != *itHtml++) {
            return false;
        }
    }
    return true;
}
