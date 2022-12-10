#include "DFSTree.h"

#include <stdexcept>

DFSTree::DFSTree() { }

DFSTree::DFSTree(const std::string filename): CFG(filename) {
    *this = this->GenerateDFSTree();
    for (const auto &pair : labelling_)
        max_label_ = std::max(max_label_, pair.second);
}

void DFSTree::SetLabel(BasicBlock b, int label) {
    labelling_[b] = label;
    reverse_labelling_[label] = b;
}

void DFSTree::SetPredecessors(BasicBlock node, std::list<BasicBlock> predecessors) {
    predecessor_key_[node] = predecessors;
}

void DFSTree::PrintLabelling() {
    for (const auto &pair : labelling_) {
        std::cout << pair.first.label << ": " << pair.second << '\n';
    }
}

int DFSTree::GetMaxLabel() const {
    return max_label_;
}

BasicBlock DFSTree::GetSemidominator(BasicBlock b) {
    if (b == GetEntryNode()) 
        throw std::runtime_error("Cannot compute semidominator of entry node.");

    BasicBlock semi(b);
    for (int label = max_label_; label > 1; --label) {

    }

    return semi;
}

std::map<BasicBlock, BasicBlock> DFSTree::ComputeSemidominators() {
    std::map<BasicBlock,BasicBlock> mp;

    return mp;
}