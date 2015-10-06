//
//  FileReader.cpp
//  ET
//
//  Created by liang on 10/1/15.
//  Copyright (c) 2015 liangliang. All rights reserved.
//

#include "FileReader.h"
#include "BufferV.h"

using namespace ET;
using namespace THREAD;
using namespace SYSTEM;

FileReader::~FileReader() {
    if (_file) {
        delete _file;
    }
}

void FileReader::run() {
    _file->read(_buf);
    if (_fileReaderCallback) {
        _fileReaderCallback(_ctx);
    }
}

void FileReader::read(ET::BufferV &buf) {
    buf.appendBuffer(_buf);
    _buf.clear();
}


