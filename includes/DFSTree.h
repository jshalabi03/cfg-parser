#pragma once

#include "CFG.h"

// Depth-first-search spanning tree; subgraph of inherited CFG
class DFSTree : public CFG {
public:
    DFSTree();
    DFSTree(const std::string filename);

    void SetLabel(BasicBlock b, int label);
    void SetAncestors(BasicBlock node, std::list<BasicBlock> ancestors);
    void AddPredecessor(BasicBlock node, BasicBlock pred);
    void PrintLabelling();

    BasicBlock AncestorWithLowestSemi(BasicBlock b);

    int GetMaxLabel() const;
    void PopulateAncestorKey();
    void PrintAncestorKey();
    void PrintPredecessors();
    BasicBlock GetSemidominator(BasicBlock b);
    std::map<BasicBlock, BasicBlock> ComputeSemidominators();
private:
    std::map<BasicBlock,int> labelling_;
    std::map<int,BasicBlock> reverse_labelling_;
    std::map<BasicBlock,std::list<BasicBlock>> ancestor_key_;
    int max_label_;

    std::map<BasicBlock,std::list<BasicBlock>> pred_;
    std::map<BasicBlock,BasicBlock> semi_;

};