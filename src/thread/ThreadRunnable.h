//
//  ThreadRunnable.h
//  ET
//
//  Created by liang on 9/27/15.
//  Copyright (c) 2015 liangliang. All rights reserved.
//

#ifndef _ET_THREAD_RUNNABLE_
#define _ET_THREAD_RUNNABLE_

namespace ET {
    namespace THREAD {
        
        class ThreadRunnable {
        public:
            virtual ~ThreadRunnable();
            
            virtual void run();
            
        private:
            ThreadRunnable() {}; // 抽象类，不可实例
        };
        
    } // end namespace THREAD
} // end namespace ET

#endif // end _ET_THREAD_RUNNABLE_
