//
//  myclass.cpp
//  dapsPractice
//
//  Created by Denny C. Dai on 2012-08-24.
//  Copyright (c) 2012 Denny C. Dai. All rights reserved.
//

#include "myclass.h"

int MY_DATA = 1001;

//this still exist in global namespace, although its spec not in header, others can still call it !
void global_myclass_func(){
    std::cout << "global_myclass_func in myclass.cpp!!" << std::endl;
}

//unnamed namespace for deinitions only available in this local compilation unit
//no other module can access or call it here!!!
//use it instead of using static
namespace {
    
    void local_myclass_func(){
        std::cout << "local_myclass_func" << std::endl;
    }

}