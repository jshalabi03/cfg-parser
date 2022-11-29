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

std::vector<std::string> GetLines(std::string filename) {
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
    size_t pos = cpy.find(' ');
    if (pos == std::string::npos) {
        std::cout << "HERE" << std::endl;
        return {cpy, ""};
    }
    else return {cpy.substr(0,pos), Trim(cpy.substr(pos))};
}

// @param str - trimmed instruction string, no params
// @returns true if instrution is a jump instruction, false otherwise
bool IsJumpInstruction(const std::string &str) {
    return ((str.length() == 1 && str[0] == 'b')
     || (str.length() > 1 && str[0] == 'b' && str[1] == '.'));
}

// std::pair<std::string,std::vector<std::string>> GetInstructionDetails(const std::string &str) {
//     string instruction;
//     vector<string> params;

//     size_t pos = str.find(' ');
//     if (pos == string::npos) return {str, {}};

//     instruction = str.substr(0,pos++);
//     string curr_instruction;
//     while (pos < str.length() && pos != string::npos) {
//         if (str[pos] == ',') {
//             params.push_back(curr_instruction);
//             curr_instruction.clear();
//             pos += 2;
//         } else {
//             curr_instruction += str[pos];
//             ++pos;
//         }
//     }
//     params.push_back(curr_instruction);
//     return {instruction, params};
// }

};