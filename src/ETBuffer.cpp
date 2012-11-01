// Use of the source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: betallcoffee
//

#include <stdlib.h>
#include <string.h>

#include "ETBuffer.h"
#include "ETAlloc.h"

using namespace ET;

const char kCRLF[] = { "\r\n" };

ETBuffer::ETBuffer(int capacity)
    : alloc_(NULL),
    first_(NULL),
    last_(NULL),
    pos_(NULL),
    capacity_(capacity),
    size_(0)
{
    alloc_ = ETAlloc::sharedInstance();
    first_ = (ETBufferChunk *)alloc_->allocate(sizeof(ETBufferChunk));
    if (first_ != NULL) {
        first_->next_ = NULL;
        first_->start_ = (char *)alloc_->allocate(capacity_);
        if (first_->start_ == NULL) {
            alloc_->deallocate(first_);
            first_ = NULL;
        } else {
            first_->end_ = first_->start_ + capacity_;
            first_->pos_ = first_->start_;
            first_->last_ = first_->start_;
        }
    }
    pos_ = last_ = first_;
}

ETBuffer::~ETBuffer()
{
    ETBufferChunk *temp;
    while (first_ != NULL) {
        temp = first_;
        first_ = first_->next_;
        alloc_->deallocate(temp->start_);
        alloc_->deallocate(temp);
    }
}

// Only read data , don't move the readable position.
int ETBuffer::read(char *to, int size)
{
    int pos = 0;
    ETBufferChunk *tmp = first_;
    while (tmp != NULL) {
        if (size - pos <= tmp->last_ - tmp->pos_) {
            memcpy(to + pos, tmp->pos_, size - pos);
            pos = size;
            break;
        } else {
            memcpy(to + pos, tmp->pos_, tmp->last_ - tmp->pos_);
            pos += tmp->last_ - tmp->pos_;
            tmp = tmp->next_;
        }
    }
    return pos; 
}

// Move the readable position
void ETBuffer::retrieve(int size)
{
    int pos = 0;
    if (first_ == NULL) return ;
    while (size > 0 && size_ > 0) {
        if (size - pos <= first_->last_ - first_->pos_) {
            first_->pos_ += size - pos;
            size_ -= size - pos;
            if (first_->pos_ == first_->last_) {
                first_->last_ = first_->pos_ = first_->start_;
                if (first_ != pos_) {
                    last_->next_ = first_;
                    first_ = first_->next_;
                    last_ = last_->next_;
                    last_->next_ = NULL;
                }
            }
            pos = size;
            break;
        } else {
            pos += first_->last_ - first_->pos_;
            size_ -= first_->last_ - first_->pos_;
            first_->last_ = first_->pos_ = first_->start_;
            if (first_ != pos_) {
                last_->next_ = first_;
                first_ = first_->next_;
                last_ = last_->next_;
                last_->next_ = NULL;
            }
        }
    }
}

int ETBuffer::write(const char *from, int size)
{
    int pos = 0;

    if (pos_ == NULL) {
        if (expend(size) == -1) {
            return -1;
        }
    }

    while (size != pos) {
        if (size - pos < pos_->end_ - pos_->last_) {
            memcpy(pos_->last_, from + pos, size - pos);
            pos_->last_ = pos_->last_ + size - pos;
            break;
        } else {
            memcpy(pos_->last_, from + pos, pos_->end_ - pos_->last_);
            pos += pos_->end_ - pos_->last_;
            pos_->last_ = pos_->end_;
            pos_ = pos_->next_;
            if (pos_ == NULL) {
                if (expend(size - pos) == -1) {
                    return -1;
                }
            } // if (pos_ == NULL)
        } // if (size - pos < pos_->end_ - pos_->last_)
    } // while (size != pos)

    size_ += size;
    return size;
}

int ETBuffer::write(ETBuffer *from)
{
    int res = 0;
    ETBufferChunk *tmp;
    while (tmp = from->pop()) {
        tmp->next_ = pos_->next_;
        pos_->next_ = tmp;
        if (pos_ == last_) {
            last_ = pos_->next_;
        }
        pos_ = pos_->next_;
        res += pos_->pos_ - pos_->start_;
        size_ += pos_->last_ - pos_->pos_;
        capacity_ += pos_->end_ - pos_->start_;
    }
    return res;
}

int ETBuffer::readToFD(int fd, int size)
{
    return 0;
}

int ETBuffer::writeFromFD(int fd)
{
    return 0;
}

