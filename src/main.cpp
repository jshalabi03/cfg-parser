#include <iostream>

#include "ParseUtil.h"
#include "CFG.h"

using namespace std;
using namespace ParseUtil;

int main(int argc, char* argv[]) {
    CFG cfg("./data/index.s");
    cfg.PrintAdj();

    // cfg.PrintAdj();
    // vector<BasicBlock> vec = cfg.ParseAssembly("./data/index.s");
    // for (auto i : vec) {
    //     cout << i << endl;
    // }

    return 0;
}