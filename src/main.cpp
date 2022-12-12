#include <iostream>

#include "ParseUtil.h"
#include "CFG.h"

using namespace std;
using namespace ParseUtil;

int main(int argc, char* argv[]) {
    
    CFG cfg("/workspaces/225FinalProject/data/index.s");

    while (true) {
        cout << "Pick one of the following options:\n";
        cout << "\t0 - Quit\n";
        cout << "\t1 - DFS Traversal\n";
        cout << "\t2 - Compute Dijkstra's Shortest Path Distance\n";
        cout << "\t3 - Compute Immediate Dominator\n";
        int option;
        cin >> option;

        if (option == 1) {
            cout << "_______________________________\n\n";
            vector<BasicBlock> dfs = cfg.DFS();
            for (const auto &block : dfs) {
                cout << block.label << " -> ";
            }
            cout << "NULL\n";

        } else if (option == 2) {

            cout << "Enter two basic block labels to compute the shortest path distance between eachother: ";
            string a, b;
            cin >> a >> b;
            cout << "_______________________________\n\n";
            cout << "The shortest path distance between block " << a << " and block " << b << " is " << cfg.Dijkstras(a,b) << '\n';

        } else if (option == 3) {

            cout << "Enter a basic block label to compute the immediate dominator of it: ";
            string a;
            cin >> a;
            cout << "_______________________________\n\n";
            cout << "The immediate dominator of block " << a << " is " << cfg.GetImmediateDominator(a).label << '\n';

        } else {
            cout << "_______________________________\n\n";
            return 0;
        }

        cout << "_______________________________\n\n";
    }

    return 0;
}