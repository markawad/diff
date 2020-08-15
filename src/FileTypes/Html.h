#ifndef HTML_H
#define HTML_H

#include "Text.h"

class Html : public Text {
public:
    Html(FileHandler &h) : Text(h) {}

    void parseData();
};


#endif //HTML_H
