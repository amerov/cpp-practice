//
//  main.cpp
//  dapsPractice
//
//  Created by Denny C. Dai on 10-09-15.
//  -
//
//
//
//  Data Abstraction and Problem Solving with C++ 
//  Practice Project 

#include <iostream>
#include <unistd.h>  // getcwd
#include <cstdlib> //for rand()
#include <time.h> //for time()

#include "Stack.hpp"
#include "AList.hpp"
#include "LList.hpp"
#include "CDLList.hpp"
#include "Queue.hpp"
#include "CAQueue.hpp"
#include "Sorts.hpp"
#include "BinaryTreeL.hpp"
#include "BinaryTreeA.hpp"

#include <cstring> //for strcmp
#include <fstream>

#include "TreeSort.hpp"

#include "ALList.hpp"

#include "Table.hpp"
#include "SetASorted.hpp"

#include "Heap.hpp"
#include "QueuePriority.hpp"

#include "HeapSort.hpp"

#include "Graph.hpp"

#include "TwoThreeTree.hpp"

using namespace std;
using namespace astemsoft::adt;
using namespace astemsoft::algs;
using namespace astemsoft;

/////////////////////////////////////////////
class Person
{
public:
    enum Type{
        Man = 1,
        Women = 2
    };
    
    
    //a "collector" function object
    //that gathers all Persons object belonging to the same type
    //used interoperatively with a data structure that allows 
    //traversing and external handler
    struct PersonGenderFO
    {
    public:
        PersonGenderFO(Type t) : type(t){}
        
        void operator()(const Person& p)
        {
            if(p.symbol == type)
                cout << "extracting person " << p << endl; 
        }
    private:
        Type type;
    };
    
public:
    Person()
    {
        ID = -1;
    }
    
    Person(int nID)
    {
        ID = nID;
    }
    
    Person(int nID, Type x)
    {
        ID = nID;
        symbol = x;
    }
    
    //copy constructor
    Person& operator=(const Person& p)
    {
        if(this!=&p)
        {
            ID = p.ID;
            symbol = p.symbol;
        }
        return *this;
    }
    
    //comparison with Person
    bool operator ==(const Person& p)
    {
        return ID == p.ID;
    }
    
    //equality key comparison
    bool operator ==(int nID)
    {
        return ID == nID;
    }

    //larger key comparison
    bool operator >(int nID)
    {
        return ID > nID;
    }

    //smaller key comparison
    bool operator <(int nID)
    {
        return  ID < nID;
    }
    
    //IMPORTANT: this allows < > comparison using primary key with Object itself
    //key type casting operator
    operator int () const
    {
        return ID;
    }
    
    //output stream operator
    friend ostream& operator <<(ostream& oss, const Person& p); //enable print
    friend ifstream& operator >>(ifstream& iss, Person& p); 
    
private:
    int ID; //used as primary key
    Type symbol; 
    //other infos
};
ostream& operator <<(ostream& oss, const Person& p)
{
    oss << "ID = " << p.ID << " Type = " << (p.symbol==Person::Man ? "Man":"Woman") ;
    return oss;
}
ifstream& operator >>(ifstream& iss, Person& p)
{
    iss >> p.ID;
    return iss;
}



////////////////////////////////////////////

template<class T>
struct test
{
public:
    test(){}
    test(List<T>* pl) : plist(pl){}
    
    void operator()(const T& item)
    {
        plist->insert(plist->size(),item);
    }
    
private:
    List<T>* plist;
};


template<class T>
struct printer
{
public:
    printer(){}
    
    void operator()(const T& item)
    {
        cout << item << endl;
    }
    
};
/////////////////////////////////////////


