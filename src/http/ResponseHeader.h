//
//  ResponseHeader.h
//  ET
//
//  Created by liang on 10/11/15.
//  Copyright (c) 2015 liangliang. All rights reserved.
//

#ifndef ET_RESPONSE_HEADER
#define ET_RESPONSE_HEADER

#include "BaseHeader.h"

namespace ET {
    
    namespace HTTP {
        
        class ResponseHeader : public BaseHeader {
        public:
            ResponseHeader() {}
            
            friend class Request;
            friend class Response;
            
            bool parseAHeaderKeyValue(const std::string &key, const std::string &value);
            
            static const std::string kAge;
            static const std::string kPublic;
            static const std::string kRetryAfter;
            static const std::string kServer;
            static const std::string kTitle;
            static const std::string kWarning;
            
            static const std::string kAcceptRanges;
            
            static const std::string kSetCookies;
            static const std::string kSetCookies2;
            static const std::string kWWWAuthenticate;
            
        private:
            std::string _age;
            std::string _public;
            std::string _retryAfter;
            std::string _server;
            std::string _title;
            std::string _warning;
            
            std::string _accpetRanges;
            
            std::string _setCookies;
            std::string _setCookies2;
            std::string _WWWAuthenticate;
            
        };
        
    }
    
}

#endif /* end ET_RESPONSE_HEADER */
