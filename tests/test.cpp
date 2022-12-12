#include "catch_amalgamated.hpp"

#include <cassert>
#include <iostream>

#include "ParseUtil.h"
#include "CFG.h"

using std::cout, std::endl;

TEST_CASE("Test GetLines") {
    std::vector<std::string> vec = ParseUtil::GetLines("/workspaces/225FinalProject/data/test.s");
    REQUIRE(vec.size() == 162);
    REQUIRE(vec[9] == ".cfi_def_cfa_offset 16");
}

TEST_CASE("Test Trim") {
    std::string str = "\t\n   \t\t\t\n EXAMPLE TEXT\n\n  \t";
    REQUIRE(ParseUtil::Trim(str) == "EXAMPLE TEXT");
}

TEST_CASE("Test CFG Construction") {
    CFG cfg("/workspaces/225FinalProject/data/test.s");

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

TEST_CASE("Test DFS") {
    CFG cfg("/workspaces/225FinalProject/data/test.s");

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

TEST_CASE("Test Dijkstras") {

    CFG cfg("/workspaces/225FinalProject/data/test.s");

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