int main (int argc, const char * argv[]) {

  
    /*
    try{
    AList<int> alist;
    alist.insert(4, 12);
    }
    catch(ListException e)
    {
        cout << e.what() << endl;
    }
    
    cout << "hello world" << endl;
    */
    //srand(time(NULL));
    
    try{
        
        TwoThreeTree<int,int> ttt;
        
        for(int i=0;i<10;i++)
        {
            ttt.insert(rand());
            //ttt.print();
        }

        ttt.print();
        //TwoThreeTree<int,int> tree = ttt;
        //ttt.print();
        
        //ttt.remove(7);
       // ttt.print();
        /*
        
        for(int i=0;i<10;i++)
        {
            ttt.remove(i);
            ttt.print();
        }
        */
        
         /*
         Table<BinaryTreeL<Person>, Person, int> table;
         //Table<BinaryTreeA<Person>, Person, int> table;
         //Table<SetASorted<Person>, Person, int> table;
         
         table.insert(Person(3,Person::Man));
         table.insert(Person(1,Person::Women));
         table.insert(Person(7,Person::Man));
         table.insert(Person(2,Person::Women));
         
         table.print();
         
         
         Person item;
         table.retrieve(7, item);
         cout << "retrieved item is " << item << endl;
         
         
         table.remove(7);
         table.print();
         
         
         Table<BinaryTreeL<Person>, Person, int> newtable = table;
         //Table<BinaryTreeA<Person>, Person, int> newtable = table;
         //Table<SetASorted<Person>, Person, int> newtable = table;
         newtable.print();
         
         
         cout << "output from table traversal: " << endl;
         //printer<Person> pt;
         Person::PersonGenderFO gf(Person::Man);
         
         table.traverse(gf);
         
         //Table<int,int>* t = NULL;
         
         

        */
        /*
        Graph<char, char, int> graph;
        
        for(int i='a';i <= 'i';i++)
            graph.insertV(i);
        
        
        graph.insertE('a', 'b', 1);
        
        
        graph.insertE('a', 'f', 1);
        graph.insertE('a', 'i', 1);
        
        
        graph.insertE('b', 'c', 1);
        graph.insertE('b', 'e', 1);
        
        graph.insertE('e', 'g', 1);
        graph.insertE('f', 'g', 1);
        
        graph.insertE('e', 'c', 1);
        
        graph.insertE('g', 'd', 1);
        graph.insertE('c', 'd', 1);
        graph.insertE('d', 'h', 1);
        
        
        graph.print();
        
        
        
        bool found = graph.local_search('e', 'h');
        
        cout << "there " << (found ? "exists" : "doesn't exist") << " a path from e to h" << endl;
        
         */
        
        /*
        //the graph's vertice payload is Person, with int key
        //the graph's edge has string as payload type
        Graph<Person, int, std::string> graph;
    

        
        graph.insertV(Person(3,Person::Man));
        graph.insertV(Person(1,Person::Man));
        graph.insertV(Person(2,Person::Women));
        
        cout << "the inserted vertex " <<  (graph.existV(3) ? "exist" : "not exist") << endl;
        
        Person item;
        graph.retrieveV(3, item);
        cout << "retrieve item is " << item << endl;
         
        graph.removeV(3);

        cout << "total vertices in graph: " << graph.vertices() << endl;
        cout << "total edges in graph: " << graph.edges() << endl;
        
        
        
        graph.insertE(1, 2, "From 1st man to 2nd woman!");
        
        
        cout << "printing the graph content here " << endl;
        graph.print();
        
        bool x = graph.existE(1, 2);
        cout << "the inserted edge " <<  (x ? "exist" : "not exist") << endl;
        
        std::string edge;
        graph.retrieveE(1, 2, edge);
        cout << "retrieved edge: " << edge << endl;
        cout << "total edges in graph: " << graph.edges() << endl;
        
        graph.removeE(1, 2);
        
        cout << "total vertices in graph: " << graph.vertices() << endl;
        cout << "total edges in graph: " << graph.edges() << endl;
        
         */
        /*
        int size = 10;
        int * arr = new int[size];
        for(int i=0;i<size;i++)
            arr[i] = i;
        

        heapsort(arr, size); 
        
        cout << " after heapsort: " << endl;
        for(int i=0;i<size;i++)
            cout << arr[i] << endl;
         
         */
        
        /*
        QueuePriority<int> qp;
        
        for(int i=0;i<10;i++)
            qp.enqueue(rand());
        
        qp.print();
        
        
        cout << "after deqeue " << endl;
        int item;
        while(!qp.empty())
        {
            qp.front(item);
            qp.dequeue();
            cout << item << endl;
        }
            */
        /*
        Heap<int> hp;
        
        for(int i=0;i<10;i++){
            hp.insert(i);
            hp.print();
        }
         
         */
        
 //       hp.print();
    
                
        /*
        
        SetASorted<Person> list;
        
        for(int i=0;i<9;i++)
            list.insert<int>(Person(i));
        
        list.print();
        
    
        SetASorted<Person> newlist = list;
        newlist.print();
        */
        
        /*
        BinaryTreeL<Person> bt;
        
        bt.insert(Person(4,Person::Man));
        bt.insert(Person(2,Person::Women));
        bt.insert(Person(1,Person::Man));
        bt.insert(Person(3,Person::Women));
        bt.insert(Person(7,Person::Man));
        bt.insert(Person(5,Person::Women));
        bt.insert(Person(6,Person::Man));
        bt.insert(Person(8,Person::Women));
        
        Person::PersonGenderFO gf(Person::Man);
        
        bt.traverse(BinaryTreeL<Person>::INORDER, gf);
        
         */
        
        /*
         
        BinaryTreeA<int> tree;
        
        
        tree.insert(4);
        tree.insert(2);
        tree.insert(1);
        tree.insert(3);
        tree.insert(7);
        tree.insert(5);
        tree.insert(6);
        tree.insert(8);
        
        tree.print();
        
        
        tree.remove(4);
        tree.print();
         
         */
        
        /*
        ALList<int> all;
        
        for(int i=0;i<10;i++)
            all.insert(all.size(), i);
        
        //all.print();
        
        int tmp;
        
        for(int i=0;i<10;i++)
        {    
            all.retrieve(i,tmp);
            cout << tmp << endl;
        }
        
                
        
        
        cout << "removing first" << endl;
        all.remove(0);
        all.print();
        
        cout << "removing last" << endl;
        all.remove(all.size()-1);
        all.print();
        

        cout << "removing mid" << endl;
        all.remove(4);
        all.print();
        

        ALList<int> newlist = all;
        newlist.print();
         */
        /*
         
        
        
        List<int>* ll = new AList<int>();
        for(int i=0;i<10;i++)
            ll->insert(0, rand());
        
        cout << "unsorted form: " << endl;
        ll->print();
        

        //BinaryTreeL<int> bt;
        BinaryTreeA<int> bt;
        
        
        treesort(ll, bt); //function template will determine the spec automaticaly
        
        //treesort<int, BinaryTreeA<int> >(ll, bt);
        //treesort<int,BinaryTreeL<int> >(ll, bt);
        
        cout << "tree sorted verion: " << endl;
        ll->print();
         
        */
        
        //BinaryTreeA<int> bt;
        
        /*
        BinaryTreeL<Person> bt;

        //for(int i=0;i<100;i++)
         //   bt.insert(Person(rand()));
        
        bt.insert(Person(4));
        bt.insert(Person(2));
        bt.insert(Person(1));
        bt.insert(Person(3));
        bt.insert(Person(7));
        bt.insert(Person(5));
        bt.insert(Person(6));
        bt.insert(Person(8));
        
        
        bt.print();
        
        Person item;
        bt.retrieve(7, item);
        
        cout << "Person is " << item << endl;
        
        
        bt.remove(6);
        bt.print();
         
         */
        /*
        bt.save("test.dat");
        
        cout << "reloading the data " << endl;
        BinaryTreeL<Person> newbt;
        newbt.restore("test.dat");
        newbt.print();
        
       
        cout << "tree height is " << newbt.height() << endl;
        */
        
        //bt.remove(4);
        //bt.print();
        // bt.print();
        
        //AList<int> list;
        //CDLList<int> list;
        
         
        
        /*
        for(int i=0;i<10;i++)
            list.insert(0, i);        
        list.print();
        */
        
        //quick_sort<CDLList<int>::iterator, int>(list.begin(), list.last());
        //quick_sort<AList<int>::iterator, int>(list.begin(), list.last());
        
        //apply a sorting algorithm that alters the internal structure 
        //of the ADT List via ADT's random access iterator !!!
        //selection_sort< CDLList<int>::iterator, int>(list.begin(), list.last());

        //bubble_sort<CDLList<int>::iterator,int>(list.begin(),list.last());
        //bubble_sort<AList<int>::iterator,int>(list.begin(),list.last());
        
        //insertion_sort< CDLList<int>::iterator, int>(list.begin(), list.last());
        //insertion_sort< AList<int>::iterator, int>(list.begin(), list.last());
        
        //merge_sort<CDLList<int>::iterator, int>(list.begin(), list.last());
        //merge_sort<AList<int>::iterator, int>(list.begin(), list.last());
        
        //cout << "after sort:" << endl;
        //list.print();
        
        
        /*
                AList<int>::iterator me;
 
        for(me = list.begin(); me!=list.end(); ++me){
            cout << "item: " << *me << endl;
        }
        
        
        list.print();
        */
        
        /*
        CAQueue<int> queue;
        queue.printAll();

        for(int i=0; i<10; i++)
        {
        queue.enqueue(rand());
        queue.printAll();
        }
        
        
        for(int i=0; i<9; i++)
        {
            queue.dequeue();
            queue.printAll();
        }
        
        
        for(int i=0; i < 50; i++)
        {
        queue.enqueue(i);
        queue.printAll();
        }
        
        
        queue.print();
        
        
        CAQueue<int> newqueue = queue;
        newqueue.printAll();
        
        
        queue.save("test.dat");
        newqueue.restore("test.dat");
        newqueue.printAll();
        */
         /*
        Queue<int > queue;
        
        queue.enqueue(rand());
        queue.print();

        queue.dequeue();
        queue.print();
        
        queue.enqueue(rand());
        queue.print();

        queue.enqueue(rand());        
        queue.print();
        
        
        int item;
        queue.front(item);
        cout << "fron item is " << item << endl;
    
         */
        /*
        Stack<int> stk;
        
        stk.push(rand());
        stk.push(rand());
        stk.push(rand());
        
        stk.print();
        
        cout << "in copied stack" << endl;
        Stack<int> newstk = stk;
        newstk.print();
        
        
        int item;
        stk.top(item); 
        cout << "top is " << item << endl;
        stk.pop();
        
        stk.top(item); 
        cout << "top is " << item << endl;
        stk.pop();
        
        stk.top(item); 
        cout << "top is " << item << endl;
        stk.pop();
        */
        
        /*
        List<int>* list = new CDLList<int>;


        list->insert(0, rand());
        list->insert(1, rand());
        list->insert(1, rand());
        list->insert(2, rand());
        list->insert(1, rand());
        
        list->save("test.dat");
        
        CDLList<int> newlist; 
        newlist.restore("test.dat");
        newlist.print();
        
        
        cout << endl;
        list->remove(0);
        list->print();
        
         cout << endl;
        list->remove(list->size()-1);
        list->print();
        
         cout << endl;
        list->remove(1);
        list->print();
        
         cout << endl;
        list->remove(0);
        list->print();
        
         cout << endl;
        list->remove(0);
        list->print();
        
        CDLList<int> mylist = newlist;
        mylist.print();
        
        
        
        
        
        delete list; list = NULL;

        */
        /*
        AList<int> alist;

        
        for(int i=0;i < 10; i++)
        {
            alist.insert(0, rand());
        }
        
        alist.print();
         
        
        alist.save("test.dat");
        
        AList<int> newlist;
        newlist.restore("test.dat");
        
        alist.print();
        */
        /*
        alist.insert(0, rand());
        alist.print();
        
        alist.insert(0, rand());
        alist.print();

        
        alist.insert(1, rand());
        alist.print();

        alist.insert(3, rand());
        alist.print();

        
 
        alist.remove(0);
        alist.print();
        
        alist.remove(alist.size()-1);
        alist.print();
        
        alist.remove(2);
        alist.print();
         */
        
        /*
        LList<int> list;
        list.insertAscendRecursive(2);
        list.print();
        
        list.insertAscendRecursive(9);
        list.print();
        
        list.insertAscendRecursive(8);
        list.print();
        
        
        list.insertAscendRecursive(9);
        list.print();
        
        list.insertAscendRecursive(1);
        list.print();
        
        list.insertAscendRecursive(9);
        list.print();
        
        list.insertAscendRecursive(1);
        list.print();
        */
        
        /*
        list.remove(6);
        list.print();
        
        list.remove(0);
        list.print();
        
        list.remove(2);
        list.print();

        list.remove(0);
        list.print();

        list.remove(0);
        list.print();

        list.remove(0);
        list.print();


        list.remove(0);
        list.print();

        list.remove(0);
        list.print();
        
        list.remove(0);
        list.print();
         */
        
        /*
        char* path = NULL;
        size_t size;
        path = getcwd(path, size);
        cout << "Current working directory is " << path << endl;
        
        list.save("test.dat");
        
        LList<int> newlist;
        newlist.restore("test.dat");
        cout << "new list loaded from file : " << endl;
        newlist.print();
        */
    }
    catch(GraphException e)
    {
        cout << e.what() << endl;
    }
    catch(SetException e)
    {
        cout << e.what() << endl;
    }
    
    catch(ListException e)
    {
        cout << e.what() << endl;
    }
    /*
    catch(LListOutOfRangeException e)
    {
        cout << e.what() << endl;
    }
    */
    
    
    return 0;
}

