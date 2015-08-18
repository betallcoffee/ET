//
//  Dir.h
//  ET
//
//  Created by liang on 7/29/15.
//  Copyright (c) 2015 liangliang. All rights reserved.
//

#ifndef _ET_DIR_H_
#define _ET_DIR_H_

#include <string>

namespace ET {
    
    namespace SYSTEM {
        
        class Dir {
        public:
            Dir(const std::string &path);
            ~Dir();
            
        private:
            std::string _path;
        };
    }
    
}

#endif /* end _ET_DIR_H_ */
