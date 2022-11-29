#include "ParseUtil.h"

std::string TrimRight(const std::string & str) {
    std::string tmp = str;
    return tmp.erase(tmp.find_last_not_of(" ") + 1);
}

std::string TrimLeft(const std::string & str) {
    std::string tmp = str;
    return tmp.erase(0, tmp.find_first_not_of(" "));
}

std::string Trim(const std::string & str) {
    std::string tmp = str;
    return TrimLeft(TrimRight(str));
}

std::string Clean(const std::string &str) {
    std::string cpy(str);
    size_t pos = cpy.find("//");
    if (pos != std::string::npos)
        cpy.erase(pos);
    return Trim(cpy);
}

bool IsLabel(const std::string &str) {
    if (str.empty()) return false;
    return str[str.length() - 1] == ':';
}

bool IsNonLabelInstruction(const std::string &str) {
    return !str.empty() && str[0] == '\t';
}

bool IsComment(const std::string &str) {
    return str.length() > 2 && str[0] == '/' && str[1] == '/';
}

std::string GetLabelString(const std::string &str) {
    return str.substr(0, str.length() - 1);
}

vector<string> GetLines(string filename) {
    string line;
    vector<string> res;

    ifstream ifs(filename);
    if (!ifs.is_open()) throw std::runtime_error("Bad IO");

    while (getline(ifs, line)) {
        res.push_back(Trim(line));
    }

    ifs.close();

    return res;
}