// Use of this source code is governed by a BSD-style license
//  that can be found in the License file.
//
//  Author: betallcoffee
//

#include <algorithm>
#include "ETBufferV.h"

using namespace ET;

const char ETBufferV::kCRLF[] = { "\r\n" };

ETBufferV::ETBufferV()
    : readIndex_(0),
    writeIndex_(0)
{
}

ETBufferV::~ETBufferV()
{
}

size_t ETBufferV::append(const char *data, size_t n)
{
    ensureWriteable(n);
    std::copy(data, data + n, beginWrite());
    writeIndex_ += n;
    return n;
}

const char *ETBufferV::findCRLF()
{
    return findCRLF(beginRead());
}

const char *ETBufferV::findCRLF(char *start)
{
    const char *res = std::search(start, beginWrite(), kCRLF + 0, kCRLF + 2);
    return res == beginWrite() ? NULL : res;
}

void ETBufferV::ensureWriteable(size_t n)
{
    if (n > writeableBytes()) {
        expend(n);
    }
}

void ETBufferV::expend(size_t size)
{
    if (size > writeableBytes() + prependableBytes()) {
        buffer_.resize(writeIndex_ + size);
    } else {
        size_t readable = readableBytes();
        std::copy(beginRead(), beginWrite(), begin());
        readIndex_ = 0;
        writeIndex_ = readIndex_+ readable;
    }
}

