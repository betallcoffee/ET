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

const std::string RequestHeader::kClientIP = "client-ip";
const std::string RequestHeader::kFrom = "from";
const std::string RequestHeader::kHost = "host";
const std::string RequestHeader::kReferer = "referer";
const std::string RequestHeader::kUserAgent = "user-agent";
const std::string RequestHeader::kOrigin = "origin";

const std::string RequestHeader::kAccept = "accept";
const std::string RequestHeader::kAcceptCharset = "accept-charset";
const std::string RequestHeader::kAcceptEncoding = "accept-encoding";
const std::string RequestHeader::kAcceptLanguage = "accept-language";

const std::string RequestHeader::kExpect = "expect";
const std::string RequestHeader::kIfMatch = "if-match";
const std::string RequestHeader::kIfModifiedSince = "if-modified-since";
const std::string RequestHeader::kIfNoneMatch = "if-none-match";
const std::string RequestHeader::kIfRange = "if-range";
const std::string RequestHeader::kIfUnmodifiedSince = "if-unmodified-since";
const std::string RequestHeader::kRange = "range";

const std::string RequestHeader::kAuthorization = "authorization";
const std::string RequestHeader::kCookies = "cookie";
const std::string RequestHeader::kCookies2 = "cookie2";

bool RequestHeader::parseAHeaderKeyValue(const std::string &k, const std::string &value) {
    bool ret = BaseHeader::parseAHeaderKeyValue(k, value);
    std::string key(k);
    std::transform(key.begin(), key.end(), key.begin(), std::tolower);
    if (!ret) {
        if (key == kClientIP) {
            _clientIP = value;
        } else if (key == kFrom) {
            _from = value;
        } else if (key == kHost) {
            _host = value;
        } else if (key == kReferer) {
            _referer = value;
        } else if (key == kUserAgent) {
            _userAgent = value;
        } else if (key == kOrigin) {
            _origin = value;
        } else if (key == kAccept) {
            _accept = value;
        } else if (key == kAcceptCharset) {
            _acceptCharset = value;
        } else if (key == kAcceptEncoding) {
            _acceptEncoding = value;
        } else if (key == kAcceptLanguage) {
            _acceptLanguage = value;
        } else if (key == kExpect) {
            _expect = value;
        } else if (key == kIfMatch) {
            _ifMatch = value;
        } else if (key == kIfModifiedSince) {
            _ifModifiedSince = value;
        } else if (key == kIfNoneMatch) {
            _ifNoneMatch = value;
        } else if (key == kIfRange) {
            _ifRange = value;
        } else if (key == kIfUnmodifiedSince) {
            _ifUnmodifiedSince = value;
        } else if (key == kRange) {
            _range = value;
        } else if (key == kAuthorization) {
            _authorization = value;
        } else if (key == kCookies) {
            _cookies = value;
        } else if (key == kCookies2) {
            _cookies2 = value;
        }
    }
    return ret;
}

