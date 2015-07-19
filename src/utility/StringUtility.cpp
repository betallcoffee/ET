/*
 * String.cpp
 *
 *  Created on: Feb 26, 2015
 *      Author: liang
 */

#include <algorithm>
#include "StringUtility.h"

std::vector<std::string> ET::STRING::splite(const std::string &str, const std::string &sep, bool isLoop) {
	std::vector<std::string> res;
	std::string::size_type begin = 0;
    std::string::size_type end = std::string::npos;
    do {
        end = str.find(sep, begin);
        res.push_back(str.substr(begin, end - begin));
        begin = end + 1;
        if (!isLoop) {
            res.push_back(str.substr(begin, std::string::npos));
            break;
        }
    } while(end != std::string::npos);
    return res;
}

void ET::STRING::trim(std::string &str) {
    std::string res;
    str.erase(std::remove(str.begin(), str.end(), ' '), str.end());
}

