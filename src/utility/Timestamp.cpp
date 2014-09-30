// Use of this source code is governed by a BSD-style license
//  that can be found in the License file.
//
//  Author: betallcoffee
//

#include <stdio.h>

#include "Timestamp.h"

using namespace ET;

Timestamp::Timestamp(long long microSecondsSinceEpoch)
{
    timeSinceEpoch_.tv_sec = microSecondsSinceEpoch / kMicroSecondsPerSecond;
    timeSinceEpoch_.tv_usec = microSecondsSinceEpoch % kMicroSecondsPerSecond;
    timeZone_.tz_minuteswest = 0;
    timeZone_.tz_dsttime = 0;
}

Timestamp::Timestamp(const Timestamp &rhs)
{
    *this = rhs;
}

Timestamp &Timestamp::operator=(const Timestamp &rhs)
{
    if (this != &rhs) {
        timeSinceEpoch_ = rhs.timeSinceEpoch_;
        timeZone_ = rhs.timeZone_;
    }
    return *this;
}

Timestamp Timestamp::now()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    long long microSecondsSinceEpoch = tv.tv_usec;
    microSecondsSinceEpoch += (long long)tv.tv_sec * kMicroSecondsPerSecond;
    return Timestamp(microSecondsSinceEpoch);
}

std::string Timestamp::toString() const
{
    char buf[32] = {0};
    snprintf(buf, sizeof(buf) - 1, "%ld, %d", timeSinceEpoch_.tv_sec, timeSinceEpoch_.tv_usec);
    return buf;
}

std::string Timestamp::toFormattedString() const
{
    char buf[32] = {0};
    ctime_r(&timeSinceEpoch_.tv_sec, buf);
    return buf;
}

