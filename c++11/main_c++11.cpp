//
//  main.cpp
//  dapsPractice
//
//  Created by Denny C. Dai on 2012-08-27.
//  Copyright (c) 2012 Denny C. Dai. All rights reserved.
//


#include <iostream>
#include <vector>
#include <functional> //lambda function support
#include <new>
#include <thread>
#include <regex>

#include <random>
#include <utility>
#include <type_traits>

using namespace std;


class TestClass{
public:

    //initializer list constructor
    TestClass(std::initializer_list<int> list)
    {
    
    }

    TestClass(){
        cout << "TestClass()" << endl;
    }
    TestClass(const TestClass& tc){
        cout << "TestClass(tc)" << endl;
    }
    
    TestClass& operator =(const TestClass& tc){
        cout << "TestClass operator =" << endl;
        return *this;
    }
};

TestClass test_func(){
    TestClass obj;
    cout << "returning obj " << &obj << endl;
    return obj;
}


void test_init_list_func(std::initializer_list<int> list){

}


constexpr int get_five(){ return 5;} //gurantee that a this function is a compile time constant
void test_constant_expression()
{
 //   int arr[ get_five() + 1 ];
    
}

constexpr double earth = 9.8;
constexpr double moon = earth / 6.0; //allow a constant variable to use in another constant variable


//uniform initialization , just like aggregate-initialization
struct BasicStruct{
    int x;
    double y;
};
BasicStruct var1({5,3.2f});

//if get ride of private and constructor, will be same as above
struct AltStruct{
    AltStruct(int x, double y) : x_(x), y_(y) { cout << "calling on AltStruct()" << endl; }
private:
    int x_;
    double y_;
};
AltStruct var2{5,3.2f};


struct IdString{
    string name;
    int id;
};

IdString get_string(){
    return {"dennycd", 19};
}


//struct with functor member variable
struct MyStruct{
    auto functor(int x, int y) -> int {
        return x + y;
    }
};


//constructor delegation - call peer constructor
// C++11 consider an object is constructed once any constructor finishes exe
class TestDelegation{
public:
    int number;
    
    TestDelegation(int n) : number(n) {}
    TestDelegation() : TestDelegation(42) {}
    
    
};


class BaseClass{
public:

    //explicit -  prevent single-argument constructor from being used as implicit type conversion operator !!!!
    explicit BaseClass(int v) : value(v) {}
    BaseClass(){}
    
    
    //explicit conversion operator
    explicit operator bool(){
        cout << "explicit type casting" << endl;
        return true;
    }
    
    virtual void print(){ cout << "value=" << value << endl;}
    
    virtual void final_func() final {}
private:
    int value = 5;
};


//declare final to prevent further inheritance 
class DerivedClass final : public BaseClass{
public:
    //using BaseClass::BaseClass; //inherit from base class constructor
    
    //impose virtual function override 
    void print() override {
        cout << "derived value = " << endl;
    }
    
    
    //void final_func(){;}
};

//class FurtherDerivedClass : public DerivedClass{
//};


//enum version 2.0 !!

//forward declaration
enum class MyEnum : char;
void test_enum(MyEnum me){}

//define enum value type
enum class MyEnum : char{
    APPLE = 'a',
    PEA = 'b',
    COCO = 'c'
};


void foo(char* ptr){ cout << "foo char" << endl;}
void foo(int p){ cout << "foo int" << endl;}


//alias template
template<typename A, typename B, int C>
class TClass{
    A a;
    B b;
};

template<typename B>
using PartialTClass = TClass<string, B, 5>;


PartialTClass<float> xyz;  // TClass<string, float, 5>


typedef void (*MyType)(double);  //function type alias
using MyNewType = void (*)(double); //function type alias via using


//unrestrictd unions
struct Point{
    Point(){}
    Point(int x, int y) : x_(x), y_(y) {}
    int x_,y_;
};

