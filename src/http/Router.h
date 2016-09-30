//
//  Router.h
//  ET
//
//  Created by liang on 12/22/14.
//  Copyright (c) 2014 liangliang. All rights reserved.
//

#ifndef ET_HTTP_ROUTER_H
#define ET_HTTP_ROUTER_H

#include <string>
#include <map>

namespace ET {

namespace HTTP{
    
    class Request;
    class Response;
    class Handler;
    
    class Router {
    public:
        Router();
        ~Router();
        
        void registerHandle(std::shared_ptr<const std::string> path, std::shared_ptr<Handler> handler);
        std::shared_ptr<Handler> disptach(std::shared_ptr<Request> request);
        
    private:
        std::map<std::shared_ptr<const std::string>, std::shared_ptr<Handler>> _handlers;
        
    };
        
} // end HTTP
    
} // end ET

#endif
