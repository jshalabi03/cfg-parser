#include <iostream>

#include "FileReader.h"

using namespace std;

int main(int argc, char* argv[]) {

    FileReader fd;
    vector<string> lines = fd.getLines("data/index.s");
    for (string l : lines) {
        cout << l << endl;
    }

    return 0;
}