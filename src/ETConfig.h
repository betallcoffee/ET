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

class ETBuffer;
class ETConnection;

const int kInvalidFD = -1;
const int kMaxConn = 128;

typedef void(*EventCallback)(void *);

typedef void(*NewConnectionCallback)(void *ctx, int fd); 

// ETConnction
typedef void(*MessageCallback)(void *ctx, ETConnection *conn, ETBuffer *msg);
typedef void(*WriteCompleteCallback)(void *ctx, ETConnection *conn);
typedef void(*CloseCallback)(void *ctx, ETConnection *conn);
typedef void(*ConnectCallback)(void *ctx, ETConnection *conn);

// ETTCPServer
typedef void(*ConnectionCb)(void *ctx, ETConnection *conn);

} // end namespace ET

#endif // ETCONFIG_H
