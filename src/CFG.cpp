#include "CFG.h"
#include "DFSTree.h"
#include "DominatorTree.h"
#include "ParseUtil.h"

#include <iostream>
#include <stack>
#include <set> 
#include <bits/stdc++.h>
#include <queue> 
#include <map> 

using namespace std; 

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
            if (curr_block.label == "main") entry_node_ = curr_block;
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

void CFG::AddVertex(BasicBlock a) {
    adj_[a] = std::list<BasicBlock>(); 
}

std::list<BasicBlock> CFG::GetAdjacent(BasicBlock b) const {
    if (adj_.find(b) == adj_.end()) return std::list<BasicBlock>();
    return adj_.at(b);
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

BasicBlock CFG::GetEntryNode() const {
    return entry_node_;
};

BasicBlock CFG::GetBlock(std::string label) {
    if (key_.find(label) == key_.end()) {
        return BasicBlock(); 
    } else {
        return key_[label]; 
    }
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

int CFG::NumConnectedComponents() const {
    int ans = 0;
    std::map<BasicBlock,int> visited;
    std::stack<BasicBlock> s;
    s.push(entry_node_);
    while (!s.empty()) {
        BasicBlock top = s.top();
        s.pop();
        visited[top] = 1;
        for (const BasicBlock &neighbor : GetAdjacent(top)) {
            if (!visited[neighbor]) s.push(neighbor);
        }

        if (!s.empty()) continue;
        ++ans;
        for (const auto &pair : adj_) {
            BasicBlock from = pair.first;
            if (!visited[from]) {
                s.push(from);
                break;
            }
        }
    }
    return ans;
}

DFSTree CFG::GenerateDFSTree() const {
    DFSTree dfs;
    dfs.entry_node_ = this->entry_node_;
    std::deque<std::pair<BasicBlock,BasicBlock>> s;
    for (const BasicBlock &neighbor : GetAdjacent(entry_node_)) {
        s.push_front({ neighbor, entry_node_ });
    }
    std::map<BasicBlock,int> visited;
    dfs.SetLabel(entry_node_, 1);
    int dfs_label = 2;
    while (!s.empty()) {
        std::pair<BasicBlock,BasicBlock> pair = s.back();
        BasicBlock curr = pair.first;
        BasicBlock predecessor = pair.second;
        s.pop_back();
        
        dfs.AddPredecessor(curr, predecessor);

        if (visited[curr]) continue;
        visited[curr] = 1;

        dfs.AddEdge(predecessor, curr);
        dfs.SetLabel(curr, dfs_label++);

        std::stack<std::pair<BasicBlock,BasicBlock>> tmp;
        for (const BasicBlock &neighbor : GetAdjacent(curr)) {
            tmp.push({neighbor,curr});
        }
        while (!tmp.empty()) {
            s.push_back(tmp.top());
            tmp.pop();
        }
    }
    dfs.PopulateAncestorKey();
    return dfs;
}

DominatorTree CFG::GenerateDominatorTree() const {
    DominatorTree dom_tree;
    DFSTree dfs_tree = this->GenerateDFSTree();

    return dom_tree;
}

std::vector<BasicBlock> CFG::DFS(){
   stack<BasicBlock> DFS_stack;

   // The entry node is the first node in the CFG
   BasicBlock start = GetEntryNode();
 
   std::set<BasicBlock> visited; 
   // make set of nodes
   // which will be used to keep track of the visited nodes
 
   std::vector<BasicBlock> ret;
 
   DFS_stack.push(start);
 
   while(!DFS_stack.empty()){
    // takes the first value off the stack and adds it to 
    // the vector to return and adds the label to the visited set
       BasicBlock top = DFS_stack.top();
       DFS_stack.pop();
       ret.push_back(top); 

       // gets all adjacent nodes to the Basic Block
       list<BasicBlock> adj_nodes = GetAdjacent(top);
 
       for(auto block : adj_nodes) {
           if (!visited.count(block)) {
            // adding to stack if not visited
            // and marking it visited
                DFS_stack.push(block);
                visited.insert(block);
           }
       }
   }
 
   return ret;
}

int CFG::Dijkstras(BasicBlock start, BasicBlock end) {
    // dummy basic block for all the blocks to point to as a predecessor
    BasicBlock dummy = BasicBlock("dummy"); 

    // map to keep track of distances
    map<BasicBlock, int> dist; 

    // map to keep track of the predecessors
    map<BasicBlock, BasicBlock> pred; 

    set<BasicBlock> visited; 

    for (auto p : adj_) {
        //setting all the Basic Blocks in our CFG with 
        //the max possible distance
        dist[p.first] = INT_MAX; 
        pred[p.first] = dummy; 
    }
    // set the distance of the start node to zero
    // and inserts start into the visited set 
    dist[start] = 0; 
    visited.insert(start); 
    
    // this is the queue that we will be using for Dijkstras
    // it does not need to be a heap/priority queue since the CFG is unweighted
    // this provides with a runtime of O(V + E) instead of O(E + VlogV)
    queue<BasicBlock> q; 
    q.push(start); 

    // iterates until the queue become empty or until we found the shortest path
    while(!q.empty()) {
        BasicBlock b = q.front(); 
        q.pop(); 
        
        // gets all adjacent nodes to the Basic Block
        list<BasicBlock> adj_nodes = GetAdjacent(b); 

        for (auto block : adj_nodes) {
            // checks to see if the block was visited
            if (!visited.count(block)) {
                visited.insert(block); 

                // sets it to the traversed distance + 1
                // marks the predecessor of the curr block
                // push the node into the queue
                dist[block] = dist[b] + 1; 
                pred[block] = b; 
                q.push(block); 

                // We can stop this dijkstras once we found
                // the end node

                if (block == end) {
                    return dist[block]; 
                }
            }
        }
    }

    // function returns -1 if dijkstras cannot find a path
    // between the starting and end nodes
    return -1; 
}

 
 

