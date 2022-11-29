#include "CFG.h"

#include "ParseUtil.h"

#include <iostream>

BasicBlock::BasicBlock():
    label("NULL"), instructions({}), lineNo(-1) { }

BasicBlock::BasicBlock(std::string label):
    label(label) { }

BasicBlock::BasicBlock(std::string label, 
                       std::vector<std::string> instructions, 
                       int lineNo):
    label(label), instructions(instructions), lineNo(lineNo) { }

BasicBlock::BasicBlock(const BasicBlock &other):
    label(other.label), instructions(other.instructions), lineNo(other.lineNo) { }
    
BasicBlock &BasicBlock::operator=(const BasicBlock &other) {
    label = other.label;
    instructions = other.instructions;
    lineNo = other.lineNo;
    return *this;
}

bool BasicBlock::operator==(const BasicBlock &other) const {
        return label == other.label 
                && instructions == other.instructions
                && lineNo == other.lineNo;
}

bool BasicBlock::operator<(const BasicBlock &other) const {
    return lineNo < other.lineNo;
}

std::ostream &operator<<(std::ostream &os, const BasicBlock &b) {
    return os << b.label;
}

CFG::CFG() { }

CFG::CFG(std::string filename) {

    
    
}

std::vector<BasicBlock> CFG::ParseAssembly(std::string filename) {
    std::vector<BasicBlock> result;
    std::vector<std::string> vec = GetLines(filename);
    BasicBlock curr_block("HEADER");
    for (unsigned idx = 0; idx < vec.size(); ++idx) {
        std::string curr_line = Clean(vec[idx]);
        if (IsLabel(curr_line)) {
            result.push_back(curr_block);
            curr_block = BasicBlock(GetLabelString(curr_line));
            continue;
        } 
        
        if (!curr_line.empty())
            curr_block.instructions.push_back(curr_line);
    }
    result.push_back(curr_block);
    return result;
}

void CFG::AddEdge(BasicBlock a, BasicBlock b) {
    adj_[a].push_back(b);
}

std::list<BasicBlock> CFG::GetAdjacent(BasicBlock b) {
    return adj_[b];
}

bool CFG::AreConnected(BasicBlock a, BasicBlock b) {
    const std::list<BasicBlock> &adjacent = adj_[a];
    for (const BasicBlock &block : adjacent) {
        if (block == b) return true;
    }
    return false;
}

void CFG::PrintAdj() {
    for (const auto &pair : adj_) {
        std::cout << pair.first << ": ";
        for (const auto &block : pair.second)
            std::cout << block << ", ";
        std::cout << '\n';
    }
}