#pragma once

#include <vector>
#include <string>

using namespace std;

struct BasicBlock {
    string label;
    vector<string> instructions;
};

class CFG {
public:
private:
    vector<vector<BasicBlock>> adj_;
};