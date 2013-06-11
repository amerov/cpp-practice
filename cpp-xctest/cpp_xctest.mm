//
//  cpp_xctest.m
//  cpp-xctest
//
//  Created by Denny C. Dai on 2013-06-11.
//  Copyright (c) 2013 Denny C. Dai. All rights reserved.
//

#import <XCTest/XCTest.h>
#import "alist.hpp"
#import "llist.hpp"
#import "allist.hpp"
#include <iostream>

using namespace std;
using namespace dennycd;

@interface cpp_xctest : XCTestCase

@end

@implementation cpp_xctest

- (void)setUp
{
    [super setUp];
    
    // Set-up code here.
}

- (void)tearDown
{
    // Tear-down code here.
    
    [super tearDown];
}

- (void)testInitialization
{
    AList<int> alist = {1,2,3,4,56,7,8};
    LList<int> llist = {1,2,3,4,5,5,6,7};
    ALList<int> allist = {1,2,3,4,5,5,6,7};
    
    alist[0] = 13;
    llist[0] = 13;
    allist[0] = 13;
    
    cout << "find " << alist.find(56) << endl;
    cout << "find " << llist.find(5) << endl;
    cout << "find " << allist.find(5) << endl;
    
}

@end
