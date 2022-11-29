#pragma once

#include <vector>
#include <string>
#include <map>
#include <unordered_map>
#include <list>
#include <iostream>

// Basic block, i.e. sequentially executed instructions
struct BasicBlock {

    BasicBlock();
    BasicBlock(std::string label);
    BasicBlock(std::string label, std::vector<std::string> instructions, int lineNo);
    BasicBlock(const BasicBlock &other);
    
    BasicBlock &operator=(const BasicBlock &other);
    bool operator==(const BasicBlock &other) const;
    bool operator<(const BasicBlock &other) const;

    std::string label;
    std::vector<std::string> instructions;
    int lineNo;
};

std::ostream &operator<<(std::ostream &os, const BasicBlock &b);

// Directed, unweighted control flow graph
class CFG {
public:
    CFG();
    CFG(std::string filename);

    void AddEdge(BasicBlock a, BasicBlock b);
    std::list<BasicBlock> GetAdjacent(BasicBlock b);
    // returns true if edge exists from a to b
    bool AreConnected(BasicBlock a, BasicBlock b);

    void PrintAdj();
private:
    std::map<BasicBlock,std::list<BasicBlock>> adj_;
    BasicBlock entryNode;
};