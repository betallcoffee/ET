/*
 * Request.cpp
 *
 *  Created on: Feb 26, 2015
 *      Author: liang
 */

#include <vector>

#include "Log.h"
#include "BufferV.h"
#include "StringUtility.h"

#include "Request.h"

using namespace ET;
using namespace HTTP;

Request::eStatus Request::parse(BufferV &data) {
    /**
     * the loop can not run long time, because it run in main thread.
     */
    bool loop = false;
    do {
        switch (_status) {
            case FIRST_LINE:
                loop = parseFirstLine(data);
                break;
            case PARSE_HEADER:
                loop = parseHeaders(data);
                break;
            case READ_BODY:
                loop = readBody(data);
                break;
            case PARSE_COMPLETE:
                loop = false;
                break;
            default:
                loop = false;
                break;
        }
    } while(loop);
    
    return status();
}

void Request::setStatus(const eStatus status)
{
    _status = status;
}

std::vector<std::string> Request::headers(const std::string &key) {
    std::string k(key);
    std::transform(k.begin(), k.end(), k.begin(), std::tolower);
    return STRING::splite(_headers[k], ",");
}

std::string Request::header(const std::string &key) {
    std::string k(key);
    std::transform(k.begin(), k.end(), k.begin(), std::tolower);
    return _headers[k];
}

void Request::addHeader(const std::string &key, const std::string &value) {
    std::string k(key);
    std::string v(value);
    std::transform(k.begin(), k.end(), k.begin(), std::tolower);
    std::transform(v.begin(), v.end(), v.begin(), std::tolower);
    _headers[k] = v;
}

RequestHeader::eMethod Request::stringToMethod(const std::string &method) {
    if (method == "GET") {
        return RequestHeader::GET;
    } else if (method == "HEAD") {
        return RequestHeader::HEAD;
    } else if (method == "POST") {
        return RequestHeader::POST;
    } else if (method == "PUT") {
        return RequestHeader::PUT;
    }
    return RequestHeader::METHOD_NONE;
}

bool Request::parseFirstLine(BufferV &data) {
    std::string line;
    bool ret = data.getLine(line);
	if (ret && line.size() > 0) {
        LogV("a request first line:%s", line.c_str());
		std::vector<std::string> strs = STRING::splite(line.substr(0, line.size() - 2));
        if (strs.size() > 0) {
            _requestHeader._method = strs[0];
            _requestHeader._m = stringToMethod(_requestHeader._method);
        }
        if (strs.size() > 1) {
            _requestHeader._path = strs[1];
        }
        if (strs.size() > 2) {
            _requestHeader._version = _requestHeader.stringToVersion(strs[2]);
        } else {
            _requestHeader._version.minor = 0;
            _requestHeader._version.major = 1;
        }
		
        setStatus(PARSE_HEADER);
	}
    return ret;
}

bool Request::parseHeaders(BufferV &data) {
    std::string line;
    bool ret = data.getLine(line);
	if (ret && line.size() > 2 && _status == PARSE_HEADER) {
        STRING::trim(line);
        std::vector<std::string> strs = STRING::splite(line, ":", false);
        if (strs.size() >= 2) {
            LogV("request head:%s=%s", strs[0].c_str(), strs[1].c_str());
            addHeader(strs[0], strs[1]);
            _requestHeader.parseAHeaderKeyValue(strs[0], strs[1]);
        }
	} else if (ret && line.size() == 2) {
        
        proccessHeaders();
        
        if (_requestHeader._m == RequestHeader::POST ||
            _requestHeader._m == RequestHeader::PUT) {
            setStatus(READ_BODY);
        } else {
            setStatus(PARSE_COMPLETE);
        }
    }
    return ret;
}

void Request::proccessHeaders() {
    std::shared_ptr<Session> session = _session.lock();
    std::string upgrade = header(RequestHeader::kUpgrade);
    LogV("upgrade : %s", upgrade.c_str());
    if (session && upgrade == "websocket") {
        session->setUpgrade(Session::WEBSOCKET);
    }
}

bool Request::readBody(ET::BufferV &data) {
    if (_body == nullptr) {
        _body = new BufferV;
    }
    size_t n = _body->appendBuffer(data);
    data.retrieve(n);
    
    if (data.empty()) {
        return false;
    } else {
        return true;
    }
}

