# Written Report

## Overview

For our Data Structures final project, we decided to explore LLVM assembly hierarchy and structure. We came in with the questions which blocks of code dominate which others and the shortest path between blocks of code in assembly instructions. We quickly realized we could answer these questions by implementing a graph class, setting the assembly labels as vertices, and their jump instructions as edges. 

With this graph implementation we determined the top three algorithms which would help us answer our leading questions. We decided to implement Depth-First Search, Dijstrka’s algorithm and Lengauer-Tarjan’s algorithm. We have included a brief summary of each algorithm below, with our results and correctness.

### Graph Implementation

For our graph implementation, we set the assembly labels as vertices, and their jump instructions as edges, connecting two vertices if they have instructions from one to another.

### Data Parsing

For our parser, we filter out the assembly labels by looking for label syntax. While creating our parsing pipeline, we encountered the issue that comments could contain these characters. To fix this, we implemented the parser to first filter out comments, and then we were able to construct the graph. We also matched the jump instructions between labels to create edges.

#### Example Adjacency List Output
```
.LBB5_1: .LBB5_2, 
.LBB5_2: .LBB5_4, .LBB5_3, 
.LBB5_3: _Z10not_calledi, .LBB5_4, 
.LBB5_4: 
_Z10not_calledi: 
_Z2f0i: _Z2f1i, _Z2f2i, 
_Z2f1i: _Z2f2i, 
_Z2f2i: 
main: _Z2f0i, _Z2f1i, .LBB5_2, .LBB5_1, 
```

### Depth-First Search
To create our DFS, we used an iterative approach, with a stack. with a disjoint set of the BasicBlock nodes to mark everything if it’s been visited or not. This then returns a vector of the graph with the DFS traversal. We know our implementation is correct because when doing a DFS algorithm manually on our assembly code, it produced the same results. The runtime was O(V+E), as we traversed all the edges and vertices.


### Dijkstra's
For the Dijkstra’s implementation, we decided to use a modified BFS traversal with a queue of BasicBlock Nodes and a set of BasicBlock Nodes to keep track of the visited nodes. While the typical Dijkstra’s algorithm is O(E+VlogV) because of its use of the priority queue data structure, our modified Dijkstra’s does not use a priority queue as all the edges are unweighted. This provides a better runtime of O(V + E) as popping from a queue can be done in constant time. Otherwise, we use a very standard Dijkstra’s approach, setting each distance to INT_MAX and setting the distance to zero for the start node. Then we do our BFS traversal setting the current block's distance to the previous block’s distance + 1. Once we find our end node, we know that it is the shortest possible path. If we are unable to find a connection/path between the start and end nodes, the function returns -1 to indicate so. To test that it was working properly we first created a simple control flow graph that we knew all the edges for by running a dijkstra’s by hand. We then wrote test cases for several of the nodes and checked the distance output to ensure correctness. We also wrote tests for edge cases, such as either a start or end node not existing, or a path not being found, both which should output -1 as an integer. 

### Lengauer-Tarjan
The first step to creating a Lengauer-Tarjan tree is to create a DFS tree. In order to do so, we run DFS on our Control Flow Graph mapping each node/Basic Block that is visited to a number from [1, n] based on the order they were visited. This creates a spanning tree with each Node/Basic Block having a label that will be later used to calculate the semi-dominators.

In a Lengauer-Tarjan dominator tree, the general idea of a semi-dominator is a node that dominates all other nodes in the subtree rooted at that node. The technical definition is given above which essentially says that the semi-dominator of w is a node that has a path in the CFG to w where every node on the path except the starting node and w has a greater value/DFS number than w and the semi-dominator is the minimum node with this property. There could be several semi-dominators for a single node in the graph but the semi-dominator of the node will be the one with the smallest DFS number. Using theorem 2 and 3, we can define the definition of the immediate dominator of w to be sdom(w) if sdom(w) = sdom(u), and idom(u) otherwise. This allows us to find the immediate dominators of each node which allows us to create our dominator tree. 

