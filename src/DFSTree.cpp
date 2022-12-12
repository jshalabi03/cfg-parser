#include "DFSTree.h"

#include <stack>
#include <list>
#include <stdexcept>
#include <iostream>

using std::cout;

DFSTree::DFSTree() { }

DFSTree::DFSTree(const std::string filename): CFG(filename) {
    *this = this->GenerateDFSTree();
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

void DFSTree::AddPredecessor(BasicBlock node, BasicBlock pred) {
    pred_[node].push_back(pred);
}

BasicBlock DFSTree::AncestorWithLowestSemi(BasicBlock block) {
    BasicBlock res = block;
    for (const auto &ancestor : ancestor_key_[block]) {
        if (semi_[ancestor] < labelling_[res])
            res = ancestor;
    }
    return res;
}

void DFSTree::PrintPredecessors() {
    for (const auto &pair : pred_) {
        std::cout << pair.first.label << ": ";
        for (const auto &pred : pair.second)
            std::cout << pred.label << ", ";
        std::cout << '\n';
    }
}

void DFSTree::LengauerTarjan() {
    for (int i = max_label_; i >= 1; --i) {
        BasicBlock n = reverse_labelling_[i];
        BasicBlock p = ancestor_key_[n].back();
        BasicBlock s = p;

        for (const BasicBlock &v : pred_[n]) {
            BasicBlock sPrime = labelling_[v] <= labelling_[n]
                ? v
                : reverse_labelling_[semi_[AncestorWithLowestSemi(v)]];
            if (labelling_[sPrime] < labelling_[s])
                s = sPrime;
        }

        semi_[n] = labelling_[s];
        bucket_[s].push_back(n);
        if (!(ancestor_key_[n].back() == p)) ancestor_key_[n].push_back(p);

        for (const auto &v : bucket_[p]) {
            BasicBlock y = AncestorWithLowestSemi(v);
            if (semi_[y] == semi_[v]) {
                idom_[v] = p;
            } else {
                samedom_[v] = y;
            }
        }
        bucket_[p].clear();
    }

    for (int i = 1; i <= max_label_; ++i) {
        BasicBlock n = reverse_labelling_[i];
        if (samedom_.find(n) != samedom_.end()) {
            idom_[n] = idom_[samedom_[n]];
        }
    }


}

void DFSTree::SetSemi(BasicBlock a, int i) {
    semi_[a] = i;
}

void DFSTree::PrintIDom() {
    for (const auto &pair : idom_) {
        std::cout << pair.first.label << ": ";
        std::cout << pair.second.label << '\n';
    }
}