// Use of the source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: betallcoffee
//

#include <string.h>
#include "Alloc.h"

using namespace ET;

Alloc *Alloc::instance_ = NULL;
pthread_once_t Alloc::once_ = PTHREAD_ONCE_INIT;

Alloc::Alloc() : chunkList_(NULL), start_(NULL), end_(NULL)
{
    memset(freeList_, 0, sizeof(freeList_));
}

Alloc::~Alloc()
{
    while(chunkList_){
        char *p = (char *)chunkList_;
        chunkList_ = chunkList_->next;
        free(p);
    }
}

Alloc *Alloc::sharedInstance()
{
    pthread_once(&once_, &Alloc::init);
    return instance_;
}

void Alloc::init()
{
    instance_ = new Alloc();
}

void *Alloc::allocate(size_t n)
{
    size_t idx = index(n);
    if (idx >= kNFreeList) {
        char *p = (char *)malloc(n);
        size_t *np = (size_t*)p;
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

void Alloc::deallocate(void *p)
{
    Obj *q = (Obj *)((char*)p - sizeof(Obj));
    size_t idx = index(q->n);
    
    if (idx >= kNFreeList) {
        free(q);
    } else {
        q->next = freeList_[idx].next;
        freeList_[idx].next = q;
    }
}

void *Alloc::refill(size_t n)
{
    size_t nObjs = kNum;
    char *chunk = (char *)chunkAlloc(n, nObjs);

    if (nObjs == 0) {
        return NULL;
    } else if (nObjs == 1) {
        return chunk;
    } else {
        Obj *q = (Obj *)chunk;
        q->n = n;
        Obj *p = (Obj *)(chunk + n + sizeof(Obj));
        size_t idx = index(n);
        Obj *cur = &freeList_[idx];

        for (int i = 1; i < nObjs; ++i) {
            p->next = cur->next;
            cur->next = p;
            p = (Obj *)((char *)p + (n + sizeof(Obj)));
        }
        return q;
    }
}

void *Alloc::chunkAlloc(size_t n, size_t &num)
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
            size_t idx = index(leftSize);
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

