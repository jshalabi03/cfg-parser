#pragma once

#include <string>
#include <vector>
#include <stdexcept>
#include <fstream>
#include <iostream>
#include <unordered_map>

namespace ParseUtil {

static std::unordered_map<char, int> is_white_space = {{' ', 1},
                                                       {'\n', 1},
                                                       {'\t', 1},};

std::string TrimRight(const std::string & str);
std::string TrimLeft(const std::string & str);
std::string Trim(const std::string & str);

// returns cleaned version of line
std::string Clean(const std::string &str);

// returns true if line is a label
bool IsLabel(const std::string &str);

bool IsNonLabelInstruction(const std::string &str);

bool IsComment(const std::string &str);

// gets "main" from "main:"
std::string GetLabelString(const std::string &str);

std::vector<std::string> GetLines(std::string filename);

// gets {"b", ".LBB0_3"} from "b    .LBB0_3"
std::pair<std::string,std::string> GetInstruction(const std::string &str);

bool IsJumpInstruction(const std::string &str);

};