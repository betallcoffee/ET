//
//  RequestHeader.h
//  ET
//
//  Created by liang on 7/19/15.
//  Copyright (c) 2015 liangliang. All rights reserved.
//

#ifndef ET_REQUEST_HEADER
#define ET_REQUEST_HEADER

#include "BaseHeader.h"

namespace ET {
    
    namespace HTTP {
        
        class RequestHeader : public BaseHeader {
        public:
            RequestHeader() : _m(METHOD_NONE) {}
            
            typedef enum Method {
                METHOD_NONE = 0,
                GET = 1, //从服务器获取一份文档， 无 body
                HEAD,  // 只从服务器获取文档的首部， 无 body
                POST, // 向服务器发送需要处理的数据， 有 body
                PUT, // 将请求的主体部分存储在服务器上， 有 body
                TRACE, // 对可能经过代理服务器传送到服务器上去的报文进行追踪， 无 body
                OPTIONS, // 决定可以在服务器上招待哪些方法
                DELETE // 从服务器上删除一份文档
            }eMethod;
            
            friend class Request;
            
            bool parseAHeaderKeyValue(const std::string &key, const std::string &value);
            
        private:
            eMethod _m;
            std::string _method; // 请求方法
            std::string _url; // 请求 url
            std::string _path;
            
            std::string _clientIP; // 提供了运行客户端的机器的 IP 地址。
            std::string _from; // 提供了客户端用户的 E-mail 地址。
            std::string _host; // 提供了接收请求的服务器的主机和端口号。
            std::string _referer; // 提供了包含当前请求 URI 的文档 的 URL。
            std::string _userAgent; // 将发起请求的应用程序名称告知服务器。
            
            // Accept 首部
            std::string _accept; // 告诉服务器能够发送哪些媒体类型。
            std::string _acceptCharset; // 告诉服务器能够发送哪些字符集。
            std::string _acceptEncoding; // 告诉服务器能够发送哪些编码方式。
            std::string _acceptLanguage; // 告诉服务器能够发送哪些语言。
            
            // 条件请求首部
            std::string _expect; // 允许客户端列出某请求所要求的服务器的行为。
            std::string _ifMatch; // 如果实体标记与文档当前的实体标记相匹配，就获取这份文档。
            std::string _ifModifiedSince; // 除非在某个指定的日期之后资源被修改过，否则就限制这个请求。
            std::string _ifNoneMatch; // 如果提供的实体标记与当文档的实体标记不相符，就获取文档。
            std::string _ifRange; // 允许对文档的某个范围进行条件请求。
            std::string _ifUnmodifiedSince; // 除非在某个指定日期之后资源没有被修改过，否则就限制这个请求。
            std::string _range; // 如果服务器支持范围请求，就请求资源指定范围。
            
            // 安全请求首部
            std::string _authorization; // 包含了客户端提供给服务器，以便对其自身进行认证的数据。
            std::string _cookies; // 客户端用它向服务器传送一个令牌，它并不是真正的安全首部，但确实隐含了安全功能。
            std::string _cookies2; // 用来说明请求端支持的 cookie 版本。

        };
        
    }
    
}

#endif /* end ET_REQUEST_HEADER */
