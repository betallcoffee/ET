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

	//
	// A buffer class
	//
	class ETBuffer
	{
	public:
		ETBuffer(int capacity);
		~ETBuffer();

        // Only read data, don't move the readable position.
		int read(char *to, int size);
        // Move the readable position.
        void retrieve(int size);

		int write(const char *from, int size);
        int write(ETBuffer *from);

        // append the data node of b, and move some empty node to b.
        int swap(ETBuffer *b);

        int findCRLF();
		int clear();
        int readableBytes() { return size_; }

	private:
		typedef struct ETBufferChunk {
			struct ETBufferChunk *next_;

			char *start_;
			char *end_;
			char *pos_; // read cursor
			char *last_; // write cursor
		}ETBufferChunk;

        static const int kExpendSize = 64;
        static const char kCRLF[];
        // remove first bufer chunk, and retrun.
        ETBufferChunk *pop();
        void push(ETBufferChunk *);
		int expend(int size);

		ETBufferChunk *first_; // first readable chunk.
		ETBufferChunk *last_;
		ETBufferChunk *pos_; // first writeable chunk.
        int capacity_;
		int size_;
	}; // end class ETBuffer	
} // end namespace ET

#endif // ETBUFFER_H
