#ifndef FILE_H
#define FILE_H

#include <iostream>
#include <string>

using namespace std;

class File {
private:
    string name;

    string originalName;

    bool directory = false;

    bool ignoreText = false, equalText = false;

    bool removeWhitespace = false, removeUrl = false;

    string textIgnored;

    pair<string, string> sameText;

public:
    File();

    const string &getName() const;

    void setName(const string &name);

    const string &getOriginalName() const;

    void setOriginalName(const string &originalName);

    bool isDirectory() const;

    void setDirectory(bool directory);

    bool IgnoreText() const;

    void setIgnoreText(bool ignoreText);

    bool EqualText() const;

    void setEqualText(bool equalText);

    bool RemoveWhitespace() const;

    void setRemoveWhitespace(bool removeWhitespace);

    bool RemoveUrl() const;

    void setRemoveUrl(bool removeUrl);

    const string &getTextIgnored() const;

    void setTextIgnored(const string &textIgnored);

    const pair<string, string> &getSameText() const;

    void setSameText(const pair<string, string> &p);

    bool IsText() const;

    bool IsHtml() const;
};

#endif //FILE_H
