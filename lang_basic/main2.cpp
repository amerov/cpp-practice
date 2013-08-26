//
//  main.cpp
//  dapsPractice
//
//  Created by Denny C. Dai on 2013-04-13.
//  Copyright (c) 2013 Denny C. Dai. All rights reserved.
//
#include <iostream>
#include <string>
using std::cout;
using std::cin;
using std::ios;
using std::endl;
using std::string;
using std::ostream;
using std::istream;

//turn off debug
//#define NDEBUG
#include <cassert>

typedef enum{
    TYPE1,
    TYPE2
}MY_TYPE;

/**
  static local objects
 
  variables are in the scope of the defining function, but persisten acrosss calls of the function
 **/
void another(){
    
    //gurantteed to be initialized no later than the first time when this function is callled 
    static int val = 1;
    
}


void test1(int& input){
    cout << "in-func address is " << &input << endl;
}

struct MyStruct{
    string name; //default to be public 
};


/**
 If you define a class and include absolutely no constructors of any kind, then a default constructor will be automatically created
 
  If your class definition includes one or more constructors of any kind, no constructor is generated automatically
 **/
class MyClass {
    string name;  //default to be private 
    
public:
    MyClass(); //default constructor
    
    MyClass(const MyClass& obj);
    MyClass& operator =(const MyClass& obj);
    
    //automatic type conversion constructor
    MyClass(int val){
       cout << "converting " << val << endl;
    };
    
    ~MyClass();

    //ok to retunrn a private var by constant reference, this avoids invocation of copy
    //the returned is an anonymous reference var of  this->name, and is immutable
    const string& getName() const{ return this->name; }
    
    //he code for an inline function declaration is inserted at each location where the function is invoked. This saves the overhead of a function invocation.
    inline void good(){
        cout << "inline good" << endl;
        this->name = "good";
    };
    
    void foo(const int& val) const;
    static void FOO();
    
private:
    static int age;
    static const int exp = 20; //an integral const static member can be initialized inside
    
    static void class_func();
    
    friend const MyClass operator +(const MyClass& lv, const MyClass& rv); //allow function to access private member vars
    friend ostream& operator <<(ostream& oss, MyClass& obj);
    friend istream& operator >>(istream& iss, MyClass&obj);
    
    
    
public:
    
    void operator()(); //overload a function application
    int operator()(int& val){
       return val;
    };
    
    const MyClass operator -(const MyClass& rv); //operator overloadder defined as a member function of the class
    
    
    MyClass& operator ++(){
        return *this;
    };
    
    MyClass& operator ++(int){
        return *this;
    };
    
    
    //make a difference when used as l-value or r-value
    string& f(){
        cout << "l-value invocation" << endl;
        return this->name;
    }
    
    const string& f() const{
        cout << "r-value invocation" << endl;
        return this->name;
    }
};

istream& operator >>(istream& iss, MyClass&obj){
    iss >> obj.name;
    return iss;
}

ostream& operator <<(ostream& oss, MyClass& obj){
    oss << obj.name;
    return oss;
}

const MyClass operator +(const MyClass& lv, const MyClass& rv){
    MyClass obj;
    obj.name =  lv.name + rv.name;
    return obj;
}


void MyClass::operator()(){
    cout << "MyClass::operator()" << endl;
}

/**
 
  Many novice programmers mistakenly think they only have direct access to the private members of the calling object and do not realize that they have direct access to all objects of the class being defined.
 
 this function is a member function of the same class, it has access to all content of the passed in rv
 **/

MyClass::MyClass(const MyClass& obj)
{
    name = obj.name;
}

MyClass& MyClass::operator =(const MyClass& obj)
{
    if(this!=&obj){
        this->name = obj.name;
    }
    return *this;
}

const MyClass MyClass::operator -(const MyClass& rv)
{
    cout << rv.name << endl; 
    MyClass obj;
    obj.name = "unknonw";
    return obj;
}



