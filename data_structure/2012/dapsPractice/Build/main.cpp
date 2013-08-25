//
//  main.cpp
//  dapsPractice
//
//  Created by Denny C. Dai on 2012-07-31.
//  Copyright (c) 2012 Denny C. Dai. All rights reserved.
//

#include <iostream>
#include <vector>
#include <string>
#include <list>

using namespace std;

void cplusplus11Test();


class BaseClass{
public:
    BaseClass(){ cout << "BaseClass()" << endl; }
    virtual ~BaseClass(){ cout << "~BaseClass()" << endl; }
};

class MyClass : public BaseClass{
public:
    MyClass(){ cout << "MyClass" << endl;}
    ~MyClass(){ cout << "~MyClass" << endl; }
};


int main(int argc, char* argv[])
{
    BaseClass* p = new MyClass();
    delete p;
    
    


    vector<string> words;
    
    words.push_back("Denny");
    words.push_back("Chen");
    words.push_back("Dai");


    for(vector<string>::const_iterator it = words.begin(); it!=words.end(); it++)
    {
        cout << *it << endl;
    }

    cplusplus11Test();
}




void cplusplus11Test()
{
#ifdef __cplusplus
    long x = __cplusplus;
    if(x > 199711L)
        cout << "<-- under C++ 11 mode with __cplusplus equals " << x <<  " -->" << endl;
#endif
}