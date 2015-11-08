// Use the source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: betallcoffee
//
// This is an public header file, it must only include public header files.

#ifndef _ET_NET_H
#define _ET_NET_H

namespace ET
{

class BufferV;
class Connection;

const int kInvalidFD = -1;
const int kMaxConn = 128;

// Watcher
typedef void(*EventCallback)(void *);

// Acceptor/Connector
typedef void(*NewSocketCallback)(void *ctx, int fd);

// ETConnction
typedef void(*ReadDataCallback)(void *ctx, Connection *conn);
typedef void(*WriteCompleteCallback)(void *ctx, Connection *conn);
typedef void(*CloseCallback)(void *ctx, Connection *conn);
typedef void(*ConnectCallback)(void *ctx, Connection *conn);

// TCPServer
typedef void(*ConnectionCb)(void *ctx, Connection *conn);

} // end namespace ET

#endif // _ET_NET_H