union U{
    int z;
    double w;
    Point p;
    
    //due to Point, a union constructor is required
    U(){
        new(&p) Point();  //
    }
};


//variadic templates
template<typename... Values>
class MyTuple{  //a tuple that contains a variant number of element types
    
};
MyTuple<int, vector<string>> t;

//tuple from std
typedef std::tuple<int,double,long&, const char*> test_tuple;
long length = 12;
test_tuple proof(18, 6.5, length, "Ciao");


const char* xx = "Ciao";

//variadic templates applying to functions
template<typename... Params>
void my_printf(const string& format, Params... parameters)  //so ... operator, while occur left of a function parameter name, it declares a variadic parameter pack !!!
{
    printf(format.c_str(), parameters...);   //while appear after a function call's parameter, it unpacks the parameter pack into separate arguments
}


//explicit default and deleted member functions
class ControlClass{
public:
    ControlClass() = default;   //can only say it is defaulted, but cannot put it in default while also definiting it !!
    
    ControlClass(const ControlClass&) = delete; //prevent copy constructor call
    ControlClass& operator=(const ControlClass&) = delete; //prevent copy operator call
    
    
    
    void f(double i){}
    template<typename T> void f(T) = delete; // disallow calling with any other type , other than what's explicitly defined !!!
    void f(int i) = delete; //prevent the call so there's no silient convertion from int to double and then invoked f(double)
};


//assertion at compilation time
template<typename T>
struct Check{
    static_assert(sizeof(int) <= sizeof(T), "T is not big enough!");  //assert at preprocessing time
};


template<typename T>
T foo(T x, T y){
    static_assert(std::is_integral<T>::value, "foo() must take in integral type"); //asert at template instantiation (compiling time), not actual function call time !!
    return x+y;
}


void func(int& r) { r++; }
template<typename F, typename P> void g(F f, P t) { f(t); }


//type traits
template<int B, int N>
struct Pow{
    //recursive call and recombination
    enum { value = B * Pow<B, N-1>::value };
};

template<int B>
struct Pow<B,0>{
    // N = 0 condition of termination
    enum{ value = 1 };
};

int quartic_of_three = Pow<3, 4>::value;


//type traits
template<bool B>
struct Algorithm {
    template<typename T1, typename T2> static int do_it (T1&, T2&){}
};

template<>
struct Algorithm<true>{
    template<typename T1, typename T2> static int do_it (T1, T2){}
};

template<typename T1, typename T2>
int elaborate(T1 A, T2 B)
{
    //type traits to identify the category of an object and all the characteristics of a class or struct
    constexpr bool isIntegral = std::is_integral<T1>::value;
    constexpr bool isFloatingPoint = std::is_floating_point<T2>::value;
    return Algorithm< (isIntegral && isFloatingPoint) >::do_it(A,B);
}

bool adjacent(long x, long y){return true;} //function declaration

