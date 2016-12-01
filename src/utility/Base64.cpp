//
//  Base64.cpp
//  ET
//
//  Created by liang on 10/7/16.
//  Copyright © 2016 liangliang. All rights reserved.
//

#include "Base64.h"

static const char base64_enc_map[64] =
{
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
    'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
    'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd',
    'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
    'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x',
    'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7',
    '8', '9', '+', '/'
};

static const char base64_dec_map[128] =
{
    127, 127, 127, 127, 127, 127, 127, 127, 127, 127,
    127, 127, 127, 127, 127, 127, 127, 127, 127, 127,
    127, 127, 127, 127, 127, 127, 127, 127, 127, 127,
    127, 127, 127, 127, 127, 127, 127, 127, 127, 127,
    127, 127, 127, 62, 127, 127, 127, 63, 52, 53,
    54, 55, 56, 57, 58, 59, 60, 61, 127, 127,
    127, 64, 127, 127, 127, 0, 1, 2, 3, 4,
    5, 6, 7, 8, 9, 10, 11, 12, 13, 14,
    15, 16, 17, 18, 19, 20, 21, 22, 23, 24,
    25, 127, 127, 127, 127, 127, 127, 26, 27, 28,
    29, 30, 31, 32, 33, 34, 35, 36, 37, 38,
    39, 40, 41, 42, 43, 44, 45, 46, 47, 48,
    49, 50, 51, 127, 127, 127, 127, 127
};

using namespace ET;

void Base64::encode(const std::string &s) {
    _plain.assign(s);
    _base64.clear();
    const char *cs = _plain.c_str();
    for (int i = 3; i < _plain.size(); i += 3) {
        char c1 = cs[i-3];
        char c2 = cs[i-2];
        char c3 = cs[i-1];
        
        _base64.append(base64_enc_map + (c1 >> 2 & 0x3f), 1);
        _base64.append(base64_enc_map + (((c1 << 4) | (c2 >> 4)) & 0x3f), 1);
        _base64.append(base64_enc_map + (((c2 << 2) | (c3 >> 6)) & 0x3f), 1);
        _base64.append(base64_enc_map + (c3 & 0x3f), 1);
    }
    
    int r = s.size() % 3;
    
    if (r) {
        char c1 = cs[s.size()-2];
        _base64.push_back(base64_enc_map[(c1 >> 2 & 0x3f)]);
        
        if (r > 1) {
            char c2 = cs[s.size()-1];
            _base64.push_back(base64_enc_map[(((c1 << 4) | (c2 >> 4)) & 0x3f)]);
            _base64.push_back(base64_enc_map[((c2 << 2) & 0x3f)]);
        } else {
            _base64.push_back(base64_enc_map[((c1 << 4) & 0x3f)]);
            _base64.push_back('=');
        }
        
        _base64.push_back('=');
    }
}

void Base64::decode(const std::string &s) {
    _base64.assign(s);
    _plain.clear();
    const char *cs = _base64.c_str();
    for (int i = 0; i < _base64.size(); i += 4) {
        char c1 = cs[i];
        char c2 = cs[i+1];
        char c3 = cs[i+2];
        char c4 = cs[i+3];
        
        _plain.push_back(char((base64_dec_map[c1] << 2) | (base64_dec_map[c2] >> 4)));
        if (c3 != '=') {
            _plain.push_back(char((base64_dec_map[c2] << 4) | (base64_dec_map[c3] >> 2)));
            if (c4 != '=') {
                _plain.push_back(char((base64_dec_map[c3] << 6) | base64_dec_map[c4]));
            }
        }
    }
}
