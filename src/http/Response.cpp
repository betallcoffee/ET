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

using namespace ET;
using namespace HTTP;

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


