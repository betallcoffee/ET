// Use of this source code is governed by a BSD-style license
//  that can be found in the License file.
//
//  Author: betallcoffee
//

#ifndef ETTIMESTAMP_H
#define ETTIMESTAMP_H

#include <sys/time.h>
#include <string>

namespace ET
{
    //
    // Timestamp in UTC, in millionsecond resolution.
    //
    // This class is immutable.
    // It's recommended to pass it by value.
    //
    class Timestamp
    {
    public:
        Timestamp()
        {
            timeSinceEpoch_.tv_sec = 0;
            timeSinceEpoch_.tv_usec = 0;
            timeZone_.tz_minuteswest = 0;
            timeZone_.tz_dsttime = 0;
        }

        explicit Timestamp(long long microSecondsSinceEpoch);
        Timestamp(const Timestamp &rhs);
        ~Timestamp() {};

        Timestamp &operator=(const Timestamp &rhs);

        static Timestamp now();

        std::string toString() const;
        std::string toFormattedString() const;
        long long microSecondsSinceEpoch() 
        {
            return timeSinceEpoch_.tv_sec * kMicroSecondsPerSecond + timeSinceEpoch_.tv_usec;
        }

    private:
        static const int kMicroSecondsPerSecond = 1000 * 1000;
        struct timeval timeSinceEpoch_;
        struct timezone timeZone_;

    }; // end class Timestamp
} // end namespace ET

#endif // end ETTIMESTAMP_H
