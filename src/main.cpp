#include <iostream>

#include "ParseUtil.h"
#include "CFG.h"
#include "DFSTree.h"

using namespace std;
using namespace ParseUtil;

int main(int argc, char* argv[]) {
    
    CFG cfg("/workspaces/225FinalProject/data/index.s");
    // DFSTree dfs_tree = cfg.GenerateDFSTree();

    cfg.PrintAdj();
    cout << "\n\n\n";
    // dfs_tree.PrintAdj();

    // dfs_tree.PrintLabelling();
    // cout << "\n\n\n";
    // dfs_tree.PrintAncestorKey();

    // dfs_tree.PrintPredecessors();

    // dfs_tree.LengauerTarjan();
    // cout << dfs_tree.max_label_ << endl;

    // dfs_tree.PrintIDom();

    return 0;
}