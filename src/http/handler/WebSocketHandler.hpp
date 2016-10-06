//
//  WebSocketHandler.hpp
//  ET
//
//  Created by liang on 10/6/16.
//  Copyright © 2016 liangliang. All rights reserved.
//

#ifndef WebSocketHandler_hpp
#define WebSocketHandler_hpp

#include "Handler.h"
#include "Request.h"

namespace ET {
    namespace HTTP {
        
        class WebSocketHandler : public Handler {
        public:
            WebSocketHandler() {}
            WebSocketHandler(std::shared_ptr<Request> request);
            ~WebSocketHandler();
            
            const std::string &name() { return "WebSocketHandler"; }
            const int type() { return Session::WEBSOCKET; }
            std::shared_ptr<Handler> createHandler(std::shared_ptr<Request> request);
            void execute();
        };
        
    }  // end HTTP
} // end ET

#endif /* WebSocketHandler_hpp */
