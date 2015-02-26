/*
 * BaseMessage.cpp
 *
 *  Created on: Feb 26, 2015
 *      Author: liang
 */

#include <string>
#include <vector>
#include "StringUtility.h"
#include "BaseMessage.h"

using namespace ET;
using namespace HTTP;

BaseMessage::sVersion BaseMessage::stringToVersion(std::string const &str) {
	sVersion version;
	std::vector<std::string> strs = STRING::splite(str, "/");
	strs = STRING::splite(strs[1], ".");
	version.major = strs[0][0] - '0';
	version.minor = strs[1][0] - '0';
	return version;
}




