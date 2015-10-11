//
//  ResponseHeader.cpp
//  ET
//
//  Created by liang on 10/11/15.
//  Copyright (c) 2015 liangliang. All rights reserved.
//

#include "ResponseHeader.h"

using namespace ET;
using namespace HTTP;

const std::string ResponseHeader::kAge = "age";
const std::string ResponseHeader::kPublic = "public";
const std::string ResponseHeader::kRetryAfter = "retry-after";
const std::string ResponseHeader::kServer = "server";
const std::string ResponseHeader::kTitle = "title";
const std::string ResponseHeader::kWarning = "warning";

const std::string ResponseHeader::kAcceptRanges = "accep-ranges";

const std::string ResponseHeader::kSetCookies = "set-cookie";
const std::string ResponseHeader::kSetCookies2 = "set-cookie2";
const std::string ResponseHeader::kWWWAuthenticate = "www-authenticate";

bool ResponseHeader::parseAHeaderKeyValue(const std::string &k, const std::string &value) {
    bool ret = BaseHeader::parseAHeaderKeyValue(k, value);
    std::string key(k);
    std::transform(key.begin(), key.end(), key.begin(), std::tolower);
    if (!ret) {
        if (key == kAge) {
            _age = value;
        } else if (key == kPublic) {
            _public = value;
        } else if (key == kRetryAfter) {
            _retryAfter = value;
        } else if (key == kServer) {
            _server = value;
        } else if (key == kTitle) {
            _title = value;
        } else if (key == kWarning) {
            _warning = value;
        } else if (key == kAcceptRanges) {
            _accpetRanges = value;
        } else if (key == kSetCookies) {
            _setCookies = value;
        } else if (key == kSetCookies2) {
            _setCookies2 = value;
        } else if (key == kWWWAuthenticate) {
            _WWWAuthenticate = value;
        }
    }
    return ret;
}
