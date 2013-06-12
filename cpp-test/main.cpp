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
#include "allist.hpp"
#include "stack.hpp"
#include "queue.hpp"

#include "astack.hpp"
#include "lstack.hpp"
#include "lqueue.hpp"


using namespace dennycd;
using namespace std;

TEST(LQueueTest, test){
    
    LQueue<int> q;
    cout << q << endl;
    q.enqueue(1);
    cout << q << endl;
    q.enqueue(2);
    q.enqueue(3);
    cout << q << endl;
    
    EXPECT_TRUE(q.front()==1);
    EXPECT_TRUE(q.dequeue()==1);
    EXPECT_TRUE(q.dequeue()==2);
    EXPECT_TRUE(q.dequeue()==3);
    EXPECT_TRUE(q.empty());
    
    
    
}

TEST(LStackTest, test){
    
    LStack<int> stack;
    
    stack.push(1);
    EXPECT_TRUE(stack.top()==1 && stack.size()==1);
    EXPECT_TRUE(stack.pop()==1);
    EXPECT_TRUE(stack.empty());
    
    stack.push(2);
    stack.push(3);
    EXPECT_TRUE(stack.size()==2);
    cout << stack << endl;
    
}

TEST(AStackTest, test){
    
    AStack<int> stack;
    
    stack.push(1);
    EXPECT_TRUE(stack.top()==1 && stack.size()==1);
    EXPECT_TRUE(stack.pop()==1);
    EXPECT_TRUE(stack.empty());
    
    stack.push(2);
    stack.push(3);
    EXPECT_TRUE(stack.size()==2);
    cout << stack << endl;
    
}

TEST(QueueTest, test){
    
    {
        Queue<AList<int>, int> q = {1,2,3,4,5};
        cout << q << endl;
        
        //fonrt
        EXPECT_TRUE(q.front() == 5);
        
        //enqueu
        q.enqueue(6);  //O(n)
        EXPECT_TRUE(q.size()==6 && q.front() == 5);
        
        //dequeue
        EXPECT_TRUE(q.dequeue() == 5);  // O(1)
        EXPECT_TRUE(q.size() == 5);
        
        //copy
        Queue<AList<int>, int> newqueue(q);
        for(int i=0;i<5;i++)
            EXPECT_TRUE( q.dequeue() == newqueue.dequeue() );
        
        EXPECT_TRUE(q.empty() && newqueue.empty());
    }

    
    {
        Queue<LList<int>, int> q = {1,2,3,4,5};
        cout << q << endl;
        
        //fonrt
        EXPECT_TRUE(q.front() == 5); // O(N))
        
        //enqueu
        q.enqueue(6);
        EXPECT_TRUE(q.size()==6 && q.front() == 5);
        
        //dequeue
        EXPECT_TRUE(q.dequeue() == 5); //O(N)
        EXPECT_TRUE(q.size() == 5);
        
        //copy
        Queue<LList<int>, int> newqueue(q);
        for(int i=0;i<5;i++)
            EXPECT_TRUE( q.dequeue() == newqueue.dequeue() );  //O(N)
        
        EXPECT_TRUE(q.empty() && newqueue.empty());
    }
    
    
    {
        Queue<ALList<int>, int> q = {1,2,3,4,5};
        cout << q << endl;
        
        //fonrt
        EXPECT_TRUE(q.front() == 5);    //O(1)
        
        //enqueu
        q.enqueue(6);  //O(1)
        EXPECT_TRUE(q.size()==6 && q.front() == 5);
        
        //dequeue
        EXPECT_TRUE(q.dequeue() == 5); //O(1)
        EXPECT_TRUE(q.size() == 5);
        
        //copy
        Queue<ALList<int>, int> newqueue(q);
        for(int i=0;i<5;i++)
            EXPECT_TRUE( q.dequeue() == newqueue.dequeue() );
        
        EXPECT_TRUE(q.empty() && newqueue.empty());
    }
    
    
}

TEST(StackTest, test){
    
    
    {
    //dynamic array based stack
    Stack<AList<int>, int> stack = {1,2,3,4,5};
    EXPECT_TRUE(stack.size()==5 && stack.top()==1);
        cout << stack << endl;
    
    
    //push
    stack.push(6);   // O(N)
    EXPECT_TRUE(stack.top()==6);
    
    //pop
    EXPECT_TRUE( stack.pop() == 6);  // O(N)
    EXPECT_TRUE( stack.size()==5 && stack.top()==1);  //O(1)
    
    //copy
    Stack<AList<int>, int> newstack(stack); 
    for(int i=0;i<5;i++)
        EXPECT_TRUE( stack.pop() == newstack.pop() );
    }

    //link list-based stack
    {
        //dynamic array based stack
        Stack<LList<int>, int> stack = {1,2,3,4,5};
        EXPECT_TRUE(stack.size()==5 && stack.top()==1);  //O(1)
        cout << stack << endl;
        
        
        //push
        stack.push(6);   //O(1)
        EXPECT_TRUE(stack.top()==6);
        
        //pop
        EXPECT_TRUE( stack.pop() == 6); 
        EXPECT_TRUE( stack.size()==5 && stack.top()==1); 
        
        //copy
        Stack<LList<int>, int> newstack(stack);
        for(int i=0;i<5;i++)
            EXPECT_TRUE( stack.pop() == newstack.pop() );
    }

    //acylic link list-based stack
    {
        //dynamic array based stack
        Stack<ALList<int>, int> stack = {1,2,3,4,5};
        EXPECT_TRUE(stack.size()==5 && stack.top()==1);
        cout << stack << endl;
        
        
        //push
        stack.push(6);
        EXPECT_TRUE(stack.top()==6);
        
        //pop
        EXPECT_TRUE( stack.pop() == 6);
        EXPECT_TRUE( stack.size()==5 && stack.top()==1);
        
        //copy
        Stack<ALList<int>, int> newstack(stack);
        for(int i=0;i<5;i++)
            EXPECT_TRUE( stack.pop() == newstack.pop() );
    }
}


