//
//  ThreadPool.cpp
//  ET
//
//  Created by liang on 8/19/15.
//  Copyright (c) 2015 liangliang. All rights reserved.
//

#include "ThreadPool.h"

using namespace std;

using namespace ET;
using namespace THREAD;

ThreadPool::ThreadPool(int maxNum) {
    _maxNum = maxNum;
}

ThreadPool::~ThreadPool() {
    for_each(_threads.begin(), _threads.end(), [](pthread_t fd) {
        
    });
}

bool ThreadPool::initialize() {
    pthread_t thread;
    int ret = pthread_create(&thread, NULL, threadRoutine, this);
    if (!ret) {
        return false;
    }
    return true;
}

void *ThreadPool::threadRoutine(void *arg) {
    ThreadPool *self = (ThreadPool *)arg;
    while (true) {
        
    }
    return NULL;
}


