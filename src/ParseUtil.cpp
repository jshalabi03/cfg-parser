#include "ParseUtil.h"

namespace ParseUtil {

std::string TrimRight(const std::string & str) {
    std::string tmp = str;
    while (!tmp.empty() && is_white_space[tmp.back()]) {
        tmp.pop_back();
    }
    return tmp;
    // return tmp.erase(tmp.find_last_not_of(" ") + 1);
}

std::string TrimLeft(const std::string & str) {
    std::string tmp = str;
    while (!tmp.empty() && is_white_space[tmp.front()]) {
        tmp.erase(0,1);
    }
    return tmp;
    // return tmp.erase(0, tmp.find_first_not_of(" "));
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
    std::string tmp = Trim(str);
    return tmp.length() > 2 && tmp[0] == '/' && tmp[1] == '/';
}

std::string GetLabelString(const std::string &str) {
    return str.substr(0, str.length() - 1);
}

std::vector<std::string> GetLines(const std::string &filename) {
    std::string line;
    std::vector<std::string> res;

    std::ifstream ifs(filename);
    if (!ifs.is_open()) throw std::runtime_error("Bad IO");

    while (std::getline(ifs, line)) {
        res.push_back(Trim(line));
    }

    ifs.close();

    return res;
}

std::pair<std::string,std::string> GetInstruction(const std::string &str) {
    std::string cpy(Trim(str));
    size_t pos_a = cpy.find_last_of('\t');
    size_t pos_b = cpy.find_last_of(' ');
    size_t pos;
    if (pos_a == std::string::npos) pos = pos_b;
    else if (pos_b == std::string::npos) pos = pos_a;
    else pos = std::max(pos_a,pos_b);

    if (pos == std::string::npos) {
        return {cpy, ""};
    }
    else return {cpy.substr(0,pos), Trim(cpy.substr(pos))};
}


// cbz, tbz, b, b.*, bl
bool IsJumpInstruction(const std::string &str) {
    if (str.length() >= 2 
    && str[1] == 'b' && (str[0] == 'c' || str[0] == 't')) return true;
    if (str == "bl") return true;
    return ((str.length() == 1 && str[0] == 'b')
     || (str.length() > 1 && str[0] == 'b' && str[1] == '.'));
}
};