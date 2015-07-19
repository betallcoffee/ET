/*
 * String
 *
 *  Created on: Feb 26, 2015
 *      Author: liang
 */

#ifndef ET_STRING_H
#define ET_STRING_H

#include <vector>
#include <string>

namespace ET {

namespace STRING {

std::vector<std::string> splite(const std::string &str, const std::string &sep = " ", bool isLoop = true);
    
    void trim(std::string &str);

}

}


#endif /* STRING_ */
