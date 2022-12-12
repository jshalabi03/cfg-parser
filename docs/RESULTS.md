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