//
//  ThreadPool.h
//  ET
//
//  Created by liang on 8/19/15.
//  Copyright (c) 2015 liangliang. All rights reserved.
//

#ifndef _ET_THREAD_POOL_
#define _ET_THREAD_POOL_

#include <vector>
#include <pthread.h>

namespace ET {
    namespace THREAD {
        
        class ThreadRunnable;
        /**
         * thread pool
         */
        class ThreadPool {
        public:
            ThreadPool(int maxNumOfThread);
            ~ThreadPool();
            
            /**
             * Initialize thread pool, create one thread, and suspend the threads.
             *
             * @return bool initialize success return true, otherwise return false.
             */
            bool initialize();
            
            /**
             * Send a threadrunnable task to thread pool.
             * @param task ThreadRunnable class, Thread pool will schedule a idle thread to run it, or create a new thread to run it.
             * 
             */
            void addTask(ThreadRunnable *task);
            
        private:
            /**
             * The thread routine, the base is a loop. Take a task from task queue, complete task, and cycle repeats.
             */
            static void *threadRoutine(void *arg);
            void threadRoutine();
            /**
             * Extend the number of threads, but the limit the _maxNum. Add one thread per call.
             */
            void extendThread();
            
            int _maxNumOfThread;
            std::vector<pthread_t> _threads;
            pthread_mutex_t _taskMutex;
            pthread_cond_t _taskCond;
            std::vector<ThreadRunnable *> _tasks;
        };
        
    } // end namespace THREAD
} // end namespace ET

#endif // end _ET_THREAD_POOL_
