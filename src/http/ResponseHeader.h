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
            
            static const std::string kAge; // （从最初创建开始）响应持续时间。
            static const std::string kPublic; // 服务器为其资源支持的请求方法列表。
            static const std::string kRetryAfter; // 如果资源不可用的话，在此日期或时间重试。
            static const std::string kServer; // 服务器应用程序软件的名称和版本。
            static const std::string kTitle; // 对 HTML 文档来说，就是 HTML 文档的源端给出的标题。
            static const std::string kWarning; // 比原因短语中更详细一些的警告报文。
            
            static const std::string kAcceptRanges; // 对此资源来说，服务器可接受的范围类型。
            
            static const std::string kSetCookies; // 不是真正的安全首部，但隐含有安全功能，可以在客户端设置一个令牌，以便服务器对客户端进行标识。
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
