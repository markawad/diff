#include "OutputHandling/OutputHandler.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

int main(int argc, char *argv[]) {

    FileHandler h(argc, argv);
    OutputHandler f(h);
    f.DecideOutputTypes(h.files[0].getOriginalName(), h.files[1].getOriginalName());
    return 0;
}