void test(int a[], int size){
    for(int i=0;i<size;i++) a[i] = 0;
};


//REFERENCE Abosolute CPP 5th Ed.

const int MyClass::exp; //but still shall be defined 

int MyClass::age = 30;
void MyClass::class_func()
{
    MyClass::age += 1;
}


MyClass::MyClass() : name("dennycd") {
    cout << "MyClass::MyClass" << endl;
}

MyClass::~MyClass()
{
    cout << "MyClass::~MyClass" << endl;
}


//:: is scope resolution operator 
void MyClass::foo(const int& val) const{
    cout << "MyClass::foo" << endl;
    //this->name = "denny";
}

void MyClass::FOO(){
    
}


//If you want the object returned by a function to be an l-value, it must be returned by reference.
int& testtest(int& val){
    return val;
}

MyClass& tricky(){
    MyClass obj;
    return obj; //return a reference to a stack-memory associated local variables is dangers, as the value obtained by caller is an address somewhere in the stack
}

int test_function(int val){
    return 0;
}

typedef int(*MyFuncPtr)(int);
MyFuncPtr funcP = test_function;


void print_vertical(int val){
    if(val < 10)
        cout << val << endl;
    else{
        print_vertical( val/10);
        cout << val%10 << endl;
    }
}


class MyBase{
public:
    MyBase(const MyBase& mb){
        cout << "MyBase::MyBase(const MyBase&)" << endl;
    }
    
    MyBase& operator =(const MyBase& origin){
        cout << "MyBase::operator=(const MyBase&)" << endl;
        if(this!=&origin){
            
        }
        return *this;
    }
    
    MyBase(){ cout << "MyBase::MyBase()" << endl;}
    MyBase(int val){ cout << "MyBase::MyBase(val)" << endl;}
    virtual ~MyBase(){cout << "MyBase::~MyBase()" << endl;}
    void test(){ cout << "MyBase::test" << endl;}
    
    
    virtual void foo(){ cout << "MyBase::foo" << endl;}
    
    //pure virtual function makes this base class abstract, therefore cannot instantiate an object 
    //virtual void fus() = 0;
};

class MyOwnClass : public MyBase{
public:
    
    static void forall(){;}

    /**
     Overloaded assignment operators and constructors are not inherited.
     However, they can be used—and in almost all cases must be used—in the definitions of 
     overloaded assignment operators and copy constructors in derived classes.
     **/
    MyOwnClass(const MyOwnClass& obj) : MyBase(obj){
        cout << "MyOwnClass::MyOwnClass(const MyOwnClass&)" << endl;
    }
    MyOwnClass& operator=(const MyOwnClass& obj){
        cout << "MyOwnClass::operator=(const MyOwnClass&)" << endl;
        if(this!=&obj){
            MyBase::operator=(obj);
        }
        return *this;
    }
    
    MyOwnClass() : MyBase(1){ cout << "MyOwnClass::MyOwnClass()" << endl;}
    ~MyOwnClass(){ cout << "MyOwnClass::~MyOwnClass()" << endl;}
    void test(){
        cout << "MyOwnClass::test" << endl;
        MyBase::test();
        
        MyOwnClass::forall();
    }
    
    
    void foo(){ cout << "MyOwnClass::foo" << endl;}
    
};

/**
 Moreover, with protected and private inheritance, an object of the derived class cannot be used as 
 an argument that has the type of the base class. If Derived is derived from Base using protected or
 private (instead of public), then an object of type Derived is not an object of type Base;
 **/


/**
 However, separate compilation of template definitions and template function declarations is not yet implemented on most compilers, 
 so it is safest to place your template function definition in the file where you invoke the template function
 **/
template <typename T>
void test_temp_func(T& x) {
    cout << x << endl;
}

template <typename ElemType>
class MyTempClass {
    ElemType _elem;
    
public:
    void set(const ElemType& elem);
};

