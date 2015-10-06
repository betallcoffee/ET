//
//  ThreadPool.cpp
//  ET
//
//  Created by liang on 8/19/15.
//  Copyright (c) 2015 liangliang. All rights reserved.
//

#include "ThreadPool.h"
#include "ThreadRunnable.h"

using namespace std;

using namespace ET;
using namespace THREAD;

ThreadPool::ThreadPool(int maxNumOfThread) {
    _maxNumOfThread = maxNumOfThread;
    initialize();
}

ThreadPool::~ThreadPool() {
    for_each(_threads.begin(), _threads.end(), [](pthread_t fd) {
        
    });
}

bool ThreadPool::initialize() {
    _taskMutex = PTHREAD_MUTEX_INITIALIZER;
    _taskCond = PTHREAD_COND_INITIALIZER;
    pthread_t thread;
    int ret = pthread_create(&thread, NULL, threadRoutine, this);
    if (!ret) {
        return false;
    }
    return true;
}

void ThreadPool::addTask(ET::THREAD::ThreadRunnable *task) {
    if (task) {
        pthread_mutex_lock(&_taskMutex);
        _tasks.push_back(task);
        pthread_cond_broadcast(&_taskCond);
        pthread_mutex_unlock(&_taskMutex);
    }
}

void *ThreadPool::threadRoutine(void *arg) {
    ThreadPool *self = static_cast<ThreadPool *>(arg);
    self->threadRoutine();
    return NULL;
}

void ThreadPool::threadRoutine() {
    while (true) {
        pthread_mutex_lock(&_taskMutex);
        while (_tasks.empty()) {
            pthread_cond_wait(&_taskCond, &_taskMutex);
        }
        
        if (!_tasks.empty()) {
            ThreadRunnable *task = _tasks.back();
            _tasks.pop_back();
            task->run();
        }

        pthread_mutex_unlock(&_taskMutex);
    }
}


