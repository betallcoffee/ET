//
//  BaseHeader.h
//  ET
//
//  Created by liang on 11/9/14.
//  Copyright (c) 2014 liangliang. All rights reserved.
//

#ifndef ET_HTTP_BASE_HEADER_H
#define ET_HTTP_BASE_HEADER_H

#include <string>

namespace ET {
    
    namespace HTTP {
        
        /**
         * 通用首部
         */
        class BaseHeader {
        public:
            
            typedef struct Version {
                int major;
                int minor;
            }sVersion;
            
            bool parseAHeaderKeyValue(const std::string &key, const std::string &value);
            
        protected:
            sVersion stringToVersion(const std::string &str);
            sVersion _version;

            std::string _connection; // 允许客户端和服务器指定与请求/响应连接有关的选项。
            std::string _date; // 提供日期和时间标志，说明报文是什么时间创建的。
            std::string _mineVersion; // 给出发送端使用的 MIME 的版本。
            std::string _update; // 给出发送端可能想要“升级”使用的新版本或协议。
            std::string _trailer; // 如果报文采用了分块传输编码(chunked transfer encoding)方式，就可以用这个首部列出位于报文拖挂部分的首部集合。
            std::string _transforEncoding; // 告知接收端为了保证报文的可靠传输，对报文采用了什么编码方式。
            std::string _via; // 显示了报文经过的中间节点（代理，网关）。
            
            std::string _cacheControl; // 用于随报文传送缓存指示。
            std::string _pragma; // 另一种随报文传送指示的方式，但并不专用于缓存。
        };
    }
    
}

#endif // end ET_BASE_HEADER_H
