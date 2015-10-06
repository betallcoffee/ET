//
//  FileReader.h
//  ET
//
//  Created by liang on 10/1/15.
//  Copyright (c) 2015 liangliang. All rights reserved.
//

#ifndef _ET_FILE_READER_
#define _ET_FILE_READER_

#include "ThreadRunnable.h"
#include "File.h"
#include "BufferV.h"

namespace ET {
    
    using namespace SYSTEM;
    
    typedef void(*FileReaderCallback)(void *ctx);
    
    /**
     * A reader read data from file. use block I/O. derived from ThreadRunnable.
     */
    class FileReader : public THREAD::ThreadRunnable {
    public:
        FileReader(File *file) :_file(file) {};
        ~FileReader();
        
        /**
         * Override the run virtual method of ThreadRunnable.
         */
        virtual void run();
        
        /**
         * Read file data from FileReader buffer to param buffer.
         * @param buf BufferV type, will move the data from FileReader buffer to it.
         */
        void read(BufferV &buf);
        
        BufferV &getReadBuffer() { return _buf; };
        
        void setContext(void *ctx) { _ctx = ctx; };
        void setFileReaderCallback(FileReaderCallback fileReaderCallback) { _fileReaderCallback = fileReaderCallback; };
        
    private:
        File *_file;
        BufferV _buf;
        
        void *_ctx;
        FileReaderCallback _fileReaderCallback;
    };
    
}


#endif // end _ET_FILE_READER_
