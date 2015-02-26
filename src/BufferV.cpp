// Use of this source code is governed by a BSD-style license
//  that can be found in the License file.
//
//  Author: betallcoffee
//

#include <algorithm>
#include <string>
#include "BufferV.h"

using namespace ET;

const char BufferV::kCRLF[] = { "\r\n" };

BufferV::BufferV()
    : readIndex_(0),
    writeIndex_(0)
{
}

BufferV::~BufferV()
{
}

size_t BufferV::append(const char *data, size_t n)
{
    ensureWriteable(n);
    std::copy(data, data + n, beginWrite());
    writeIndex_ += n;
    return n;
}

const char *BufferV::findCRLF()
{
    return findCRLF(beginRead());
}

const char *BufferV::findCRLF(char *start)
{
    const char *res = std::search(start, beginWrite(), kCRLF + 0, kCRLF + 2);
    return res == beginWrite() ? NULL : res;
}

std::string BufferV::getLine() {
	const char *begin = beginRead();
	const char *end = findCRLF();
	if (end == NULL) return std::string();
	std::string line(begin, end + 2);
	retrieve(line.size() + 2);
	return line;
}

void BufferV::ensureWriteable(size_t n)
{
    if (n > writeableBytes()) {
        expend(n);
    }
}

void BufferV::expend(size_t size)
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

