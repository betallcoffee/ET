// Use the source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: betallcoffee
//
// This is an public header file, it must only include public header files.

#ifndef ETCONFIG_H
#define ETCONFIG_H

namespace ET
{

class BufferV;
class Connection;

const int kInvalidFD = -1;
const int kMaxConn = 128;

// Watcher
typedef void(*EventCallback)(void *);

// Acceptor/Connector
typedef void(*NewConnectionCallback)(void *ctx, int fd); 

// ETConnction
typedef void(*ReadDataCallback)(void *ctx, Connection *conn, BufferV *data);
typedef void(*WriteCompleteCallback)(void *ctx, Connection *conn);
typedef void(*CloseCallback)(void *ctx, Connection *conn);
typedef void(*ConnectCallback)(void *ctx, Connection *conn);

// TCPServer
typedef void(*ConnectionCb)(void *ctx, Connection *conn);

} // end namespace ET

#endif // ETCONFIG_H
