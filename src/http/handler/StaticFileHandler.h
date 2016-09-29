//
//  StaticFileHandler.h
//  ET
//
//  Created by liang on 11/6/15.
//  Copyright (c) 2015 liangliang. All rights reserved.
//

#ifndef _ET_STATIC_FILE_Handler_H_
#define _ET_STATIC_FILE_Handler_H_

#include "Handler.h"
#include "Request.h"

namespace ET {
    namespace HTTP {
        
        class StaticFileHandler : public Handler {
        public:
            StaticFileHandler(std::shared_ptr<Request> &request) : _request(request) {};
            ~StaticFileHandler();
            
            void execute();
            
        private:
            std::weak_ptr<Request> _request;
        };
        
    }  // end HTTP
} // end ET

#endif // end _ET_STATIC_FILE_HANDLER_H_
