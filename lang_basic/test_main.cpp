//
//  main.cpp
//  dapsPractice
//
//  Created by Denny C. Dai on 2012-07-31.
//  Copyright (c) 2012 Denny C. Dai. All rights reserved.
//

#include <iostream>
#include <iomanip>  //iostream manipulator

#include <cstring>
#include <cctype>

#include <vector>
#include <string>
#include <list>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <utility>   // pair

#include <algorithm>  //generic algorithms

#include <exception> //for exception class

#include <new>

#include <cstddef> // NULL

#include "dummy.hpp"

#include <fstream>

#define NDEBUG
#include <cassert>

using namespace std;
//using std::cout;
//using std::endl;
//using std::vector;
//using std::string;
//using std::list;

void cplusplus11Test();


struct Data{
    string name = "dennycd";
};

typedef struct Node
{
    string data;
    Node* next;
    
    Data self;
    
    //callable   Node()
    int operator()(int val){
        cout << "calling Node with " << val << endl;
        return 1;
    }
    
    //overload pointer operator
    const Data* operator ->(){
        return &self;
    }

    
    //somehow compiler allows to overload addressing operator...
    long operator &(){
        return 0;
    }
    
    //dereferecing   *node
    string operator *(){
        return "DennyCD";
    }
    
    //type casting   (int)node
    operator int(){
        return 2;
    }
    
    //equality operator overload
    bool operator ==(const struct Node& rnode){
        return true;
    }
    
    //default consttuctor
    Node(){
        this->data = "";
    }
    
    //copy constructor
    Node(const Node& rnode){
        cout << "copy constructor" << endl;
        this->data = rnode.data;
    }
    
    //assignment operator overload
    Node& operator =(const Node& rnode){
        cout << "assignment operator overload" << endl;
        this->data = rnode.data;
        return *this;
    }
    
    
    friend istream& operator >>(istream& lis, Node& robj);
    friend ostream& operator <<(ostream& los, Node& robj);
    
}LNode;
typedef LNode* NodePtr;

//input stream extraction operator
istream& operator >>(istream& lis, LNode& robj)
{
    lis >> robj.data;
    return lis;
}

//outoyt stream
ostream& operator <<(ostream& los, Node& robj)
{
    los << robj.data;
    return los;
}



class MyException : public std::exception{
public:
    string msg = "";
public:
    MyException(){
        cout << "MyException() " << this << endl;
    }
    
    MyException(string msg){
        this->msg = msg;
        cout << "MyException(msg) " << this << endl;
    }
    
    ~MyException(){
        cout << "~MyException()" << this << endl;
    }
};



class BaseClass{
public:
    BaseClass(string name){ cout << "BaseClass(name)" << endl;}
    BaseClass(){ cout << "BaseClass() " << endl; }
    virtual ~BaseClass(){ cout << "~BaseClass() " << endl; }
    virtual void test_func() throw(std::exception){}   //so std::exception is more general than MyException so the exception spec is still valid in myclasss
};

class MyClass : public BaseClass{
public:
    MyClass() : BaseClass("dennycd") { cout << "MyClass " << endl;}
    ~MyClass(){ cout << "~MyClass " << endl; }
    void test_func() throw(MyException){ throw MyException("hall");}
    
};

//if throw() but then throw an exception, it will terminate the program
//that forcess to say this function does not throw any exception at all
void test_func() throw (MyException, std::exception)
{
    throw MyException("test_func exp");
}


template<typename T>
class MyTempClass{
public:
    void test(MyTempClass<T>*& ref);
};

template<typename T>
void MyTempClass<T>::test(MyTempClass<T>*& ref){
    ref = NULL;
}


class CommonClass {
private:
    string name = "Denny";
    friend void friend_func(CommonClass& obj);
public:
    void print(){cout << "name is " << name << endl;}
};

void friend_func(CommonClass& obj)
{
    obj.name = "ChenDai";
}


void unexpected_handle_func()
{
    cout << "unexpected happens" << endl;
    exit(1);
}

template <typename T>
T test_template_func() {
   T x = 1;
   return x;
}

namespace dennycd{
  namespace test{
    string name = "Denny";
  }
}

extern void global_myclass_func();
extern void local_myclass_func();
extern int MY_DATA;

void test(char ss[])
{
   printf("address is %X \n", ss);
    cout << ss << endl;
}


class LocalClass{
public:
    string data = "";
    void update() const{ cout << "updating " << data << " on " << this << endl; };
    
    LocalClass(){cout << "LocalClass()" << endl;}
    LocalClass(const LocalClass& lc){ cout << "LocalClass(lc)" << endl;}
    ~LocalClass(){ cout << "~LocalClass() " << data << endl;}
};

