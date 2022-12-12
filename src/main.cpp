#include <iostream>

#include "ParseUtil.h"
#include "CFG.h"

using namespace std;
using namespace ParseUtil;

int main(int argc, char* argv[]) {
    
    CFG cfg("/workspaces/225FinalProject/data/test.s");

    std::string label_main = "main",
                label_1 = ".LBB5_1",
                label_2 = ".LBB5_2",
                label_3 = ".LBB5_3",
                label_4 = ".LBB5_4",
                label_f0 = "_Z2f0i",
                label_f1 = "_Z2f1i",
                label_f2 = "_Z2f2i",
                label_nc = "_Z10not_calledi";

    cout << cfg.GetAdjacent(label_main).size() << endl;
    cout << (cfg.GetAdjacent(label_main).size() == 4) << endl;

    return 0;
}