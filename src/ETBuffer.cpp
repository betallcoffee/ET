// Use of the source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: betallcoffee
//

#include <stdlib.h>

#include "ETBuffer.h"

using namespace ET;

ETBuffer::ETBuffer(int capacity)
    : size_(0),
    capacity_(capacity)
{
    first_ = (ETBufferChunk *)malloc(sizeof(ETBufferChunk));
    if (first_ != NULL) {
        first_->next = NULL;
        first_->start_ = (char *)malloc(capacity_);
        if (first_->start_ == NULL) {
            free(first_);
            first_ = NULL;
        } else {
            first_->end_ = first_->start_ + capacity_;
            first_->pos_ = first_->start_;
            first_->last_ = first_->start_;
        }
    }
    pos_ = last_ = first_;
}

~ETBuffer::ETBuffer()
{
    ETBufferChunk *temp;
    while (first_ != NULL) {
        temp = first_;
        first_ = first_->next;
        free(temp->start_);
        free(temp);
    }
}

// Only read data , don't move the readable position.
int ETBuffer::read(char *to, int size)
{
    int pos = 0;
    ETBufferChunck *tmp = first_;
    while (tmp != NULL) {
        if (size - pos <= tmp->last_ - tmp->pos_) {
            memcpy(to + pos, tmp->pos_, size - pos);
            pos = size;
            break;
        } else {
            memcpy(to + pos, tmp->pos, tmp->last_ - tmp->pos_);
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
    while (size > 0 && first_ != NULL) {
        if (size - pos <= first_->last_ - first_->pos_) {
            first_->pos_ += size - pos;
            if (first_->pos_ == first_->last_) {
                first_->last_ = first_->pos_ = first_->start_;
                last_->next = first_;
                first_ = first_->next_;
                last_ = last_->next_;
                last_->next_ = NULL;
            }
            pos = size;
            break;
        } else {
            pos += first_->last_ - first_->pos_;
            first_->last_ = first_->pos_ = first_->start_;
            last_->next_ = first_;
            first_ = first_->next_;
            last_ = last_->next_;
            last_->next_ = NULL;
        }

    size_ -= pos;
}

int ETBuffer::write(char *from, int size)
{
    int pos = 0;

    if (pos_ == NULL) {
        if (expend(size) == -1) {
            return -1;
        }
    } else {
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
                        return pos;
                    }
                } // if (pos_ == NULL)
            } // if (size - pos < pos_->end_ - pos_->last_)
        } // while (size != pos)
    } // if (pos_ == NULL)
    size_ += size;
    return size;
}

int ETBuffer::clear();
{
}

int ETBuffer::expend(int size)
{
    if (pos_ == NULL) {
        pos_ = (ETBufferChunk *)malloc(sizeof(ETBufferChunk));
        if (pos_ == NULL) {
            return -1;
        } else {
            pos_->next = NULL;
            pos_->start_ = (char *)malloc(size);
            if (pos_->start == NULL) {
                free(pos_);
                pos_ = NULL;
                return -1;
            } else {
                pos_->end_ = pos_->start_ + size;
                pos_->pos_ = pos_->last_ = pos_->start_;
                first_ = first_ == NULL ? pos_ : first_;
                last_ = pos_;
            }
        } 
    } // if (pos_ == NULL)
    capacity_ += size;
    return size;
}