int ETBuffer::swap(ETBuffer *b)
{
    int res = 0;
    ETBufferChunk *tmp;
    while (tmp = b->pop()) {
        // First append data nodes from b.
        if (first_ == NULL) {
            first_ = last_ = pos_ = tmp;
            tmp->next_ = NULL;
        } else {
            tmp->next_ = pos_->next_;
            pos_->next_ = tmp;
            if (pos_ == last_) {
                // The pos_ and last_ point to same node.
                // So move last_ to next.
                last_ = pos_->next_;
            }
            pos_ = pos_->next_;
        }
        res += pos_->pos_ - pos_->start_;
        size_ += pos_->last_ - pos_->pos_;
        capacity_ += pos_->end_ - pos_->start_;

        // Second move empty nodes to b.
        tmp = pos_->next_;
        if (tmp != NULL) {
            if (last_ == tmp) {
                // The next of pos_ is last_, so move last_ to pos_.
                last_ = pos_;
            }
            pos_->next_ = tmp->next_;
            tmp->next_ = NULL;
            tmp->last_ = tmp->pos_ = tmp->start_;
            capacity_ -= tmp->end_ - tmp->start_;
            b->push(tmp);
        }
    }
    return res;

}

int ETBuffer::findCRLF()
{
    int res = 0;
    ETBufferChunk *tmp = first_;
    while (tmp) {
        int offset = 0;
        while (tmp->pos_ + offset < tmp->last_) {
            if('\r' == *(tmp->pos_ + offset)) {
                if (tmp->pos_ + offset + 1 < tmp->last_ &&
                        '\n' == *(tmp->pos_ + offset + 1)) {
                    res += offset;
                    return res;
                } else if (tmp->next_ &&
                        tmp->next_->pos_ < tmp->next_->last_ &&
                        '\n' == *(tmp->next_->pos_) ) {
                    res += offset;
                    return res;
                } 
            }

            offset++;
        }
        res += offset;
        tmp = tmp->next_;
    }
    return -1;
}

int ETBuffer::clear()
{
    ETBufferChunk *tmp = first_;
    while(tmp != pos_->next_) {
        tmp->last_ = tmp->pos_ = tmp->start_;
        tmp = tmp->next_;
    }
    size_ = 0;
}

ETBuffer::ETBufferChunk *ETBuffer::pop()
{
    ETBufferChunk *res;
    if (first_ == NULL) {
        // The buffer is empty.
        res = NULL;
    } else if (first_ != pos_) {
        // The pos_ and last_ is behind first_.
        // Only move first_ to next node.
        res = first_;
        first_ = first_->next_;
        res->next_ = NULL;
    } else if (first_ == pos_ &&
            pos_->last_ > pos_->start_) {
        // The pos_ and first_ point to the same node, and it isn't empty.
        // So move first_ and pos_ to next node.
        res = first_;
        first_ = first_->next_;
        pos_ = pos_->next_;
        res->next_ = NULL;
    } else {
        // The pos_ and first_ point to the same node, but it is empty.
        res = NULL;
    }

    if (first_ == NULL) {
        // The only one node has pop, there is no node.
        last_ = pos_ = first_;
    }

    if (res) {
        // Ajust the size_ and capacity_.
        size_ -= res->last_ - res->pos_;
        capacity_ -= res->end_ - res->start_;
    }
    return res;
}

void ETBuffer::push(ETBufferChunk *b)
{
    b->pos_ = b->last_ = b->start_;
    b->next_ = NULL;
    if (first_ == NULL) {
        // The buffer is empty.
        first_ = last_ = pos_ = b;
    } else {
        last_->next_ = b;
        last_ = last_->next_;
    }
    capacity_ += b->end_ - b->start_;
}

int ETBuffer::expend(int size)
{
    size = size > kExpendSize ? size : kExpendSize;
    if (pos_ == NULL) {
        pos_ = (ETBufferChunk *)alloc_->allocate(sizeof(ETBufferChunk));
        if (pos_ == NULL) {
            pos_ = last_;
            return -1;
        } else {
            pos_->next_ = NULL;
            pos_->start_ = (char *)alloc_->allocate(size);
            if (pos_->start_ == NULL) {
                alloc_->deallocate(pos_);
                pos_ = last_;
                return -1;
            } else {
                pos_->end_ = pos_->start_ + size;
                pos_->pos_ = pos_->last_ = pos_->start_;
                if (first_ == NULL) {
                    first_ = last_ = pos_;
                } else {
                    last_->next_ = pos_;
                    last_ = last_->next_;
                }
            }
        } 
    } // if (pos_ == NULL)
    capacity_ += size;
    return size;
}

