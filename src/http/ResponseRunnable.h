//
//  ResponseRunnable.h
//  ET
//
//  Created by liang on 10/7/15.
//  Copyright (c) 2015 liangliang. All rights reserved.
//

#ifndef _ET_RESPONSE_RUNNABLE_
#define _ET_RESPONSE_RUNNABLE_

#include "ThreadRunnable.h"

namespace ET {
    namespace HTTP {
        
        class Session;
        class Request;
        
        /**
         * Read data from file to response. use block I/O. derived from ThreadRunnable.
         */
        class ResponseRunnable : public THREAD::ThreadRunnable {
        public:
            ResponseRunnable(std::shared_ptr<Session> &session, std::shared_ptr<Request> &request) : _session(session), _request(request) {};
            ~ResponseRunnable() {};
          
            /**
             * Override the run virtual method of ThreadRunnable.
             */
            virtual void run();
            
        private:
            std::weak_ptr<Session> _session;
            std::shared_ptr<Request> _request;
        };
    }
}

#endif // end _ET_RESPONSE_RUNNABLE_
