#include "DFSTree.h"

DFSTree::DFSTree() { }

DFSTree::DFSTree(const std::string filename): CFG(filename) {
    *this = this->GenerateDFSTree();
}

void DFSTree::SetLabel(BasicBlock b, int label) {
    labelling_[b] = label;
}

void DFSTree::PrintLabelling() {
    for (const auto &pair : labelling_) {
        std::cout << pair.first.label << ": " << pair.second << '\n';
    }
}