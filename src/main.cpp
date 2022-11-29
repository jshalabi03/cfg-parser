#include <iostream>

#include "FileReader.h"
#include "CFG.h"

using namespace std;

int main(int argc, char* argv[]) {

    // FileReader fd;
    // vector<string> lines = fd.getLines("data/index.s");
    // for (string l : lines) {
    //     cout << l << endl;
    // }

    BasicBlock a("a"), b("b"), c("c"), d("d");

    CFG cfg;
    cfg.AddEdge(a, b);
    cfg.AddEdge(a, c);
    cfg.AddEdge(b, d);
    cfg.AddEdge(c, d);

    cfg.PrintAdj();

    return 0;
}