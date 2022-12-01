#include "CFG.h"

#include "ParseUtil.h"

#include <iostream>

BasicBlock::BasicBlock():
    label("NULL"), instructions({}) { }

BasicBlock::BasicBlock(std::string label):
    label(label) { }

BasicBlock::BasicBlock(std::string label, 
                       std::vector<std::string> instructions):
    label(label), instructions(instructions) { }

BasicBlock::BasicBlock(const BasicBlock &other):
    label(other.label), instructions(other.instructions) { }
    
BasicBlock &BasicBlock::operator=(const BasicBlock &other) {
    label = other.label;
    instructions = other.instructions;
    return *this;
}

bool BasicBlock::operator==(const BasicBlock &other) const {
        return label == other.label 
                && instructions == other.instructions;
}

bool BasicBlock::operator<(const BasicBlock &other) const {
    return label < other.label;
}

std::vector<std::string> BasicBlock::GetOutgoingLabels() const {
    std::vector<std::string> res;
    for (const std::string &line : instructions) {
        auto pair = ParseUtil::GetInstruction(line);
        if (ParseUtil::IsJumpInstruction(pair.first)) {
            res.push_back(pair.second);
        }
    }
    return res;
}

std::ostream &operator<<(std::ostream &os, const BasicBlock &b) {
    os << b.label << '\n';
    for (const std::string &instruction : b.instructions) {
        os << '\t' << instruction << '\n';
    }
    return os;
}

CFG::CFG() { }

CFG::CFG(const std::string &filename) {
    ParseAssembly(filename);
    for (const auto &pair : key_) {
        const auto&[label, block] = pair;
        const std::vector<std::string> &outgoing_labels = block.GetOutgoingLabels();
        for (const std::string &label : outgoing_labels) {
            if (key_.find(label) == key_.end()) continue;
            AddEdge(block, key_[label]);
        }
    }
}

void CFG::ParseAssembly(const std::string &filename) {
    std::vector<std::string> vec = ParseUtil::GetLines(filename);
    BasicBlock curr_block("HEADER");
    for (unsigned idx = 0; idx < vec.size(); ++idx) {
        std::string curr_line = ParseUtil::Clean(vec[idx]);
        if (ParseUtil::IsLabel(curr_line)) {
            key_[curr_block.label] = curr_block;
            curr_block = BasicBlock(ParseUtil::GetLabelString(curr_line));
            continue;
        } 

        if (!curr_line.empty())
            curr_block.instructions.push_back(curr_line);
    }

    key_[curr_block.label] = curr_block;
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

bool CFG::AreConnected(std::string label_a, std::string label_b) {
    BasicBlock a = key_[label_a], b = key_[label_b];
    const std::list<BasicBlock> &adjacent = adj_[a];
    for (const BasicBlock &block : adjacent) {
        if (block == b) return true;
    }
    return false;
}

void CFG::PrintAdj() {
    for (const auto &pair : adj_) {
        std::cout << pair.first.label << ": ";
        for (const auto &block : pair.second)
            std::cout << block.label << ", ";
        std::cout << '\n';
    }
}

void CFG::PrintKey() {
    for (const auto &pair : key_) {
        std::cout << pair.first << '\n';
        std::cout << pair.second << "\n\n";
    }
}