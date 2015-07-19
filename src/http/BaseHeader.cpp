/*
 * BaseHeader.cpp
 *
 *  Created on: Feb 26, 2015
 *      Author: liang
 */

#include <string>
#include <vector>
#include "StringUtility.h"
#include "BaseHeader.h"

using namespace ET;
using namespace HTTP;

BaseHeader::sVersion BaseHeader::stringToVersion(std::string const &str) {
	sVersion version;
	std::vector<std::string> strs = STRING::splite(str, "/");
	strs = STRING::splite(strs[1], ".");
	version.major = strs[0][0] - '0';
	version.minor = strs[1][0] - '0';
	return version;
}

bool BaseHeader::parseAHeaderKeyValue(const std::string &key, const std::string &value) {
    bool ret = false;
    
    if (key == "Connection") {
        _connection = value;
    } else if (key == "Date") {
        _date = value;
    } else if (key == "MIME-Version") {
        _mineVersion = value;
    } else if (key == "Trailer") {
        _trailer = value;
    } else if (key == "Transfer-Encoding") {
        _transforEncoding = value;
    } else if (key == "Update") {
        _update = value;
    } else if (key == "Via") {
        _via = value;
    } else if (key == "Cache-Control") {
        _cacheControl = value;
    } else if (key == "Pragma") {
        _pragma = value;
    }
    
    return ret;
}