In a dominator tree, it is made up nodes where each node’s children are those nodes it immediately dominates. We use the previous theorems to calculate semi-dominators which then allows us to calculate the immediate dominator of each node. When we have all the immediate dominators in our graph, we can connect them based on the dominance which allows us to build our dominator tree. 

## Runtime analysis
Let m, n be the number of edges and nodes in the control flow graph, respectively
### DFS Runtime
O(m+n)
### Dijkstra's Runtime
O(m+n)
### Lengauer-Tarjan Runtime
O(m log n)

## Results
### DFS Results

```
root@60a6593c9a45:/workspaces/225FinalProject# make
clang++ -std=c++20 -I includes/ -I src/ -I tests/ -I catch2/ src/CFG.cpp src/ParseUtil.cpp src/main.cpp -o bin/main.out
bin/main.out

Pick one of the following options:
        0 - Quit
        1 - DFS Traversal
        2 - Compute Dijkstra's Shortest Path Distance
        3 - Compute Immediate Dominator
1
_______________________________

main -> .LBB5_1 -> .LBB5_2 -> .LBB5_3 -> _Z10not_calledi -> .LBB5_4 -> _Z2f1i -> _Z2f2i -> _Z2f0i -> NULL
_______________________________
```

### Dijkstra's Results

```
Pick one of the following options:
        0 - Quit
        1 - DFS Traversal
        2 - Compute Dijkstra's Shortest Path Distance
        3 - Compute Immediate Dominator
2
Enter two basic block labels to compute the shortest path distance between eachother: main _Z10not_calledi
_______________________________

The shortest path distance between block main and block _Z10not_calledi is 3
_______________________________
```
```
Pick one of the following options:
        0 - Quit
        1 - DFS Traversal
        2 - Compute Dijkstra's Shortest Path Distance
        3 - Compute Immediate Dominator
2
Enter two basic block labels to compute the shortest path distance between eachother: .LBB5_2 .Z2f0i
_______________________________

The shortest path distance between block .LBB5_2 and block .Z2f0i is -1
_______________________________
```

### Lengauer-Tarjan Results
```
Pick one of the following options:
        0 - Quit
        1 - DFS Traversal
        2 - Compute Dijkstra's Shortest Path Distance
        3 - Compute Immediate Dominator
3
Enter a basic block label to compute the immediate dominator of it: _Z10not_calledi
_______________________________

The immediate dominator of block _Z10not_calledi is .LBB5_3
_______________________________
```
```
Pick one of the following options:
        0 - Quit
        1 - DFS Traversal
        2 - Compute Dijkstra's Shortest Path Distance
        3 - Compute Immediate Dominator
3
Enter a basic block label to compute the immediate dominator of it: main
_______________________________

The immediate dominator of block main is NULL
_______________________________
```

## Testing
For the following tests, we construct an example control-flow graph, labelled cfg, by parsing an example static assembly file.
### Data Parsing
We test the data parsing by verifying the constructed control-flow graph's adjacency list is as expected.

