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

const int kInvalidFD = -1;
const int kMaxConn = 128;

typedef void(*EventCallback)(void *);

} // end namespace ET

#endif // ETCONFIG_H
