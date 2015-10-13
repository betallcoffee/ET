//
//  Response.cpp
//  ET
//
//  Created by liang on 10/1/15.
//  Copyright (c) 2015 liangliang. All rights reserved.
//

#include "Connection.h"
#include "BufferV.h"
#include "StringUtility.h"

#include "Response.h"
#include "Session.h"
#include "Request.h"

using namespace ET;
using namespace HTTP;
using namespace STRING;

const std::string Response::kCRLF = "\r\n";
const std::string Response::kSep = ":";

Response::Response(Request *request) :
  _request(request) {

};

Response::~Response() {
}


std::string Response::header(const std::string &k) {
    std::string key(k);
    std::transform(key.begin(), key.end(), key.begin(), std::tolower);
    return _headers[key];
}

void Response::addHeader(const std::string &k, const std::string &value) {
    std::string key(k);
    std::transform(key.begin(), key.end(), key.begin(), std::tolower);
    _headers[key] = value;
}

BufferV &Response::createHeaders() {
    _buf.clear();
    std::string firstLine = intToStr(_statusCode);
    firstLine.append(" ");
    firstLine.append(_phrase);
    _buf.append(firstLine.c_str(), firstLine.size());
    std::for_each(_headers.begin(), _headers.end(), [=](std::pair<std::string, std::string> pair){
        std::string line(kCRLF);
        line.append(pair.first);
        line.append(kSep);
        line.append(pair.second);
        _buf.append(line.c_str(), line.size());
    });
    _buf.append(kCRLF.c_str(), kCRLF.size());
    _buf.append(kCRLF.c_str(), kCRLF.size());
    return _buf;
}
