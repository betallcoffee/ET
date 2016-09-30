//
//  ResponseRunnable.h
//  ET
//
//  Created by liang on 10/7/15.
//  Copyright (c) 2015 liangliang. All rights reserved.
//

#ifndef _ET_RESPONSE_RUNNABLE_
#define _ET_RESPONSE_RUNNABLE_

#include "Log.h"

#include "ThreadRunnable.h"

namespace ET {
    namespace HTTP {
        
        class Server;
        class Session;
        class Request;
        
        /**
         * Read data from file to response. use block I/O. derived from ThreadRunnable.
         */
        class ResponseRunnable : public THREAD::ThreadRunnable {
        public:
            ResponseRunnable(Server* server,
                             std::shared_ptr<Session> session,
                             std::shared_ptr<Request> request) : _server(server), _session(session), _request(request) {
                LogD("response runnable init");
            }
            ~ResponseRunnable() {
                LogD("response runnable destroy");
            }
          
            /**
             * Override the run virtual method of ThreadRunnable.
             */
            virtual void run();
            
        private:
            Server* _server;
            std::shared_ptr<Session> _session;
            std::shared_ptr<Request> _request;
        };
    }
}

#endif // end _ET_RESPONSE_RUNNABLE_
