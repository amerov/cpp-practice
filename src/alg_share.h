//
//  alg_share.h
//  cpp-practice
//
//  Created by Denny C. Dai on 2013-06-12.
//  Copyright (c) 2013 Denny C. Dai. All rights reserved.
//

#ifndef cpp_practice_alg_share_h
#define cpp_practice_alg_share_h

#include <iostream>
#include <functional>
#include <cmath>
#include <cassert>
#include <cstdlib>

namespace dennycd{

#define swap(x,y) \
{auto temp = y; y = x; x = temp;}
    
//return reference to the middle value item
template<class T>
const T* mid(const T& x, const T& y, const T& z){
    if((x >= y && x <= z) || (x >= z && x <= y)) return &x;
    if((y > x && y < z) || (y >= z && y <= z)) return &y;
    if((z >= x && z <= y) || (z >= y && z <= x)) return &z;
    return &z;
}
    
}
#endif
