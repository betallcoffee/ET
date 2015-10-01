//
//  FileReader.h
//  ET
//
//  Created by liang on 10/1/15.
//  Copyright (c) 2015 liangliang. All rights reserved.
//

#ifndef _ET_FILE_READER_
#define _ET_FILE_READER_


namespace ET {
    
    class File;
    
    /**
     * A reader read data from file. use block I/O, so run in a thread pool, not in main thread.
     */
    class FileReader {
    public:
        FileReader(File &file);
        ~FileReader();
        
    private:
        File &_file;
    };
}


#endif // end _ET_FILE_READER_
