//
//  RequestHeader.cpp
//  ET
//
//  Created by liang on 7/19/15.
//  Copyright (c) 2015 liangliang. All rights reserved.
//

#include "RequestHeader.h"

using namespace ET;
using namespace HTTP;

bool RequestHeader::parseAHeaderKeyValue(const std::string &key, const std::string &value) {
    bool ret = BaseHeader::parseAHeaderKeyValue(key, value);
    if (!ret) {
        if (key == "Client-IP") {
            _clientIP = value;
        } else if (key == "From") {
            _from = value;
        } else if (key == "Host") {
            _host = value;
        } else if (key == "Referer") {
            _referer = value;
        } else if (key == "User-Agent") {
            _userAgent = value;
        } else if (key == "Accept") {
            _accept = value;
        } else if (key == "Accept-Charset") {
            _acceptCharset = value;
        } else if (key == "Accept-Encoding") {
            _acceptEncoding = value;
        } else if (key == "Accept-Language") {
            _acceptLanguage = value;
        } else if (key == "Expect") {
            _expect = value;
        } else if (key == "If-Match") {
            _ifMatch = value;
        } else if (key == "If-Modified-Since") {
            _ifModifiedSince = value;
        } else if (key == "If-None-Match") {
            _ifNoneMatch = value;
        } else if (key == "If-Range") {
            _ifRange = value;
        } else if (key == "If-Unmodified-Since") {
            _ifUnmodifiedSince = value;
        } else if (key == "Range") {
            _range = value;
        } else if (key == "Authorization") {
            _authorization = value;
        } else if (key == "Cookie") {
            _cookies = value;
        } else if (key == "Cookie2") {
            _cookies2 = value;
        }
    }
    return ret;
}

