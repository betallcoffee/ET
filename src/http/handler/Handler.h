//
//  Handler.h
//  ET
//
//  Created by liang on 11/7/15.
//  Copyright (c) 2015 liangliang. All rights reserved.
//

#ifndef _ET_HANDLER_
#define _ET_HANDLER_

#include <string>

namespace ET {
    namespace HTTP{
        
        class Request;
        
        class Handler {
        public:
            Handler() {}
            virtual ~Handler() {}
            
            virtual const std::string &name() = 0;
            virtual const int type() = 0;
            virtual std::shared_ptr<Handler> createHandler(std::shared_ptr<Request> request) = 0;
            virtual void execute() = 0;
            
        protected:
            std::weak_ptr<Request> _request;
        };
        
    } // end HTTP
} // end ET


#endif // end _ET_HANDLER_
