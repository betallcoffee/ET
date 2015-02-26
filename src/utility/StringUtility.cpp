/*
 * String.cpp
 *
 *  Created on: Feb 26, 2015
 *      Author: liang
 */

#include "StringUtility.h"

using namespace ET::STRING;

std::vector<std::string> splite(std::string const &str, std::string const &sep) {
	std::vector<std::string> res;
	std::string::size_type begin = 0;
	do {
		std::string::size_type end = str.find(sep);
		std::string substr = str.substr(begin, end);
		res.push_back(substr);
		begin = end;
	} while(begin != std::string::npos);
	return res;
}

