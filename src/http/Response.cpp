//
//  Response.cpp
//  ET
//
//  Created by liang on 10/1/15.
//  Copyright (c) 2015 liangliang. All rights reserved.
//

#include "Connection.h"
#include "BufferV.h"

#include "Response.h"
#include "Session.h"
#include "Request.h"

using namespace ET;
using namespace HTTP;

Response::Response(Request *request) :
  _request(request) {

};

Response::~Response() {
}



