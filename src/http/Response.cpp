//
//  Response.cpp
//  ET
//
//  Created by liang on 10/1/15.
//  Copyright (c) 2015 liangliang. All rights reserved.
//

#include "BufferV.h"
#include "FileReader.h"
#include "Response.h"
#include "Transport.h"
#include "Request.h"

using namespace ET;
using namespace HTTP;

Response::Response(Transport *transport, Request *request) :
_transport(transport), _request(request), _fileReader(nullptr) {
    std::string path = "/Users/liang/Workspace/projects/ET";
    path.append(_request->path());
    if (File::exist(path)) {
        File *file = new File(path, "r");
        _fileReader = new FileReader(file);
        _fileReader->setContext(this);
        _fileReader->setFileReaderCallback(fileReaderCallback);
        Transport::sThreadPool->addTask(_fileReader);
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
    size_t size = _transport->writeData(buf);
    buf.retrieve(size);
}


