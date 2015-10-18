//
//  FileRunnable.h
//  ET
//
//  Created by liang on 10/7/15.
//  Copyright (c) 2015 liangliang. All rights reserved.
//

#ifndef _ET_FILE_RUNNABLE_
#define _ET_FILE_RUNNABLE_

#include "ThreadRunnable.h"

namespace ET {
    namespace HTTP {
        
        class Request;
        
        /**
         * Read data from file to response. use block I/O. derived from ThreadRunnable.
         */
        class FileRunnable : public THREAD::ThreadRunnable {
        public:
            FileRunnable(std::shared_ptr<Request> &request) : _request(request) {};
            ~FileRunnable() {};
          
            /**
             * Override the run virtual method of ThreadRunnable.
             */
            virtual void run();
            
        private:
            std::weak_ptr<Request> _request;
        };
    }
}

#endif // end _ET_FILE_RUNNABLE_
