#pragma once

#include "CFG.h"

// Dominator tree constructed from inherited CFG.
// Describes dominance relationships in CFG.
class DominatorTree : public CFG {
public:
    DominatorTree();
    DominatorTree(const std::string &filename);
private:
};