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

const std::string BaseHeader::kConnection = "connection";
const std::string BaseHeader::kDate = "date";
const std::string BaseHeader::kMineVersion = "mime-version";
const std::string BaseHeader::kUpdate = "update";
const std::string BaseHeader::kTrailer = "trailer";
const std::string BaseHeader::kTransforEncoding = "transfor-encoding";
const std::string BaseHeader::kVia = "via";

const std::string BaseHeader::kCacheControl = "cache-control";
const std::string BaseHeader::kPragma = "pragma";

const std::string BaseHeader::kContentBase = "content-base";
const std::string BaseHeader::kContentEncoding = "content-encoding";
const std::string BaseHeader::kContentLanguage = "content-language";
const std::string BaseHeader::kContentLenght = "content-length";
const std::string BaseHeader::kContentLocation = "content-location";
const std::string BaseHeader::kContentMD5 = "content-md5";
const std::string BaseHeader::kContentRange = "content-range";
const std::string BaseHeader::kContentType = "content-type";

BaseHeader::sVersion BaseHeader::stringToVersion(std::string const &str) {
	sVersion version;
	std::vector<std::string> strs = STRING::splite(str, "/");
	strs = STRING::splite(strs[1], ".");
	version.major = strs[0][0] - '0';
	version.minor = strs[1][0] - '0';
	return version;
}

bool BaseHeader::parseAHeaderKeyValue(const std::string &k, const std::string &value) {
    bool ret = false;
    std::string key(k);
    std::transform(key.begin(), key.end(), key.begin(), std::tolower);
    if (key == kConnection) {
        _connection = value;
    } else if (key == kDate) {
        _date = value;
    } else if (key == kMineVersion) {
        _mineVersion = value;
    } else if (key == kTrailer) {
        _trailer = value;
    } else if (key == kTransforEncoding) {
        _transforEncoding = value;
    } else if (key == kUpdate) {
        _update = value;
    } else if (key == kVia) {
        _via = value;
    } else if (key == kCacheControl) {
        _cacheControl = value;
    } else if (key == kPragma) {
        _pragma = value;
    }
    
    return ret;
}




