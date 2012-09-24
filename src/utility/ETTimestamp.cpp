// Use of this source code is governed by a BSD-style license
//  that can be found in the License file.
//
//  Author: betallcoffee
//

#include <stdio.h>

#include "ETTimestamp.h"

using namespace ET;

ETTimestamp::ETTimestamp(long long microSecondsSinceEpoch)
{
    timeSinceEpoch_.tv_sec = microSecondsSinceEpoch / kMicroSecondsPerSecond;
    timeSinceEpoch_.tv_usec = microSecondsSinceEpoch % kMicroSecondsPerSecond;
    timeZone_.tz_minuteswest = 0;
    timeZone_.tz_dsttime = 0;
}

ETTimestamp::ETTimestamp(const ETTimestamp &rhs)
{
    *this = rhs;
}

ETTimestamp &ETTimestamp::operator=(const ETTimestamp &rhs)
{
    if (this != &rhs) {
        timeSinceEpoch_ = rhs.timeSinceEpoch_;
        timeZone_ = rhs.timeZone_;
    }
    return *this;
}

ETTimestamp ETTimestamp::now()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    long long microSecondsSinceEpoch = tv.tv_usec;
    microSecondsSinceEpoch += (long long)tv.tv_sec * kMicroSecondsPerSecond;
    return ETTimestamp(microSecondsSinceEpoch);
}

std::string ETTimestamp::toString() const
{
    char buf[32] = {0};
    snprintf(buf, sizeof(buf) - 1, "%d, %ld", timeSinceEpoch_.tv_sec, timeSinceEpoch_.tv_usec);
    return buf;
}

std::string ETTimestamp::toFormattedString() const
{
    char buf[32] = {0};
    long long sec = timeSinceEpoch_.tv_sec;
    ctime_r(&timeSinceEpoch_.tv_sec, buf);
    return buf;
}