template <typename ElemType>
void MyTempClass<ElemType>::set(const ElemType& elem) {
    _elem = elem;
}


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
        cout << "operator ()(int val)" << endl;
        return 1;
    }
    
    //overload pointer operator
    const Data* operator ->(){
        cout << "operator ->()" << endl;
        return &self;
    }
    
    
    //somehow compiler allows to overload addressing operator...
    long operator &(){
        cout << "operator &()" << endl;
        return 0;
    }
    
    //dereferecing   *node
    string operator *(){
        cout << "operator *()" << endl;
        return "DennyCD";
    }
    
    //type casting   (int)node
    operator int(){
        cout << "operator int()" << endl;
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

//if throw list is defined, exactly thoese excpetions should be thrown, otherwise a runtime crash will occur !
void throw_func() throw (int,string, const char*)
{
    throw "dennycd"; //string("dennycd");
}
        


int main(int argc, char* arg[])
{

    
    try{
        throw_func();
    }
    catch(int val){
        
    }
    catch(string val){
        cout << "throwed string " << val << endl;
    }
    catch(...){
        cout << "throwed " << endl;;
    }
    
    {
        Node head;
        head(4);
        int x = (int)head;
    }
    
    {
        MyTempClass<int> obj1;
        obj1.set(4);
    }
    
    test_temp_func("X");
    
    {
        MyBase* p = new MyOwnClass();
    
        MyOwnClass* q = dynamic_cast<MyOwnClass*>(p);
        assert(q!=NULL);
    }
    
    {
        MyBase obj;
    
    }
    
    {
        MyBase* p = new MyOwnClass();
    
        //if virtual, this invokes the derived class's foo
        //if not virtual , this invokes whatever pointer's type class's foo
        p->foo();
    
    
        //if destructor not virtual, this only invokes base class deconstructor
        //if destructor virtual, this invokes the actual concrete class's destructor, then the base
        delete p;
    }
    
    
    MyOwnClass obj;
    obj.test();
    
    
    MyOwnClass obj2 = obj;
    
    obj = obj2;
    
    print_vertical(12335);
    
    (*funcP)(1);
    
    typedef int*  IntPtr;
    
    
    //allocate 10 ints in heap
    int* var = new int[10]; //new int(10);
    delete [] var;
    
    //allocate one int on heap, initialize its value to be int !!
    int* var2 = new int(10);
    delete var2;
    
    //a C-string variable
    const char* str = "dennycd";
    cout << "size " << sizeof(str) << endl;
    assert(sizeof(str)==8); 
    
    //a character array variables - also a C-string variable
    char str1[11];
    cout << "sizeof str1 " << sizeof(str1) << endl;
    assert(sizeof(str1)==11); //str1 is recognized (statically declared) as an array of 11 elements
    
    char str2[] = "dennycd";  //will assign # of chars plus 1 ending null char
    cout << "sizeof str2 " << sizeof(str2) << endl;
    assert(sizeof(str2)==8); 
    
    //array initialiation - not a c-string
    char str3[] = {'a','b','c'};
    
    //with a specified size, sizeof will give the decalred size
    char str4[10] = "dennycd";
    cout << "size " << sizeof(str4) << endl;
    assert(sizeof(str4)==10);
    
    
    {
        MyClass obj;
    
        obj.f() = "dennychendai";
        string name = obj.f();
    }
    
    {
        int var = 1;
        testtest(var) = 2; //now it changes var
        assert(var==2);
    }
    
    {
        int x = 1;
        int& y = x; //a reference is a the name of a mem location, an alias of a mem address
    
        assert(&y == &x);
    
        int *z = &x; //pointer itself is a new variable with its own mem address, it's value is  the address of another variable
    
    }
    
    {
        MyClass obj1 = 5;
        MyClass obj2 = obj1 + 9;
    }
    
    {
        MyClass obj;
    
        obj();
    }
    
    {
        MyClass obj1, obj2;
    
        //not allowed as the returned is a const object
        //(obj1+obj2).good();
    
    
        MyClass obj3 = obj1 + obj2;
        obj3.good(); // obj3 is a new object copied from the anonymous object produced by the + operation
    
    }
    
    {
        MyClass obj1, obj2;
    
        MyClass obj3 = obj1 + obj2;
        MyClass obj4 = obj1 - obj2;
    
        //cin >> obj1 >> obj2 >> obj3 >> obj4;
        cout << obj1 << obj2 << obj3 << obj4 << endl;
    }
    
    {
        int val = 1;
    
        // int is a const, meanign the value it points to shall be be modified
        const int* p = &val;
        p = NULL; //but the pointer value itself is modifierabl
        //this will give compile error
        //*p = 0;
    
        // int* now is const, pointer value shall not be modified, but can modified the value it  points to
        int* const q = &val;
    
        *q = 0; //ok
    
        //now this is not allowed
        //q = NULL;
    
    
        
    }
    
    
    {
        MyClass obj;
    
        int var = 1;
        obj.foo(var);
    
    
        //this is considered a function declaration, not a object declaration
        MyClass function();
        function();
    
    
        //explicit constructor call
        MyClass obj2 = MyClass();  //Calling the constructor creates an anonymous object with new values, and then use it to initialize obj2
    
    }


    //some array operation
    {
        int a[] = {1,2,3,4};
        test(a,4);
        assert(a[0]==0);
    }


    {
    
        //Structures are normally used with all member variables public and with no member functions.
        typedef struct {
            int id;
        }MyStructType;

        //MyStructType mst = { 2 };


    }

    {
        int var[] = {1,2,3};
        int* pvar = var;
        cout << "total of a staticially allocated array is " << sizeof(var) << endl;
        cout << "size of an array pointer is " << sizeof(pvar) << endl;
        assert(sizeof(var)==3*sizeof(int));
        
        
        int *dvar = new int[3];
        cout << "size of a dynamically allocated array size is " << sizeof(dvar) << endl;
        assert(sizeof(dvar)==sizeof(int*));
        
    }
    

    {
        int var = 1;
        cout << "declared var addr = " << &var << endl;
        test1(var);
    }

    //four types of casting
    /**
    static_cast<Type>(Expression) 
    const_cast<Type>(Expression) 
    dynamic_cast<Type>(Expression) 
    reinterpret_cast<Type>(Expression)
    **/



    //integer division discards the part after the decimal point.
    {
        assert(5/2 == 2); 
    }

    //exponents
    {
        cout.setf(ios::fixed);
        cout.setf(ios::showpoint);
        cout.precision(5);
    
        float x = 5.78e6;
        cout << "x is " << x << endl;
    }

    {
        cout << "short size "<< sizeof(short) << endl;
        cout << "int size "<< sizeof(int) << endl;
        cout << "long size "<< sizeof(long) << endl;
        cout << "long long size "<< sizeof(long long) << endl;
        cout << "float size " << sizeof(float) << endl;
        cout << "double size " << sizeof(double) << endl;
        cout << "long double size " << sizeof(long double) << endl;
    }

    {
        //short-circuit evaluation
        int x = -1, y = 1;
        bool result = ( x > 0 ) && ( ++y < 0 );
        assert(result==false);
        assert(y==1);
    }
   
    //pointer variable
    int* p = NULL;
    cout << "size of pointer is " << sizeof(p) << endl;  //64bit pointer 

    //enum
    MY_TYPE mt = TYPE1;
    assert(mt == TYPE1);


    //the assignment statement, when used as an expression, returns the new value of the variable on the left side of the assignment operator.
    int y;
    int x = ( y = 12);    
    assert(x == 12);


    //The comma operator is a way of evaluating a list of expressions and returning the value of the last expression.
    {
        int first, second, third;
        int result = (first = 2, second = first + 1, third = second + 1);
        assert(result == 4);
    }
}



MyClass function(){
    cout << "invoking function" << endl;
    return MyClass();
}