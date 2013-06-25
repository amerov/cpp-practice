## cpp-practice
My practice library of common data structure and algorithms implemented in C++. 

### Data Structures 
The library covers the following data structures with several variations

* [Linked List](https://en.wikipedia.org/wiki/Linked_list) 
    * `alist.hpp` heap-allocated dynamic array with geometric size expansion
    * `llist.hpp` pointer-based non-circular singly link list
    * `allist.hpp` pointer-based acyclic singly link list

* [Stack](https://en.wikipedia.org/wiki/Stack_(abstract_data_type)
	* `stack.hpp` templated with optional containers (alist, llist, allist)
	* `astack.hpp` static array based implementation with max size cap
	* `lstack.hpp` pointer-based stack implementation with dynamic size

* [Queue](https://en.wikipedia.org/wiki/Queue_(abstract_data_type)
    * `queue.hpp` templated with optioanl containers (alist, llist, allist)
    * `aqueue.hpp` circular array based implementation with max size cap
    * `lqueue.hpp` pointer-based with acylic links using tail pointer
    
* [Binary Search Tree](https://en.wikipedia.org/wiki/Binary_search_tree)
    * `a_binary_tree.hpp` array based binary tree implementation using free list
    * `p_binary_tree.hpp`  pointer-based implementation

* [Heap](https://en.wikipedia.org/wiki/Heap_(data_structure) (Priority Queue)
    * `heap.hpp` an array-based binary search tree implementation of heap
    
* [Balanced Search Tree](https://en.wikipedia.org/wiki/Self-balancing_binary_search_tree)
    * `two_three_tree.hpp`  A balanced search tree with nodes having either 2 or 3 childs and all leaf nodes residing at the same level

* [Hash Table](https://en.wikipedia.org/wiki/Hash_table)
    * `hash_map.hpp` A bucket-based hash map implementation using std::map as the separation chain and std::vector as the bucket array. template support arbitrary hash function definition

* [Graph](https://en.wikipedia.org/wiki/Graph_(abstract_data_type)
    * `lgraph.hpp`  An adjacent list implementation of directed ADT graph



All data structures are templated with arbitrary data element type. 

### Algorithms 

Sorting algorithms with their header file name self-explanatory

* Selection Sort `selection_sort.hpp`
* Bubble Sort `bubble_sort.hpp`
* Insertion Sort  `insertion_sort.hpp`
* Merge Sort `merge_sort.hpp`
* Quick Sort `quick_sort.hpp`
* Radix Sort `radix_sort.hpp`
* Tree Sort `tree_sort.hpp`
* Heap Sort `heap_sort.hpp`

All algorithms are C++ template functions to allow arbitrary data types and container type.

### Testing 
The library uses 

* [Google C++ Testing Framework](https://code.google.com/p/googletest/)

test code located in test folder. For details of the runtime and space complexity, either refer to the code comment or check out the [BigO Cheet Sheet](http://bigocheatsheet.com/)  

### Install
The library is header file only.

### Reference 
Loosely follows the book 

* [Data Abstraction and Problem Solving with C++](http://www.pearsonhighered.com/educator/product/Data-Abstraction-Problem-Solving-with-C-Walls-and-Mirrors-6E/9780132923729.page) by Frank M. Carrano

## Author 
Denny C. Dai <dennycd@me.com> or visit <http://dennycd.me>

## License 
[MIT License](http://opensource.org/licenses/MIT) 