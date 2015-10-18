//
//  FileRunnable.cpp
//  ET
//
//  Created by liang on 10/7/15.
//  Copyright (c) 2015 liangliang. All rights reserved.
//

#include <string>

#include "Connection.h"

#include "File.h"
#include "BufferV.h"
#include "StringUtility.h"

#include "FileRunnable.h"
#include "Request.h"
#include "Response.h"

using namespace ET;
using namespace HTTP;
using namespace SYSTEM;
using namespace STRING;

void FileRunnable::run() {
    Response &response = _request->response();
    std::string path = "/Users/liang/Workspace/projects/ET";
    path.append(_request->path());
    if (File::exist(path)) {
        File *file = new File(path, "r");
        
        response.setStatusCode(Response::OK);
        response.setPhrase("OK");
        
        // 设置 body 的大小
        long end = file->size();
        response.addHeader(ResponseHeader::kContentLenght, intToStr(end));
        
        // 设置短连接 connection: close
        response.addHeader(ResponseHeader::kConnection, "close");
        
        _request->connection().send(response.createHeaders());
        
        BufferV buf;
        do {
            file->read(buf);
            printf("Response::fileReader(): buffer:(%s)\n", buf.beginRead());
            size_t size = _request->connection().send(buf);
            if (size > 0) {
                buf.retrieve(size);
            }
        } while (!buf.empty());
        
    }
}
