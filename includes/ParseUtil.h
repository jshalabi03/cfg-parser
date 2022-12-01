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

std::string TrimRight(const std::string &str);
std::string TrimLeft(const std::string &str);
std::string Trim(const std::string &str);

// returns cleaned version of line
std::string Clean(const std::string &str);

// returns true if line is a label
bool IsLabel(const std::string &str);

// returns true if line is non label instruction
bool IsNonLabelInstruction(const std::string &str);

// returns true if line is comment
bool IsComment(const std::string &str);

// gets "main" from "main:"
std::string GetLabelString(const std::string &str);

// returns vector of lines contained in filename's corresponding file
std::vector<std::string> GetLines(const std::string &filename);

// gets {"b", ".LBB1_20"} from "tbz	w8, #0, .LBB1_20"
std::pair<std::string,std::string> GetInstruction(const std::string &str);

// @param str - trimmed instruction string, no params
// @returns true if instrution is a jump instruction, false otherwise
bool IsJumpInstruction(const std::string &str);

};