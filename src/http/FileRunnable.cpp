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

#include "FileRunnable.h"
#include "Request.h"
#include "Response.h"

using namespace ET;
using namespace HTTP;
using namespace SYSTEM;

void FileRunnable::run() {
    std::string path = "/Users/liang/Workspace/projects/ET";
    path.append(_request->path());
    if (File::exist(path)) {
        File *file = new File(path, "r");
        BufferV buf;
        do {
            file->read(buf);
            printf("Response::fileReader(): buffer:(%s)\n", buf.beginRead());
            size_t size = _request->connection().send(buf);
            buf.retrieve(size);
        } while (!buf.empty());
        
    }
}
