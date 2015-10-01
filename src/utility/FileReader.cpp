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
    pthread_mutex_lock(&_bufMutex);
    _file->read(_buf);
    pthread_mutex_unlock(&_bufMutex);
}

void FileReader::read(ET::BufferV &buf) {
    pthread_mutex_lock(&_bufMutex);
    buf.appendBuffer(_buf);
    _buf.clear();
    pthread_mutex_unlock(&_bufMutex);
}


