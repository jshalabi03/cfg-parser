#include <iostream>

#include "ParseUtil.h"
#include "CFG.h"

using namespace std;
using namespace ParseUtil;

int main(int argc, char* argv[]) {
    
    CFG cfg("/workspaces/225FinalProject/data/index.s");
    cfg.PrintAdj();

    return 0;
}