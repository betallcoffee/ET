//
//  Command.h
//  ET
//
//  Created by liang on 11/7/15.
//  Copyright (c) 2015 liangliang. All rights reserved.
//

#ifndef _ET_COMMAND_
#define _ET_COMMAND_

namespace ET {
    namespace HTTP{
        
        class Command {
        public:
            Command() {};
            ~Command() {};
            
            virtual void execute() = 0;
        };
        
    } // end HTTP
} // end ET


#endif // end _ET_COMMAND_
