#include "FileReader.h"

#include <fstream>
#include <stdexcept>

using namespace std;

FileReader::FileReader() {}

vector<string> FileReader::getLines(string filename) {
    string line;
    vector<string> res;

    ifstream ifs(filename);
    if (!ifs.is_open()) throw std::runtime_error("Bad IO");

    while (getline(ifs, line)) {
        res.push_back(line);
    }

    ifs.close();

    return res;
}
