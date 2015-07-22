// Use of this source code is governed by a BSD-style license
//  that can be found in the License file.
//
//  Author: betallcoffee
//

#ifndef ETBUFFERV_H
#define ETBUFFERV_H

#include <vector>

namespace ET
{

    //
    // A buffer that is based on std::vector.
    //
    class BufferV
    {
    public:
        BufferV();
        ~BufferV();
        
        char *beginRead() { return begin() + readIndex_; }
        char *beginWrite() { return begin() + writeIndex_; }
        size_t readableBytes() { return writeIndex_ - readIndex_; }
        size_t writeableBytes() { return buffer_.size() - writeIndex_; }
        size_t prependableBytes() { return readIndex_; }
        bool empty() { return readIndex_ == writeIndex_; }

        size_t append(const char *data, size_t n);
        size_t appendBuffer(BufferV &buffer);
        const char *findCRLF();
        const char *findCRLF(char *start);

        void retrieve(size_t n) { readIndex_ += n; }
        void clear() { readIndex_ = writeIndex_ = 0; }

        bool getLine(std::string &line);

    private:
        static const char kCRLF[];

        char *begin() { return &*buffer_.begin(); }
        //const char *begin() { return &*buffer_.begin(); }
        void ensureWriteable(size_t n);
        void expend(size_t size);
        
        std::vector<char> buffer_;
        size_t readIndex_;
        size_t writeIndex_;

    }; // end class BufferV

} // end namespace ET

#endif // end ETBUFFERV_H
