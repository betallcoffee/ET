// Use of the source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: betallcoffee
//

#ifndef ETALLOC_H
#define ETALLOC_H

#include <stdlib.h>
#include <pthread.h>

namespace ET
{
    //
    // Memory pool. Slab alloc.
    // Singleton class, only use in ETBuffer.
    //
    class ETAlloc
    {
    public:
        ~ETAlloc();

        // Return a singleton ETAlloc instance.
        static ETAlloc *sharedInstance();

        void *allocate(size_t n);
        void deallocate(void *p);

    private:
        static const int kNum = 20;
        static const int kBase = 32;
        static const int kNFreeList = 16;
        static const int kChunkSize = 1024 * 1024;

        union uObj {
            union uObj *next;
            size_t n;
        };
        typedef union uObj Obj;

        ETAlloc(); 
        ETAlloc(const ETAlloc &);
        static void init();

        int index(size_t n) { return ((n + kBase -1) / kBase - 1); }
        int roundUpOf(size_t n, int base) { return ((n + base -1) & ~(base - 1)); }
        
        // Return a node which's size is n, and n is multiple of 8.
        // And increase the node number of free list.
        void *refill(size_t n);

        // Recursion allocate a chunk of room.
        // Maybe adjust the free list.
        void *chunkAlloc(size_t n, int &num);

        static ETAlloc *instance_;
        static pthread_once_t once_;

        Obj freeList_[kNFreeList];
        Obj *chunkList_;
        char *start_;
        char *end_;
    }; // end class ETAlloc.
} // end namespace ET

#endif // end ETALLOC_H
