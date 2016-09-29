//
//  Handler.h
//  ET
//
//  Created by liang on 11/7/15.
//  Copyright (c) 2015 liangliang. All rights reserved.
//

#ifndef _ET_HANDLER_
#define _ET_HANDLER_

namespace ET {
    namespace HTTP{
        
        class Handler {
        public:
            Handler() {};
            ~Handler() {};
            
            virtual void execute() = 0;
        };
        
    } // end HTTP
} // end ET


#endif // end _ET_HANDLER_
