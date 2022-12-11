#include "DFSTree.h"

#include <stack>
#include <list>
#include <stdexcept>
#include <iostream>

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

void DFSTree::SetAncestors(BasicBlock node, std::list<BasicBlock> ancestors) {
    ancestor_key_[node] = ancestors;
}

void DFSTree::PrintLabelling() {
    for (const auto &pair : labelling_) {
        std::cout << pair.first.label << ": " << pair.second << '\n';
    }
}

int DFSTree::GetMaxLabel() const {
    return max_label_;
}

void DFSTree::PopulateAncestorKey() {
    std::stack<std::pair<BasicBlock,std::list<BasicBlock>>> s;
    s.push({entry_node_, {}});
    std::map<BasicBlock,int> visited;
    while (!s.empty()) {
        auto top = s.top();
        BasicBlock curr = top.first;
        s.pop();
        if (visited[curr]) continue;
        visited[curr] = 1;
        std::list<BasicBlock> ancestors = top.second;
        ancestor_key_[curr] = ancestors;
        ancestors.push_back(curr);
        for (const auto &neighbor : adj_[curr]) {
            if (!visited[neighbor])
                s.push({neighbor, ancestors});
        }
    }
}

void DFSTree::PrintAncestorKey() {
    for (const auto &pair : ancestor_key_) {
        std::cout << pair.first.label << ": ";
        for (const auto &block : pair.second) {
            std::cout << block.label << ", ";
        }
        std::cout << '\n';
    }
}

BasicBlock DFSTree::GetSemidominator(BasicBlock b) {
    // The semidominator of the root is the root itself
    if (b == GetEntryNode()) 
        return b;

    BasicBlock sdom(b);
    

    return sdom;
}

std::map<BasicBlock, BasicBlock> DFSTree::ComputeSemidominators() {
    std::map<BasicBlock,BasicBlock> mp;

    return mp;
}

void DFSTree::AddPredecessor(BasicBlock node, BasicBlock pred) {
    pred_[node].push_back(pred);
}

BasicBlock DFSTree::AncestorWithLowestSemi(BasicBlock label) {

}

void DFSTree::PrintPredecessors() {
    for (const auto &pair : pred_) {
        std::cout << pair.first.label << ": ";
        for (const auto &pred : pair.second)
            std::cout << pred.label << ", ";
        std::cout << '\n';
    }
}