//dynamic array
TEST(AListTest, test){
    AList<int> list = {1,2,3};

    EXPECT_TRUE(list.find(1)==0);
    EXPECT_TRUE(list.find(3)==2);
    EXPECT_TRUE(list.find(2)==1);
    EXPECT_TRUE(list.find(99)==-1);
    
    //accessor
    EXPECT_TRUE(list[0]==1 && list[1]==2 && list[2]==3);
    EXPECT_TRUE(list.get(0)==1);
    cout << list << endl;
    
    //setter
    list.set(0, 8);
    EXPECT_TRUE(list.get(0)==8);
    cout << list << endl;

    //insertion at front
    list.insert(0, 17);
    EXPECT_TRUE(list[0] == 17);
    EXPECT_TRUE(list.size()==4);
    cout << list << endl;
    
    //insert at tail
    list.insert((int)list.size(), 99);
    EXPECT_TRUE(list[(int)list.size()-1]==99);
    EXPECT_TRUE(list.size()==5);
    cout << list << endl;
    
    //insertt at mid
    list.insert(3, 77);
    EXPECT_TRUE(list[3]==77);
    EXPECT_TRUE(list.size()==6);
    cout << list << endl;
    
    //removal
    list.remove(0);
    EXPECT_TRUE(list.size()==5 && list[0] == 8);
    cout << list << endl;
    
    list.remove((int)list.size()-1);
    EXPECT_TRUE(list.size()==4 && list[(int)list.size()-1]==3);
    cout << list << endl;
    
    
    //copy
    AList<int> newlist(list);
    EXPECT_TRUE(list.size()==newlist.size());
    for(int i=0;i<list.size();i++)
        EXPECT_TRUE(list[i] == newlist[i]);
}

//singly link list
TEST(LListTest, test){
    LList<int> list = {1,2,3};
    cout << list << endl;
    
    EXPECT_TRUE(list.find(1)==0);
    EXPECT_TRUE(list.find(3)==2);
    EXPECT_TRUE(list.find(2)==1);
    EXPECT_TRUE(list.find(99)==-1);
    
    //accessor
    EXPECT_TRUE(list[0]==1 && list[1]==2 && list[2]==3);
    EXPECT_TRUE(list.get(0)==1);
    cout << list << endl;
    
    //setter
    list.set(0, 8);
    EXPECT_TRUE(list.get(0)==8);
    cout << list << endl;
    
    //insertion at front
    list.insert(0, 17);
    EXPECT_TRUE(list[0] == 17);
    EXPECT_TRUE(list.size()==4);
    cout << list << endl;
    
    //insert at tail
    list.insert((int)list.size(), 99);
    EXPECT_TRUE(list[(int)list.size()-1]==99);
    EXPECT_TRUE(list.size()==5);
    cout << list << endl;
    
    //insertt at mid
    list.insert(3, 77);
    EXPECT_TRUE(list[3]==77);
    EXPECT_TRUE(list.size()==6);
    cout << list << endl;
    
    //removal
    list.remove(0);
    EXPECT_TRUE(list.size()==5 && list[0] == 8);
    cout << list << endl;
    
    list.remove((int)list.size()-1);
    EXPECT_TRUE(list.size()==4 && list[(int)list.size()-1]==3);
    cout << list << endl;

    //copy
    LList<int> newlist(list);
    EXPECT_TRUE(list.size()==newlist.size());
    for(int i=0;i<list.size();i++)
        EXPECT_TRUE(list[i] == newlist[i]);
}


//singly acylic link list
TEST(ALList, test){
    ALList<int> list = {1,2,3};
    
    EXPECT_TRUE(list.find(1)==0);
    EXPECT_TRUE(list.find(3)==2);
    EXPECT_TRUE(list.find(2)==1);
    EXPECT_TRUE(list.find(99)==-1);
    
    //accessor
    EXPECT_TRUE(list[0]==1 && list[1]==2 && list[2]==3);
    EXPECT_TRUE(list.get(0)==1);
    cout << list << endl;
    
    //setter
    list.set(0, 8);
    EXPECT_TRUE(list.get(0)==8);
    cout << list << endl;
    
    //insertion at front
    list.insert(0, 17);
    EXPECT_TRUE(list[0] == 17);
    EXPECT_TRUE(list.size()==4);
    cout << list << endl;
    
    //insert at tail
    list.insert((int)list.size(), 99);
    EXPECT_TRUE(list[(int)list.size()-1]==99);
    EXPECT_TRUE(list.size()==5);
    cout << list << endl;
    
    //insertt at mid
    list.insert(3, 77);
    EXPECT_TRUE(list[3]==77);
    EXPECT_TRUE(list.size()==6);
    cout << list << endl;
    
    //removal
    list.remove(0);
    EXPECT_TRUE(list.size()==5 && list[0] == 8);
    cout << list << endl;
    
    list.remove((int)list.size()-1);
    EXPECT_TRUE(list.size()==4 && list[(int)list.size()-1]==3);
    cout << list << endl;

    //copy
    ALList<int> newlist(list);
    EXPECT_TRUE(list.size()==newlist.size());
    for(int i=0;i<list.size();i++)
        EXPECT_TRUE(list[i] == newlist[i]);
}


int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

