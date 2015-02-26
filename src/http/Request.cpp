/*
 * Request.cpp
 *
 *  Created on: Feb 26, 2015
 *      Author: liang
 */

#include <vector>
#include "BufferV.h"
#include "StringUtility.h"
#include "Request.h"

using namespace ET;
using namespace HTTP;

Request::eStatus Request::parse(BufferV &data) {
	switch (_status) {
	case FIRST_LINE:
		parseFirstLine(data);
		break;
	case PARSE_HEADER:
		parseHeaders(data);
		break;
	case READ_BODY:
		readBody(data);
		break;
	case COMPLETE:
		break;
	}
	return status();
}

void Request::parseFirstLine(BufferV &data) {
	std::string line = data.getLine();
	if (line.size() > 0) {
		std::vector<std::string> strs = STRING::splite(line);
		_method = strs[0];
		_m = stringToMethod(_method);
		_path = strs[1];
		_version = stringToVersion(strs[2]);
		_status = PARSE_HEADER;
	}
}

Request::eMethod Request::stringToMethod(std::string const &method) {
	if (method == "GET") {
		return GET;
	} else if (method == "HEAD") {
		return HEAD;
	} else if (method == "POST") {
		return POST;
	} else if (method == "PUT") {
		return PUT;
	}
	return METHOD_NONE;
}
