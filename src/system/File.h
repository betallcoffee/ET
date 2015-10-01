//
//  File.h
//  ET
//
//  Created by liang on 7/23/15.
//  Copyright (c) 2015 liangliang. All rights reserved.
//

#ifndef ET__FILE_H
#define ET__FILE_H

#include <string>
#include <stdio.h>

namespace ET {
    
    class BufferV;
    
    namespace SYSTEM {
        
        class File {
        public:
            File(const std::string &path, const std::string &mode);
            ~File();
            
            static bool exist(const std::string &path);
            
            size_t read(BufferV &buf);
            size_t write(BufferV &buf);
            
            time_t modifyTime();
            time_t createTime();
            time_t accessTime();
            
        private:
            std::string _path;
            FILE *_file;
            size_t _size;
            time_t _atime;
            time_t _mtime;
            time_t _ctime;
        };
    } // end namespace SYSTEM
    
} // end namespace ET

#endif /* end ET_FILE_H */
