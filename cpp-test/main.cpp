//
//  main.cpp
//  cpp-test
//
//  Created by Denny C. Dai on 2013-06-10.
//  Copyright (c) 2013 Denny C. Dai. All rights reserved.
//

#include <iostream>
#include <gtest/gtest.h>

#include <iostream>
#include "alist.hpp"
#include "llist.hpp"

using namespace dennycd;
using namespace std;

TEST(ADTTest, DynamicArra){
    AList<int> alist = {1,2,3,4,56,7,8};
    LList<int> llist = {1,2,3,4,5,5,6,7};
    
    alist[0] = 13;
    llist[0] = 13;
    
    cout << "find " << alist.find(56) << endl;
    cout << "find " << llist.find(5) << endl;

}


int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

