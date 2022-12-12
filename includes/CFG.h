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
    BasicBlock(std::string label, int id);
    BasicBlock(std::string label, std::vector<std::string> instructions);
    BasicBlock(const BasicBlock &other);
    
    BasicBlock &operator=(const BasicBlock &other);
    bool operator==(const BasicBlock &other) const;
    bool operator<(const BasicBlock &other) const;

    std::vector<std::string> GetOutgoingLabels() const;

    std::string label;
    std::vector<std::string> instructions;
    int id;
};

std::ostream &operator<<(std::ostream &os, const BasicBlock &b);

// Directed, unweighted control flow graph
class CFG {
public:
    CFG();
    CFG(const std::string &filename);

    // Adds directed edge from a to b
    void AddEdge(BasicBlock a, BasicBlock b);
    // Adds lone vertex to graph
    void AddVertex(BasicBlock a); 

    // Adjacency and predecessor list getter functions
    std::list<BasicBlock> GetAdjacent(BasicBlock b) const;
    std::list<BasicBlock> GetAdjacent(std::string b) const;
    std::list<BasicBlock> GetPredecessors(BasicBlock b) const;
    std::list<BasicBlock> GetPredecessors(std::string b) const;

    // returns true if edge exists from a to b
    bool AreConnected(BasicBlock a, BasicBlock b);
    bool AreConnected(std::string a, std::string b);

    BasicBlock GetEntryNode() const;
    // returns basic block for given label using key
    BasicBlock GetBlock(std::string label); 

    // Prints functions for private members
    void PrintAdj();
    void PrintPred();
    void PrintKey();
    void PrintIDs();

    // Computes number of connected components in graph
    int NumConnectedComponents() const;

    // runs a DFS traversal outputting a vector of Basic Blocks
    std::vector<BasicBlock> DFS();

    int Dijkstras(BasicBlock start, BasicBlock end); 
    int Dijkstras(std::string start, std::string end);

    // returns immediate dominator for block b
    BasicBlock GetImmediateDominator(BasicBlock b);
    BasicBlock GetImmediateDominator(std::string b);

private: 
    // for each basic block, holds a list of all adjacent nodes
    std::map<BasicBlock,std::list<BasicBlock>> adj_;
    BasicBlock entry_node_;
    int num_nodes_;

    // maps basic block to list of its predecessors
    std::map<BasicBlock,std::list<BasicBlock>> pred_;

    // key_[label] returns basic block corresponding to label
    std::unordered_map<std::string,BasicBlock> key_;

    // maps basicblock labels to arbitrary id for use in dfs tree generation
    std::map<std::string,int> id_;
    // maps abitrary ids to basicblock labels
    std::vector<std::string> reverse_id_;

    // populates key_
    void ParseAssembly(const std::string &filename);

    // Uses the Lengauer-Tarjan algorithm to compute the immediate
    // dominators of each node
    std::map<BasicBlock,BasicBlock> ComputeImmediateDominators();
    std::map<BasicBlock,BasicBlock> idom_rels_;

};