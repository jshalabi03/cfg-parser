#include "catch_amalgamated.hpp"

#include <cassert>
#include <iostream>

#include "ParseUtil.h"
#include "CFG.h"

using std::cout, std::endl;

TEST_CASE("Test GetLines") {
    std::vector<std::string> vec = ParseUtil::GetLines("/workspaces/225FinalProject/data/test.s");
    REQUIRE(vec.size() == 47);
    REQUIRE(vec[9] == ".cfi_def_cfa_offset 16");
}

TEST_CASE("Test Trim") {
    std::string str = "\t\n   \t\t\t\n EXAMPLE TEXT\n\n  \t";
    REQUIRE(ParseUtil::Trim(str) == "EXAMPLE TEXT");
}

TEST_CASE("Test CFG Construction") {
    CFG cfg("/workspaces/225FinalProject/data/test.s");

    std::string label_0 = "main",
                label_1 = ".LBB0_1",
                label_2 = ".LBB0_2",
                label_3 = ".LBB0_3";

    REQUIRE(cfg.GetAdjacent(label_0).size() == 2);
    REQUIRE(cfg.GetAdjacent(label_1).size() == 1);
    REQUIRE(cfg.GetAdjacent(label_2).size() == 1);
    REQUIRE(cfg.GetAdjacent(label_3).size() == 0);

    REQUIRE(cfg.AreConnected(label_0, label_1));
    REQUIRE(cfg.AreConnected(label_0, label_2));
    REQUIRE(cfg.AreConnected(label_1, label_3));
    REQUIRE(cfg.AreConnected(label_2, label_3));
}