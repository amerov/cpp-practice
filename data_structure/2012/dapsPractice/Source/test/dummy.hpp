//
//  dummy.h
//  dapsPractice
//
//  Created by Denny C. Dai on 2012-08-22.
//  Copyright (c) 2012 Denny C. Dai. All rights reserved.
//

#ifndef __dapsPractice__dummy__
#define __dapsPractice__dummy__

#include <iostream>

//unnamed namespace
namespace{


}

template <typename T>
class Dummy {
protected:
    T data;
    
public:
    void test_func(const T& origin);
};

//Template Method Definitions
template <typename T>
void Dummy<T>::test_func(const T& origin) {
    this->data = origin;
    std::cout << "test_func" << std::endl;
}



//polymorphysim : ability to associate many meanings to one function name by means of a the late-binding mechanism
//   virtual function - late binding - polymorphism
class Test{
protected:

public:
    Test(){;}
    virtual ~Test(){ std::cout << "~Test()" << std::endl; }  
    //all subclasses overriding this function is also a virtual function
    virtual void test_func() const{; }  //virtual function, waiting until runtime to determine the implmenetation of this function    
    virtual void dummy_func() = 0; //pure virutal function, classs is abstract class
    
};

class SubTest : public Test{
public:
    SubTest() : Test() {}
    ~SubTest(){std::cout << "~SubTest()" << std::endl;}  //automatically is virtual since base class destructor is virtual
    void test_func() const { std::cout << "SubTest test func" << std::endl;} //if a virutal function, we call it function overrride , otherwise redefine
    void dummy_func(){;}
    
    
    SubTest& operator =(const SubTest& rst){
        if(this != &rst)
        {
            
        }
        return *this;
    }
    
    SubTest(const SubTest& rst){}
};


class SubSubTest : public SubTest{
public:

    SubSubTest() : SubTest() {}
    
    SubSubTest(const SubSubTest& rst) : SubTest(rst) {}
    SubSubTest& operator =(const SubSubTest& rst){
        SubTest::operator=(rst);
        return *this;
    }

    ~SubSubTest(){std::cout << "~SubSubTest()" << std::endl;}
    void test_func() const { std::cout << "SubSubTest test func" << std::endl;}
};


class SubSubSubTest : private SubSubTest{
public:
    void my_test(){
        this->test_func();
    }
};

#endif /* defined(__dapsPractice__dummy__) */
