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
		int write(char *from, int size);
		int clear();

        int readableBytes() { return size_; }

	private:
		typedef struct ETBufferChunk {
			struct ETBufferChunk *next_;

			char *start_;
			char *end_;
			char *pos_;
			char *last_;
		}ETBufferChunk;

		int expend(int size);

		ETBufferChunk *first_;
		ETBufferChunk *last_;
		ETBufferChunk *pos_;
        int capacity_;
		int size_;
	}; // end class ETBuffer	
} // end namespace ET

#endif // ETBUFFER_H

