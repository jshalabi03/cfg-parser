#ifndef FILE_READER_H
#define FILE_READER_H

#include <string>
#include <vector>

using std::string, std::vector;

class FileReader {
public:
    FileReader();
    vector<string> getLines(string filename);
private:

};

#endif