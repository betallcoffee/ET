cmake_minimum_required(VERSION 2.8.11)

project(ET)



include_directories(
    /Users/liang/Workspace/projects/ET/ET/
    /Users/liang/Workspace/projects/ET/ET/

)

# Linker options
set(CMAKE_LDFLAGS "${CMAKE_LDFLAGS}  ")

# Library path
set(CMAKE_LDFLAGS "${CMAKE_LDFLAGS} -L\".\" ")

# Define the CXX sources
set ( CXX_SRCS
    ../src/ETAcceptor.cpp
    ../src/ETBuffer.cpp
    ../src/ETBufferV.cpp
    ../src/ETConnection.cpp
    ../src/ETConnector.cpp
    ../src/ETEpollSelect.cpp
    ../src/ETEventLoop.cpp
    ../src/ETKqueueSelect.cpp
    ../src/ETSelect.cpp
    ../src/ETTCPServer.cpp
    ../src/ETWatcher.cpp
)

set_source_files_properties(
    ${CXX_SRCS} PROPERTIES COMPILE_FLAGS 
    " -g")

add_library(ET ${CXX_SRCS} ${C_SRCS})

