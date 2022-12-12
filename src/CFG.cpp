#include "CFG.h"
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

BasicBlock::BasicBlock(std::string label, int id):
    label(label), id(id) { }

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

    // Erase keys that are not apart of graph, populate id_, reverse_id_
    int idx = 0;
    for (auto it = key_.begin(); it != key_.end();) {
        BasicBlock b = it->second;
        if (adj_.find(b) == adj_.end()
            && pred_.find(b) == pred_.end()) {
                auto next = std::next(it);
                key_.erase(it);
                it = next;
        } else {
            id_[it->second.label] = idx++;
            reverse_id_.push_back(it->second.label);
            ++it;
        }

    }

    num_nodes_ = reverse_id_.size();
    idom_rels_ = this->ComputeImmediateDominators();
}

void CFG::ParseAssembly(const std::string &filename) {
    std::vector<std::string> vec = ParseUtil::GetLines(filename);
    int id = 0;
    BasicBlock curr_block("HEADER", id++);
    for (unsigned idx = 0; idx < vec.size(); ++idx) {
        std::string curr_line = ParseUtil::Clean(vec[idx]);
        if (ParseUtil::IsLabel(curr_line)) {
            key_[curr_block.label] = curr_block;
            if (curr_block.label == "main") entry_node_ = curr_block;
            curr_block = BasicBlock(ParseUtil::GetLabelString(curr_line), id++);
            continue;
        } 

        if (!curr_line.empty())
            curr_block.instructions.push_back(curr_line);
    }

    key_[curr_block.label] = curr_block;
}

void CFG::AddEdge(BasicBlock a, BasicBlock b) {
    adj_[a].push_back(b);
    pred_[b].push_back(a);
}

void CFG::AddVertex(BasicBlock a) {
    adj_[a] = std::list<BasicBlock>(); 
}

std::list<BasicBlock> CFG::GetAdjacent(BasicBlock b) const {
    if (adj_.find(b) == adj_.end()) return std::list<BasicBlock>();
    return adj_.at(b);
}

std::list<BasicBlock> CFG::GetAdjacent(std::string b) const {
    if (key_.find(b) == key_.end()) return std::list<BasicBlock>();
    return GetAdjacent(key_.at(b));
}

std::list<BasicBlock> CFG::GetPredecessors(BasicBlock b) const {
    if (pred_.find(b) == pred_.end()) return std::list<BasicBlock>();
    return pred_.at(b);
}

