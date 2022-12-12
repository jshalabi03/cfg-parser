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

    BasicBlock AncestorWithLowestSemi(BasicBlock block);

    int GetMaxLabel() const;
    void PopulateAncestorKey();
    void PrintAncestorKey();
    void PrintPredecessors();
    BasicBlock GetSemidominator(BasicBlock b);
    std::map<BasicBlock, BasicBlock> ComputeSemidominators();

    void PrintIDom();

    // populate idom
    void LengauerTarjan();

    void SetSemi(BasicBlock a, int i);

public: // CHANGE BACK
    std::map<BasicBlock,int> labelling_;
    std::map<int,BasicBlock> reverse_labelling_;

    // maps blocks to its DFSTree ancestors
    std::map<BasicBlock,std::list<BasicBlock>> ancestor_key_;
    int max_label_;

    // maps blocks to its CFG immediate predecessors
    std::map<BasicBlock,std::list<BasicBlock>> pred_;

    // maps blocks to its semi doms label
    std::map<BasicBlock,int> semi_;

    // maps blocks to its immediate dominator
    std::map<BasicBlock,BasicBlock> idom_;

    // maps blocks to other blocks who share the same semidom
    std::map<BasicBlock,BasicBlock> samedom_;

    // bucket[w] = n if n's semidom is w
    std::map<BasicBlock,std::list<BasicBlock>> bucket_;

};