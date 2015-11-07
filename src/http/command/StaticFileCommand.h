//
//  StaticFileCommand.h
//  ET
//
//  Created by liang on 11/6/15.
//  Copyright (c) 2015 liangliang. All rights reserved.
//

#ifndef _ET_STATIC_FILE_COMMAND_H_
#define _ET_STATIC_FILE_COMMAND_H_

#include "Command.h"
#include "Request.h"

namespace ET {
    namespace HTTP {
        
        class StaticFileCommand : public Command {
        public:
            StaticFileCommand(std::shared_ptr<Request> &request) : _request(request) {};
            ~StaticFileCommand();
            
            void execute();
            
        private:
            std::weak_ptr<Request> _request;
        };
        
    }  // end HTTP
} // end ET

#endif // end _ET_STATIC_FILE_COMMAND_H_
