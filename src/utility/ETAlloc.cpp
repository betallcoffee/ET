// Use of the source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: betallcoffee
//

#include <string.h>
#include "ETAlloc.h"

using namespace ET;

ETAlloc *ETAlloc::instance_ = NULL;
pthread_once_t ETAlloc::once_ = PTHREAD_ONCE_INIT;

ETAlloc::ETAlloc() : chunkList_(NULL), start_(NULL), end_(NULL)
{
    memset(freeList_, 0, sizeof(freeList_));
}

ETAlloc::~ETAlloc()
{
    while(chunkList_){
        char *p = (char *)chunkList_;
        chunkList_ = chunkList_->next;
        free(p);
    }
}

ETAlloc *ETAlloc::sharedInstance()
{
    pthread_once(&once_, &ETAlloc::init);
    return instance_;
}

void ETAlloc::init()
{
    instance_ = new ETAlloc();
}

void *ETAlloc::allocate(size_t n)
{
    int idx = index(n);
    if (idx >= kNFreeList) {
        char *p = (char *)malloc(n);
        int *np = (int*)p;
        *np = n;
        return p + sizeof(Obj);
    } else {
        Obj *p = freeList_[idx].next;

        if (p == NULL) {
            p = (Obj *)refill(n);
            if (p == NULL) {
                return p;
            }
        } else {
            freeList_[idx].next = p->next;
        }

        p->n = n; 
        return (char *)p + sizeof(Obj);
    }
}

void ETAlloc::deallocate(void *p)
{
    Obj *q = (Obj *)((char*)p - sizeof(Obj));
    int idx = index(q->n);
    
    if (idx >= kNFreeList) {
        free(q);
    } else {
        q->next = freeList_[idx].next;
        freeList_[idx].next = q;
    }
}

void *ETAlloc::refill(size_t n)
{
    int noObjs = kNum;
    char *chunk = (char *)chunkAlloc(n, noObjs);

    if (noObjs == 0) {
        return NULL;
    } else if (noObjs == 1) {
        return chunk;
    } else {
        Obj *q = (Obj *)chunk;
        q->n = n;
        Obj *p = (Obj *)(chunk + n + sizeof(Obj));
        int idx = index(n);
        Obj *cur = &freeList_[idx];

        for (int i = 1; i < noObjs; ++i) {
            p->next = cur->next;
            cur->next = p;
            p = (Obj *)((char *)p + (n + sizeof(Obj)));
        }
        return q;
    }
}

void *ETAlloc::chunkAlloc(size_t n, int &num)
{
    char *p = NULL;
    size_t size = n + sizeof(Obj);
    size_t totalSize = size * num;
    size_t leftSize = end_ - start_;

    if (leftSize >= totalSize) {
        p = start_;
        start_ += totalSize;
        return p;
    } else if (leftSize >= size){
        num = leftSize / size;
        totalSize = size * num;
        p = start_;
        start_ += totalSize;
        return p;
    } else {
        if (leftSize > 0) {
            int idx = index(leftSize);
            Obj *q = (Obj *)start_;
            q->next = freeList_[idx].next;
            freeList_[idx].next = q;
        }

        start_ = (char *)malloc(kChunkSize);
        if (start_) {
            end_ = start_ + kChunkSize;
            return chunkAlloc(n, num);
        } else {
            return NULL;
        }
    }
}

