#pragma once

#include "CFG.h"

// Depth-first-search spanning tree of inherited control-flow graph
class DFSTree : public CFG {
public:
    DFSTree();
    DFSTree(const std::string filename);

    void SetLabel(BasicBlock b, int label);
    void SetPredecessors(BasicBlock node, std::list<BasicBlock> predecessors);
    void PrintLabelling();

    int GetMaxLabel() const;
    BasicBlock GetSemidominator(BasicBlock b);
    std::map<BasicBlock, BasicBlock> ComputeSemidominators();
private:
    std::map<BasicBlock,int> labelling_;
    std::map<int,BasicBlock> reverse_labelling_;
    std::map<BasicBlock,std::list<BasicBlock>> predecessor_key_;
    int max_label_;
};