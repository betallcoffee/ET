//
//  Base64.hpp
//  ET
//
//  Created by liang on 10/7/16.
//  Copyright © 2016 liangliang. All rights reserved.
//

#ifndef Base64_hpp
#define Base64_hpp

#include <string>

namespace ET {
    
    class Base64 {
    public:
        Base64() {};
        ~Base64() {};
        
        void encode(const std::string &s);
        void decode(const std::string &s);
        
        const char *plain() { return _plain.c_str(); }
        const char *base64() { return _base64.c_str(); }
        
    private:
        std::string _plain;
        std::string _base64;;
    };
    
}



#endif /* Base64_hpp */
