//
// Created by Sakata on 2021/3/5.
//

#include "spiral_util.h"

namespace spiral {

/**
 * 处理字符串中的转义字符
 * @param temp 要处理的原字符串
 * @return std::string 处理后的字符串
 */
std::string ConvertStringToCString(const std::string &temp) {
    std::string ret;
    for (int i = 0; temp[i]; ++i) {
        switch (temp[i]) {
            case '\\': {
                ++i;
                switch (temp[i]) {
                    case 'n': {
                        ret += '\n';
                        break;
                    }
                    case 't': {
                        ret += '\t';
                        break;
                    }
                    case 'r': {
                        ret += '\r';
                        break;
                    }
                    case 'a': {
                        ret += '\a';
                        break;
                    }
                    case 'b': {
                        ret += '\b';
                        break;
                    }
                    case 'f': {
                        ret += '\f';
                        break;
                    }
                    case 'v': {
                        ret += '\v';
                        break;
                    }
                    case '\\': {
                        ret += '\\';
                        break;
                    }
                    case '\'': {
                        ret += '\'';
                        break;
                    }
                    case '\"': {
                        ret += '\"';
                        break;
                    }
                    default:
                        throw std::runtime_error("Unsupported escape character: " + temp);
                }
                break;
            }
            default:
                ret += temp[i];
        }
    }
    return ret;
}

} // namespace spiral