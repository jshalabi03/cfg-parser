#pragma once

#include "CFG.h"

// Depth-first-search spanning tree of inherited control-flow graph
class DFSTree : public CFG {
public:
    DFSTree();
    DFSTree(const std::string filename);

    void SetLabel(BasicBlock b, int label);
    void PrintLabelling();
private:
    std::map<BasicBlock, int> labelling_;
};