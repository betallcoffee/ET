//
//  Response.cpp
//  ET
//
//  Created by liang on 10/1/15.
//  Copyright (c) 2015 liangliang. All rights reserved.
//

#include "Connection.h"
#include "BufferV.h"
#include "FileReader.h"

#include "Response.h"
#include "Session.h"
#include "Request.h"

using namespace ET;
using namespace HTTP;

Response::Response(Request *request) :
  _request(request), _fileReader(nullptr) {
    std::string path = "/Users/liang/Workspace/projects/ET";
    path.append(_request->path());
    if (File::exist(path)) {
        File *file = new File(path, "r");
        _fileReader = new FileReader(file);
        _fileReader->setContext(this);
        _fileReader->setFileReaderCallback(fileReaderCallback);
        Session::sThreadPool->addTask(_fileReader);
    }
};

Response::~Response() {
    if (_fileReader) {
        delete _fileReader;
    }
}

void Response::fileReaderCallback(void *ctx) {
    Response *self = static_cast<Response *>(ctx);
    self->fileReader();
}

void Response::fileReader() {
    BufferV &buf = _fileReader->getReadBuffer();
    printf("Response::fileReader(): buffer:(%s)\n", buf.beginRead());
    size_t size = _request->connection().send(buf);
    buf.retrieve(size);
}