```
TEST_CASE("Test CFG Construction") {
    std::string label_main = "main",
                label_1 = ".LBB5_1",
                label_2 = ".LBB5_2",
                label_3 = ".LBB5_3",
                label_4 = ".LBB5_4",
                label_f0 = "_Z2f0i",
                label_f1 = "_Z2f1i",
                label_f2 = "_Z2f2i",
                label_nc = "_Z10not_calledi";

    
    REQUIRE(cfg.GetAdjacent(label_main).size() == 4);
    REQUIRE(cfg.GetAdjacent(label_1).size() == 1);
    REQUIRE(cfg.GetAdjacent(label_2).size() == 2);
    REQUIRE(cfg.GetAdjacent(label_3).size() == 2);
    REQUIRE(cfg.GetAdjacent(label_4).size() == 0);
    REQUIRE(cfg.GetAdjacent(label_f0).size() == 2);
    REQUIRE(cfg.GetAdjacent(label_f1).size() == 1);
    REQUIRE(cfg.GetAdjacent(label_f2).size() == 0);
    REQUIRE(cfg.GetAdjacent(label_nc).size() == 0);

    REQUIRE(cfg.AreConnected(label_main, label_1));
    REQUIRE(cfg.AreConnected(label_main, label_2));
    REQUIRE(cfg.AreConnected(label_main, label_f0));
    REQUIRE(cfg.AreConnected(label_main, label_f1));

    REQUIRE(cfg.AreConnected(label_f0, label_f1));
    REQUIRE(cfg.AreConnected(label_f0, label_f2));

    REQUIRE(cfg.AreConnected(label_f1, label_f2));

    REQUIRE(cfg.AreConnected(label_2, label_3));
    REQUIRE(cfg.AreConnected(label_2, label_4));

    REQUIRE(cfg.AreConnected(label_1, label_2));

    REQUIRE(cfg.AreConnected(label_3, label_nc));
}
```
### DFS
We test the DFS traversal by comparing the output to the expected traversal of the example control-flow graph
```
TEST_CASE("Test DFS") {
    std::vector<BasicBlock> dfs = cfg.DFS();

    std::vector<std::string> expected_traversal = {
        "main",
        ".LBB5_1",
        ".LBB5_2",
        ".LBB5_3",
        "_Z10not_calledi",
        ".LBB5_4",
        "_Z2f1i",
        "_Z2f2i",
        "_Z2f0i"
    };

    int len = dfs.size();
    REQUIRE(len == expected_traversal.size());

    for (int idx = 0; idx < len; ++idx) {
        REQUIRE(dfs[idx].label == expected_traversal[idx]);
    }
    
}
```

### Dijkstra's
We test our Dijkstra's implementation by verifying the shortest distances between various pairs of nodes are as expected.
```
TEST_CASE("Test Dijkstras") {
    std::string label_main = "main",
                label_1 = ".LBB5_1",
                label_2 = ".LBB5_2",
                label_3 = ".LBB5_3",
                label_4 = ".LBB5_4",
                label_f0 = "_Z2f0i",
                label_f1 = "_Z2f1i",
                label_f2 = "_Z2f2i",
                label_nc = "_Z10not_calledi";

    REQUIRE(cfg.Dijkstras(label_main, label_nc) == 3);
    REQUIRE(cfg.Dijkstras(label_main, label_f2) == 2);
    REQUIRE(cfg.Dijkstras(label_1, label_nc) == 3);

    REQUIRE(cfg.Dijkstras(label_2, label_f1) == -1);
}
```

### Lengauer-Tarjan
We test our Lengauer-Tarjan implementation by verifying the immediate dominators of several of several nodes are as expected.
```
TEST_CASE("Test Lengauer-Tarjan") {
    std::string label_main = "main",
                label_1 = ".LBB5_1",
                label_2 = ".LBB5_2",
                label_3 = ".LBB5_3",
                label_4 = ".LBB5_4",
                label_f0 = "_Z2f0i",
                label_f1 = "_Z2f1i",
                label_f2 = "_Z2f2i",
                label_nc = "_Z10not_calledi";
    
    REQUIRE(cfg.GetImmediateDominator(label_main) == BasicBlock());

    REQUIRE(cfg.GetImmediateDominator(label_f0).label == label_main);
    REQUIRE(cfg.GetImmediateDominator(label_f1).label == label_main);
    REQUIRE(cfg.GetImmediateDominator(label_f2).label == label_main);
    REQUIRE(cfg.GetImmediateDominator(label_2).label == label_main);
    REQUIRE(cfg.GetImmediateDominator(label_1).label == label_main);

    REQUIRE(cfg.GetImmediateDominator(label_4).label == label_2);
    REQUIRE(cfg.GetImmediateDominator(label_3).label == label_2);

    REQUIRE(cfg.GetImmediateDominator(label_nc).label == label_3);
}
```