std::list<BasicBlock> CFG::GetPredecessors(std::string b) const {
    if (key_.find(b) == key_.end()) return std::list<BasicBlock>();
    return GetPredecessors(key_.at(b));
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

void CFG::PrintPred() {
    for (const auto &pair : pred_) {
        std::cout << pair.first.label << ": ";
        for (const auto &block : pair.second)
            std::cout << block.label << ", ";
        std::cout << '\n';
    }
}

void CFG::PrintKey() {
    for (const auto &pair : key_) {
        std::cout << pair.first << '\n';
        // std::cout << pair.second << "\n\n";
    }
}

void CFG::PrintIDs() {
    for (const auto &pair : key_) {
        std::cout << pair.first << ": " << pair.second.id << '\n';
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

std::map<BasicBlock,BasicBlock> CFG::ComputeImmediateDominators() {
    // maps ids to set of possible semidom ids
    std::vector<std::set<int>> bucket_(num_nodes_);
    // maps id to id of semidom
    std::vector<int> semi_(num_nodes_, -1);
    // maps id to id of immediate ancestor in dfs tree
    std::vector<int> ancestor_(num_nodes_, -1);
    // maps id to ids of nodes with same semidom
    std::vector<int> samedom_(num_nodes_, -1);
    // maps id to current best minimum semidom
    std::vector<int> best_(num_nodes_, -1);
    // maps ids to dfs num
    std::vector<int> dfnum_(num_nodes_, 0);
    // maps dfs num to vertex
    std::vector<int> vertex_(num_nodes_, -1);
    // maps id to parent id
    std::vector<int> parent_(num_nodes_, -1);
    // maps id to id of immediate dominator
    std::vector<int> idom_(num_nodes_, -1);

    // DFS Tree Label Generation
    int N = 0;
    std::deque<std::pair<int,int>> stack;
    stack.push_back({-1, id_["main"]});
    while (!stack.empty()) {
        std::pair<int,int> pair = stack.back();
        int p = pair.first;
        int n = pair.second;
        stack.pop_back();
        if (dfnum_[n] != 0) continue;
        dfnum_[n] = N;
        vertex_[N] = n;
        parent_[n] = p;
        ++N;

        std::stack<std::pair<int,int>> tmp;
        for (const auto &block : adj_[key_[reverse_id_[n]]]) {
            tmp.push({n, id_[block.label]});
        }
        while (!tmp.empty()) {
            stack.push_back(tmp.top());
            tmp.pop();
        }
    }

    // Lambda expression to return dfs tree 
    // ancestor with lowest semidominator value
    std::function<int(int)> AncestorWithLowestSemi = [&](int v) -> int {
        int a = ancestor_.at(v);
        if (ancestor_.at(a) >= 0) {
            int b = AncestorWithLowestSemi(a);
            ancestor_.at(b) = ancestor_.at(a);
            if (dfnum_.at(semi_.at(b)) < dfnum_.at(semi_.at(best_.at(v)))) {
                best_.at(v) = b;
            }
        }
        return best_.at(v);
    };

    // Lambda expression to link parent node to child
    std::function<void(int,int)> Link = [&](int p, int n) -> void {
        ancestor_.at(n) = p;
        best_.at(n) = n;
    };

    auto invalid_node_err = std::runtime_error("Invalid node.");

    for (int i = N-1; i >= 0; --i) {
        int n = vertex_.at(i);
        int p = parent_.at(n);
        int s = p;

        // If node's key doesn't exist, throw error
        if (key_.find(reverse_id_.at(n)) == key_.end()) {
            cout << "key\n";
            throw invalid_node_err;
        }

        // If node doesn't have any CFG predecessors, i.e. entry node, skip
        if (pred_.find(key_.at(reverse_id_.at(n))) == pred_.end()) {
            continue;
        }

        for (BasicBlock block : pred_.at(key_.at(reverse_id_.at(n)))) {
            int v = id_.at(block.label);

            int sPrime = dfnum_.at(v) <= dfnum_.at(n)
                ? v
                : semi_.at(AncestorWithLowestSemi(v));

            if (dfnum_.at(sPrime) < dfnum_.at(s)) {
                s = sPrime;
            }
        }

        semi_.at(n) = s;
        bucket_.at(s).insert(n);
        Link(p,n);

        for (int v : bucket_.at(p)) {
            int y = AncestorWithLowestSemi(v);
            // if semi(y) == semi(v), idom(v) = semi(n)
            if (semi_.at(y) == semi_.at(v)) {
                idom_.at(v) = p;
            } else {
                samedom_.at(v) = y;
            }
        }
        bucket_.at(p).clear();
    }

    // if semi(y) != semi(n), idom(n) = idom(y)
    for (int i = 0; i < N; ++i) {
        int n = vertex_.at(i);
        if (samedom_.at(n) >= 0) {
            idom_.at(n) = idom_.at(samedom_.at(n));
        }
    }

    // converts idom_ id map to basicblock map, return result
    std::map<BasicBlock,BasicBlock> idom_relationships;
    for (int i = 0; i < idom_.size(); ++i) {
        idom_relationships[key_[reverse_id_[i]]] = key_[reverse_id_[idom_[i]]];
    }

    return idom_relationships;
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
    BasicBlock dummy = BasicBlock("dummy", -1); 

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

int CFG::Dijkstras(std::string start, std::string end) {
    return Dijkstras(key_[start], key_[end]);
}
 
BasicBlock CFG::GetImmediateDominator(BasicBlock b) {
    if (idom_rels_.find(b) == idom_rels_.end()) return BasicBlock();
    return idom_rels_.at(b);
}

BasicBlock CFG::GetImmediateDominator(std::string b) {
    return GetImmediateDominator(key_[b]);
}

