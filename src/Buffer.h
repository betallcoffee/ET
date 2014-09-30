// Use of this source code is governed by a BSD-style license
//  that can be found in the License file.
//
//  Author: betallcoffee
//
//  This is an interal header file, you should not include this file.
//

#ifndef ETBUFFER_H
#define ETBUFFER_H

namespace ET
{

    class Alloc;

    //
    // A buffer class
    //
    class Buffer
    {
    public:
        Buffer(int capacity);
        ~Buffer();

        // Only read data, don't move the readable position.
        int read(char *to, int size);
        // Move the readable position.
        void retrieve(int size);

        int write(const char *from, int size);
        int write(Buffer *from);

        // Read the data of buffer, and write to FD.
        int readToFD(int fd, int size);
        // Write the data which is read from FD to buffer.
        int writeFromFD(int fd);

        // Append the data node of b, and move some empty node to b.
        int swap(Buffer *b);

        int findCRLF();
        void clear();
        int readableBytes() { return size_; }

    private:
        typedef struct BufferChunk {
            struct BufferChunk *next_;

            char *start_;
            char *end_;
            char *pos_; // read cursor
            char *last_; // write cursor
        }BufferChunk;

        static const int kExpendSize = 64;
        static const char kCRLF[];
        // Pop first buffer chunk, and retrun.
        BufferChunk *pop();
        // Push a empty buffer chunk to buffer.
        void push(BufferChunk *);
        // Expend the room of buffer.
        int expend(int size);

        Alloc *alloc_;
        BufferChunk *first_; // first readable chunk.
        BufferChunk *last_;
        BufferChunk *pos_; // first writeable chunk.
        int capacity_;
        int size_;
    }; // end class Buffer
} // end namespace ET

#endif // ETBUFFER_H