class AnoClass{
public:
    AnoClass(){ cout << "AnoClass()" << endl;   obj.data = "some secret content";}
    
    const LocalClass& test(){ cout << "local address is " << &obj << endl;  return obj; }
    
    //return a local class obj
    LocalClass test_return(){ LocalClass o; o.data = "some local data"; return o;}
    
private:
    LocalClass obj;
};

class TestBaseClass{
//private  - default 
    int base_var = 1; 
};

class TestClass : public TestBaseClass{
public:
    TestClass() : myobj(1,2)  //invoke member variable's constructor
    {
        cout << "TestClass()" << endl;        
    }
    
    TestClass(const TestClass& obj) : myobj(1,2)
    {
        cout << "TestClass(&obj)" << endl;
    }
    
    TestClass& operator =(const TestClass& obj){
        if(this!=&obj)
        {
            
        }
        
        cout << "TestClass operator =" << endl;
        return *this;
    }
    
    static int count;
    static void testClassFunc();
    
    //nested classs definition
    class TestSubClass{
    public:
        TestSubClass(int x, int y){
        }
    };
    
    
private:
    TestSubClass myobj;
};

int TestClass::count = 0;
void TestClass::testClassFunc(){


    //a local class definition inside a function !!
    class localClassDef{

    };
}

struct TestStruct{
    int data;
    float value;
    char name[10];
}TestStructName1, TestStructName2;

int testA[] = {1,2,3};


void test_arr_string_v2(const char * ptr)
{
    ptr = NULL; //can modify ptr itself, but not its content
    //ptr[0] = '1';
}


void test_arr_string(char * const ptr)
{
    //ptr = NULL;  //the variable itself is consnt, cannot be assigned other value, but it's pointing content can be modified
    ptr[0] = '1';
}


void  test_arr_func(const int arg[]){
//    cout << "passed in size " << sizeof(arg) << endl; //which only gives the pointer address size
}

//v1 actuall has the same address as the calling variable !!!
void test_by_reference(int& v1)
{
    int* ptr = &v1;
    cout << "v1 address " << ptr << endl;
}

