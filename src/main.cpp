#include <iostream>

#include "ParseUtil.h"
#include "CFG.h"

using namespace std;

int main(int argc, char* argv[]) {
    CFG cfg;
    vector<BasicBlock> vec = cfg.ParseAssembly("./data/index.s");
    for (auto i : vec) {
        cout << i << endl;
    }

    return 0;
}