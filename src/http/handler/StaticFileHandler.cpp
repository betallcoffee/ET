//
//  StaticFileCommand.cpp
//  ET
//
//  Created by liang on 11/6/15.
//  Copyright (c) 2015 liangliang. All rights reserved.
//

#include <string>

#include "Connection.h"

#include "File.h"
#include "BufferV.h"
#include "StringUtility.h"

#include "StaticFileHandler.h"

#include "Request.h"
#include "Response.h"
#include "ResponseRunnable.h"

using namespace ET;
using namespace HTTP;
using namespace SYSTEM;
using namespace STRING;

StaticFileHandler::StaticFileHandler(std::shared_ptr<Request> request) {
    _request = request;
}
StaticFileHandler::~StaticFileHandler() {}

std::shared_ptr<Handler> StaticFileHandler::createHandler(std::shared_ptr<Request> request) {
    return std::make_shared<StaticFileHandler>(request);
}

void StaticFileHandler::execute() {
    std::shared_ptr<Request> request = _request.lock();
    if (request) {
        Response &response = request->response();
        std::string path = "/Users/liang/Workspace/projects/ET/web/";
        path.append(request->path());
        if (File::exist(path)) {
            File *file = new File(path, "r");
            
            response.setStatusCode(Response::OK);
            response.setPhrase("OK");
            
            // 设置 body 的大小
            long end = file->size();
            response.addHeader(ResponseHeader::kContentLenght, intToStr(end));
            
            request->connection()->lock();
            request->connection()->send(response.createHeaders());
            
            BufferV buf;
            do {
                file->read(buf);
                //                printf("Response::fileReader(): buffer:(%s)\n", buf.beginRead());
                size_t size = request->connection()->send(buf);
                if (size > 0) {
                    buf.retrieve(size);
                } else {
                    break;
                }
            } while (!buf.empty());
            request->connection()->unlock();
        } else {
            response.setStatusCode(Response::NOTFOUND);
            response.setPhrase("Not Found");
            
            // 设置短连接 connection: close
            response.addHeader(ResponseHeader::kConnection, "close");
            
            request->connection()->lock();
            request->connection()->send(response.createHeaders());
            request->connection()->unlock();
        }
    }
}