int main(int argc, char* argv[])
{
    
    assert(NULL);
    

    int val = 2;
    cout << "val address " << &val << endl;
    test_by_reference(val);

    int mm[][2] = {1,2, 3,4};
    
//    char cc[][2] = {'x', 'y', 'z', 'k'};
//    string sss[][2] = {"x", "y", "z", "k"};
    
    
    cout << "mm array size " << sizeof(mm) << endl;

//    TestStruct ts = {2, 1.23f, "dennycd"};
    
    int xx[] = {1,2,3+2,4,5};
    
    
    test_arr_func(xx); //compiler will ignore the declared arg[3]'s 3 
    
    int* yy = xx;
    cout << sizeof(xx) << endl; //actuall gives the entire size of the array 3*sizeoof(int)
    cout << sizeof(yy) << endl; //just the address pointer size which is 8 bytes - 64 bit pointer 

//    TestClass::TestSubClass ssobj;
    

    TestClass obj; //default constructor call
    obj =  TestClass();  //default constructor call, then operator =
    
    
    TestClass obj1 = TestClass(); //default constructor call (no assignment call!!!)

    obj1.count = 0;
    TestClass::testClassFunc();




    AnoClass o;
    

    cout << "calling" << endl;

    o.test().update();
//    const LocalClass *ptr =  &(o.test());
//    cout << "address is " << ptr << endl;
//    ptr->update();
    
//    o.test_return().update();
    


//    AnoClass* p = NULL;
    
//    cout << &AnoClass() << endl;
//    (p = &(AnoClass()))->test();
    

    char ss[] = "Hello World";
    ss[0] = 'R';
    
//    printf("address is %X \n", (void*)ss);
    test(ss);

    int x = 1;
    int* p = &x;
    
    cout << "size of p " << sizeof(p) << setw(20) << p << endl;
    cout << "int bytes " << sizeof(int) << endl;
    cout << "long bytes " << sizeof(long) << endl;
    cout << "double bytes " << sizeof(double) << endl;

    
    using namespace dennycd::test;
    
    cout << MY_DATA << endl;
    
    global_myclass_func();
    //local_myclass_func();
    
    LNode node;
    node.data = "dennycd";
    
    cout << node->name << endl;
    
    cout << "node address " << &node << endl;
    
    cout << node << endl;
    
    //cout.unsetf();
   
//    //cout.setf(ios::scientific);
    cout.setf(ios::fixed); //display floating point numbers in fixed-point notation ( compare to scientific-e notations)
    cout.setf(ios::showpoint); //always include a decimal point in floating point numbers
//    //cout.setf(ios::showpos);
//    cout.precision(2);
    //cout.setf(ios::fixed | ios::showpoint); //can do a bitwise or


//    cout.setf(ios::hex | ios::showbase | ios::basefield);

    

//    double x = 100.0/3.0;
    
    cout.setf(ios::showbase);
    cout << hex << 15 << endl;

    
    ifstream ifs;
    ofstream ofs;

    int x1= 2, x2 = 3;
    
    ifs.open("test.txt");
    if(!ifs.fail())
    {
        int x;
        while(!ifs.eof())
        {
            ifs >> x;
            cout << x << "\t";
        }
//        //extraction operator
//        ifs >> x1 >> x2 >> x3;
//        ifs.close();
//        cout << x1 << "-" << x2 << "-" << x3 << endl;    
    }
    
    
    //open to append
    ofs.open("out.txt", ios::app);
    if(!ofs.fail())
    {
        ofs << "x=" << x1 << "\ty=" << x2 << "\n";
        ofs.close();    
    }




//    string input;
//    cout << "enter your fuzz";
//    cin  >> input;
//    

    /*
    SubSubSubTest ssst;
    ssst.my_test();
    */
    
    /*
    Test* t = new SubSubTest();
    
    
    SubSubTest* sst = dynamic_cast<SubSubTest*>(t);
    if(sst!=NULL)
        sst->test_func();
    delete t;
    
    
    SubTest test1;
    SubSubTest test2;
    
    try{
        test1 =  static_cast<SubTest>(test2); //upcast is allowed, slicing problem, but legal
        test1.test_func();
    }
    catch(bad_cast bc)
    {
        cout << "bad static cast " << endl;
    }
    */
    
    /*
    basic_string<MyClass> xx;

    int ret = test_template_func<int>();
    cout << ret << endl;

    Dummy<string> dumobj;
    dumobj.test_func("dennycd");
    
    Node xnode, ynode;
    cout << "typecast " << (int)xnode << endl;
    cout << "dereferencing " << *xnode << endl;
    cout << "compare " << (xnode == ynode) << endl;
    cout << "function obj " << xnode(2) << endl;
    
    Node znode = xnode;
    znode = xnode;
    
    CommonClass cc;
    friend_func(cc);
    cc.print();
    
    /// If you write a replacement %unexpected handler, it must be of this type.
    //typedef void (*unexpected_handler) ();
    
    MyTempClass<string>* obj = new MyTempClass<string>();
    MyTempClass<string>* obj2 = new MyTempClass<string>();
    
    cout << "obj is " << obj << endl;
    obj2->test(obj);
    cout << "obj is " << obj << endl;
    
    
    set<string> names;
    names.insert("Denny");
    names.insert("Chen");
    names.insert("Dai"); names.insert("Dai");
    
    //non-modifying generic functions
    set<string>::const_iterator loc = find(names.begin(), names.end(), "Denny");
    
    
    if(loc != names.end())
        cout << "found " << *loc << endl;
    
    
    try{
        test_func();
        //throw MyException("hello world exception");
    }
    catch(MyException e)
    {
        cout << "catching exception " << &e << " : " << e.msg << endl;
    }
    catch(std::exception e){
        cout << "catching std exception " << endl;
    }
    catch(...)
    {
        cout << "something unexpected" << endl;
        
        terminate();
    }
    
    
    
    //    set<string>::iterator it = names.find("Chen");
    //    if(it!=names.end())
    //        cout << "found " << *it << endl;
    //
    //    MyClass obj;
    //    map<string, MyClass> maps;
    //
    //    maps.insert(pair<string, MyClass>("denny",obj));
    
    
    BaseClass* p = new MyClass();
    try{
        p->test_func();
    }
    catch(MyException e){
        cout << "my exception " << endl;
    }
    delete p;
    
    //    stack<string, vector<string>> names;
    
    
    //    std::list<string> names;
    //    names.push_back("Denny");
    //    names.push_back("Chen");
    //    names.push_back("Dai");
    
    
    //    vector<string> words;
    //    typedef vector<string>::const_iterator wordIT;
    //
    //    words.insert(words.begin(), "Denny");
    //    words.insert(words.begin(), "Chen");
    //    words.insert(words.begin(), "Dai");
    
    //    words.push_back("Denny");
    //    words.push_back("Chen");
    //    words.push_back("Dai");
    
    
    //    for(wordIT it = words.begin(); it!=words.end(); it++)
    //        cout << *it << endl;
    
    //    for(vector<string>::const_reverse_iterator it = words.rbegin(); it != words.rend(); it++)
    //        cout << *it << endl;
    
    //    //random access
    //    cout << words[2] << endl;
    //
    //    wordIT it = words.begin();
    //    cout << *(it+2) << endl;
    
    set_unexpected(unexpected_handle_func);
    unexpected();
    
    */
    
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