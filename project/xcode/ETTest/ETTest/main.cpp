//
//  main.cpp
//  ETTest
//
//  Created by liang on 10/1/16.
//  Copyright © 2016 tina. All rights reserved.
//

#include <regex>
#include <iostream>

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    std::string emailPattern("(\\w)+(\\.\\w+)*@(\\w)+(\\.\\w+)+");
    std::string pathPattern("/?(\\w+)(\\.html)");
    try {
        std::regex emailRegex(emailPattern);
        std::string testString = "liangliang@126.com";
        for (std::sregex_iterator it(std::begin(testString), std::end(testString), emailRegex), endIt; it != endIt; it++) {
            printf("email %s", it->str().c_str());
        }
        
        std::regex pathRegex(pathPattern);
        std::smatch resutls;
        std::string testPath = "/test.html";
        if (std::regex_match(testPath, resutls, pathRegex)) {
            printf("match result");
        }
    } catch (std::regex_error e) {
        
    }

    return 0;
}
