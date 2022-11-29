#pragma once

#include <string>
#include <vector>
#include <stdexcept>
#include <fstream>
#include <iostream>

using namespace std;

std::string TrimRight(const std::string & str);
std::string TrimLeft(const std::string & str);
std::string Trim(const std::string & str);

// returns cleaned version of
std::string Clean(const std::string &str);

bool IsLabel(const std::string &str);

bool IsNonLabelInstruction(const std::string &str);

bool IsComment(const std::string &str);

// gets "main" from "main:"
std::string GetLabelString(const std::string &str);

vector<string> GetLines(string filename);