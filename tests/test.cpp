#include "catch_amalgamated.hpp"

#include <cassert>
#include <iostream>

#include "ParseUtil.h"
#include "CFG.h"

using std::cout, std::endl;

TEST_CASE("Test GetLines") {
    std::vector<std::string> vec = ParseUtil::GetLines("/workspaces/225FinalProject/data/a.s");
    REQUIRE(vec.size() == 16);
    REQUIRE(vec[9] == "mov	w0, #0");
}