//
//  BaseMessage.h
//  ET
//
//  Created by liang on 11/9/14.
//  Copyright (c) 2014 liangliang. All rights reserved.
//

#ifndef ET_HTTP_BASE_MESSAGE_H
#define ET_HTTP_BASE_MESSAGE_H

#include <string>

namespace ET {
    
    namespace HTTP {
        
        class BaseMessage {
        public:
            
            typedef struct sVersion {
                int major;
                int minor;
            }sVersion;
            
        private:
            
            sVersion _version;
            
            std::string _connection;
            std::string _date;
            std::string _mine;
            std::string _update;
            std::string _trailer;
            std::string _transforEncoding;
            
            std::string _cacheControl;
            std::string _pragma;
            
        };
    }
    
}

#endif // end ET_BASE_MESSAGE_H