void cplusplus11Test();
int main(int argc, char* argv[])
{
    cplusplus11Test();
    
    
    
    
    
    
    //wrapper reference
    int i = 0;
    g(func, i); //i will not get modified since i is instantiated by the template
    cout << "i=" << i << endl;
    
    g(func, std::ref(i));  //a reference wrapper to i is instantiated, , i is modifiable
    cout << "i=" << i << endl;
    
    
    //function wrapper using template
    std::function<int (int, int)> func;
    
    std::plus<int> add; // plus is  template<typename T> T plus(T,T);
    
    func = add; //
    
    std::function<bool (short, short)> func2;
    if(!func2)
    {
        
        func2 = &adjacent;
        
        //function objects
        struct Test{
            bool operator()(short x, short y){ return true;}
        };
        
        Test car;
        func = std::ref(car); // creates a function wrapper referece from  car()
    }
    
    
    
    //pseudorandom
    std::uniform_int_distribution<int> distribution(0,99);
    std::mt19937 engine; //Mersenne twister
    auto generator = std::bind(distribution, engine);
    int random = generator(); //generate a uniform integral variate between 0 and 99
    int random2 = distribution(engine); //another sample directly using the distrubtion and he engine
    
    
    //regular expression
    const char* reg_esp = "[ ,.\\t\\n;:]";
    std::regex rgx(reg_esp);   // std::basic_regex<char>
    std::cmatch match;   //std::match_results<char>
    
    const char* target = "Unseen University - Ahkh-Morpork";

    //identify all words separated by characters of rgx
    if( std::regex_search(target, match, rgx)){
        const size_t n = match.size();
        for(size_t a = 0; a < n; a++){
            string str(match[a].first, match[a].second);
            cout << "match word " << str << endl;
        }
    }

    //template <class _Fp, class ..._Args, class>
    //thread::thread(_Fp&& __f, _Args&&... __args)
    
    
    auto runner = []()->int{
        cout << "running.." << endl;
        return 0;
    };
    
//    thread task(runner,5,4);
//    task.detach();
    
    ControlClass obj, obj2;

    foo(3, 4);
    foo('a', 'b');

//    foo(obj, obj2); //will fail at compile time 
    

    
//    obj.f('a');
//    obj = obj2;
    
    long long int longVar = 3;
    cout << "size of long long int is " << sizeof(longVar) << endl; //at least 64 bit !!
    
    //user defined literals
    
    
    
    //unicode string literna
    const char utf8str[] = u8"I'm a UTF-8 string. [\u2018] ";
    const char16_t utf16str[] = u"I'm a UTF-16 string. [\2018] ";
    const char32_t utf32str[] = U"I'm a UTF-32 string. [\2018] ";


    const char rawstr[] = R"(  raw string with" " ' '  no escaping \ stuff )";
    const char rawstr2[] = R"mydelimiter(  raw string with" " ' '  no escaping \ stuff )mydelimiter";


    
    //null pointer constant
    char *pc = nullptr;
    int *pi = nullptr;
    
    foo(pc);  //always resolve to foo(char*) even if pc is null 
    
    
    BaseClass x, y(6);
    x.print();
    y.print();
    
    //if requires a boolean, therefore attempts to invoke a explicit type conversion 
    if(x)
        cout << "Hell YEa!" << endl;
    
    //invoking initializer list constructor
    TestClass myobj = {1,2,3,4,5};
    vector<int> vec{1,2,3,4,5,6};
    
    //function param as initialize list
    test_init_list_func({1,2,3,4,5});
    
    
    //type inference
    auto my_var = 9;
    
    //query the type of expression, and then use the type to declare another !!!
    decltype(my_var) my_var2 = 5;
    cout << my_var2 << endl;
    
    for(auto itr = vec.cbegin(); itr != vec.cend(); itr++)
        cout << *itr << endl;
        
    //range-based for loop
    int myarr[] = {1,2,3,4,5};
    for(int &x : myarr){
        x *= 2;
    }
    
    for(int& x : vec)
        cout << x << endl;
        
    //the closure for the lambda
    int var_x = 13;
    string var_str = "dennycd";
        
    //functor on stack
    //lambda functions (a.k.a. anonymous functions)
    function<double(int,int)> functor = [var_x, &var_str](int x, int y) -> double {
        return (double)(x+y);
    };
    
    auto functor2 = functor;
    
    double result = functor(2,3);
    cout << "functor result: " << result << endl;
    
    
    //functor on heap
    auto heapFunctor = new auto([=](int x){ ;});
    delete heapFunctor;
    

    
}


void cplusplus11Test()
{
#ifdef __cplusplus
    long x = __cplusplus;
    if(x > 199711L)
        cout << "<-- under C++ 11 mode with __cplusplus equals " << x <<  " -->" << endl;
#endif

    if(__has_feature(cxx_variadic_templates))
        cout << "variadic template supported" << endl;
}




