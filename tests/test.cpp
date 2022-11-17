#include <cassert>

#include "FileReader.h"

int main() {
    
    // FileReader Tests
    {
        FileReader fd;
        std::vector<std::string> vec = fd.getLines("/workspaces/225FinalProject/data/a.s");
        assert(vec.size() == 16);
        assert(vec[9] == "\tmov	w0, #0");
    }

    return 0;
}