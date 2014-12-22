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
    
    typedef void (*Handle)(Reqeust *req, Response *res);
    
    class Router {
    public:
        Router();
        ~Router();
        
        void registerHandle(const std::string *path, Handle handle);
        void disptach(const std::string *path, Request *req, Response *res);
        
    private:
        std::map<std::string, Handle> _handles;
        
    };
        
} // end HTTP
    
} // end ET

#endif
