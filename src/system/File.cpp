//
//  File.cpp
//  ET
//
//  Created by liang on 7/23/15.
//  Copyright (c) 2015 liangliang. All rights reserved.
//

#include <unistd.h>
#include <sys/stat.h>

#include "File.h"
#include "BufferV.h"

using namespace ET;
using namespace SYSTEM;

File::File(const std::string &path, int flags, mode_t mode) {
    _path = path;
    _fd = open(_path.c_str(), flags, mode);
    if (_fd > 0) {
        struct stat st;
        int ret = fstat(_fd, &st);
        if (ret == 0) {
            _size = st.st_size;
            _atime = st.st_atimespec.tv_sec;
            _mtime = st.st_mtimespec.tv_sec;
            _ctime = st.st_ctimespec.tv_sec;
        }
    }
}

File::~File() {
    if (_fd > 0) {
        close(_fd);
    }
}

bool File::exist(const std::string &path) {
    struct stat st;
    int ret = stat(path.c_str(), &st);
    if (ret) {
        return false;
    } else {
        return true;
    }
}

size_t File::read(BufferV &buf) {
    if (_size > 0) {
        size_t size = 1024*1024;
        size = size > _size ? _size : size;
        buf.ensureWriteable(size);
        size = ::read(_fd, buf.beginWrite(), size);
        return size;
    }
    return 0;
}

size_t File::write(BufferV &buf) {
    size_t size = 0;
    while (!buf.empty()) {
        size_t s = ::write(_fd, buf.beginRead(), buf.readableBytes());
        if (s > 0) {
            buf.retrieve(s);
            size += s;
        }
    }
    return 0;
}
