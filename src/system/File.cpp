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

File::File(const std::string &path, const std::string &mode) {
    _path = path;
    struct stat st;
    int ret = stat(path.c_str(), &st);
    if (ret == 0) {
        _size = st.st_size;
        _atime = st.st_atimespec.tv_sec;
        _mtime = st.st_mtimespec.tv_sec;
        _ctime = st.st_ctimespec.tv_sec;
        _file = fopen(path.c_str(), mode.c_str());
    }
}

File::~File() {
    if (_file) {
        fclose(_file);
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
        size_t size = 1024;
        size = size > _size ? _size : size;
        buf.ensureWriteable(size);
        size = fread(buf.beginWrite(), size, 1, _file);
        return size;
    }
    return 0;
}

size_t File::write(BufferV &buf) {
    size_t size = 0;
    while (!buf.empty()) {
        size_t s = fwrite(buf.beginRead(), buf.readableBytes(), 1, _file);
        if (s > 0) {
            buf.retrieve(s);
            size += s;
        }
    }
    return 0;
}
