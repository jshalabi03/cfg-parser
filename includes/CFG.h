#pragma once

#include <vector>
#include <string>
#include <map>
#include <unordered_map>
#include <list>
#include <iostream>

class DFSTree;
class DominatorTree;

// Basic block, i.e. sequentially executed instructions
struct BasicBlock {

    BasicBlock();
    BasicBlock(std::string label);
    BasicBlock(std::string label, std::vector<std::string> instructions);
    BasicBlock(const BasicBlock &other);
    
    BasicBlock &operator=(const BasicBlock &other);
    bool operator==(const BasicBlock &other) const;
    bool operator<(const BasicBlock &other) const;

    std::vector<std::string> GetOutgoingLabels() const;

    std::string label;
    std::vector<std::string> instructions;
};

std::ostream &operator<<(std::ostream &os, const BasicBlock &b);

// Directed, unweighted control flow graph
class CFG {
public:
    CFG();
    CFG(const std::string &filename);

    void AddEdge(BasicBlock a, BasicBlock b);
    void AddVertex(BasicBlock a); 

    std::list<BasicBlock> GetAdjacent(BasicBlock b) const;

    // returns true if edge exists from a to b
    bool AreConnected(BasicBlock a, BasicBlock b);
    bool AreConnected(std::string a, std::string b);

    BasicBlock GetEntryNode() const;

    void PrintAdj();

    void PrintKey();

    DFSTree GenerateDFSTree() const;
    DominatorTree GenerateDominatorTree() const;

    int NumConnectedComponents() const;

protected:
    std::map<BasicBlock,std::list<BasicBlock>> adj_;
    BasicBlock entry_node_;

    // key_[label] returns basic block corresponding to label
    std::unordered_map<std::string,BasicBlock> key_;

    // populates key_
    void ParseAssembly(const std::string &filename);
};