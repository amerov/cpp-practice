//
//  TwoThreeTree.hpp
//  dapsPractice
//
//  Created by Denny C. Dai on 10-10-03.
//
#ifndef ASTEMSOFT_ADT_TWO_THREE_TREE_HPP
#define ASTEMSOFT_ADT_TWO_THREE_TREE_HPP

#include "Set.hpp"
#include <cassert>
#include <iostream>
#include <string>
#include <sstream>

namespace astemsoft
{
    namespace adt
    {
        template<typename Item, typename Key>
        class TwoThreeTreeNode
        {
        public:
            
            //friend std::ostream& operator <<(std::ostream& oss, const TwoThreeTreeNode& node);
            enum{EmptyNode = 0, OneNode,TwoNode,ThreeNode} type;
            Item items[3]; 
            TwoThreeTreeNode *ptr[4];
            TwoThreeTreeNode *parent; 
        public:
            
            TwoThreeTreeNode& operator=(const TwoThreeTreeNode& node)
            {
                if(this!=&node)
                {
                    type = node.type;
                    for(int i=0;i<type;i++)
                    {
                        items[i] = node.items[i];
                        ptr[i] = node.ptr[i];
                    }
                    ptr[type] = node.ptr[type];
                    parent = node.parent;
                }
                return *this;
            }
            
            //p is a Empty child node
            //merging current'node's one item into its other non-empty child node
            void merge(TwoThreeTreeNode* p)
            {
                TwoThreeTreeNode* tmpP;
                if(type==OneNode)
                {
                    if(p==ptr[0])
                    {
                        ptr[1]->add(items[0],p->ptr[0],ptr[1]->ptr[0]);
                        ptr[0] = ptr[1]; 
                        ptr[1] = NULL;
                        type = EmptyNode;
                        delete p;
                        return;
                    }
                    else
                    if(p==ptr[1])
                    {
                        ptr[0]->add(items[0],ptr[0]->ptr[1],p->ptr[0]);
                        ptr[1] = NULL;
                        type = EmptyNode;
                        delete p;
                        return;
                    }
                }
                else 
                if(type==TwoNode)
                {
                    if(p == ptr[0])
                    {
                        ptr[1]->add(items[0],p->ptr[0],ptr[1]->ptr[0]);
                        this->remove(0,tmpP);
                        delete p;
                        return;
                    }
                    else
                    if(p == ptr[1])
                    {
                        ptr[0]->add(items[0],ptr[0]->ptr[1],p->ptr[0]);
                        this->remove(0,tmpP);
                        delete p;
                        return;
                    }
                    else 
                    if(p == ptr[2])
                    {
                        ptr[1]->add(items[1],ptr[1]->ptr[1],p->ptr[0]);
                        this->remove(1,tmpP);
                        delete p;
                        return;
                    }
                }
                
                throw SetException("unkown merge error");
            }
        
            //redistribute a given child (Empty) among 
            //its adjacent two-nodesibling that is twoNode
            //and current node
            // p must be one of the child node of current node
            //return true if distribute is possible and done, otherwise false
            bool redistribute(TwoThreeTreeNode* p)
            {
                TwoThreeTreeNode* tmpP;
                Item tmp;
                
                if(type==OneNode)
                {
                    if(p==ptr[0] && ptr[1]->type==TwoNode)
                    {
                        tmp = items[0];
                        items[0] = ptr[1]->remove(0,tmpP);
                        ptr[0]->add(tmp,ptr[0]->ptr[0],tmpP);
                        return true;
                    }
                    else
                    if(p==ptr[1] && ptr[0]->type==TwoNode)
                    {
                        tmp = items[0];
                        items[0] = ptr[0]->remove(1,tmpP);
                        ptr[1]->add(tmp,tmpP,ptr[1]->ptr[0]);
                        return true;
                    }
                }
                else
                if(type==TwoNode)
                {
                    if(p==ptr[0] && ptr[1]->type==TwoNode)
                    {
                        tmp = items[0];
                        items[0] = ptr[1]->remove(0,tmpP);
                        ptr[0]->add(tmp,ptr[0]->ptr[0],tmpP);
                        return true;
                    }
                    else
                    if(p==ptr[1])
                    {
                        if(ptr[0]->type == TwoNode)
                        {
                            tmp = items[0];
                            items[0] = ptr[0]->remove(1,tmpP);
                            ptr[1]->add(tmp,tmpP,ptr[1]->ptr[0]);
                            return true;
                        }
                        else
                        if(ptr[2]->type == TwoNode)
                        {
                            tmp = items[0];
                            items[0] = ptr[2]->remove(0,tmpP);
                            ptr[1]->add(tmp,ptr[0]->ptr[0],tmpP);
                            return true;
                        }
                    }
                    else
                    if(p==ptr[2] && ptr[1]->type==TwoNode)
                    {
                        tmp = items[1];
                        items[1] = ptr[1]->remove(1,tmpP);
                        ptr[2]->add(tmp,tmpP,ptr[2]->ptr[0]);
                        return true;
                    }
                }
                
                return false;
            }
            
            //retrieve index of the item matching the key
            int index(const Key& key) const
            {
                for(int i=0;i<type;i++)
                    if( (Key)items[i] == key)
                        return i;
                return -1;
            }
            
            //find the inorder successor of the given key on the node
            TwoThreeTreeNode* successor_inorder(const Key& key) const
            {
                TwoThreeTreeNode *cur = NULL;
                for(int i=0;i<type;i++)
                    if( (Key)items[i] == key)
                    {
                        cur = ptr[i+1];
                        break;
                    }
                
                if(cur)
                {
                    //find left-most child of this subtree
                    while( cur->ptr[0])
                        cur = cur->ptr[0];
                }
                
                return cur;
            }
            
            //remove item via index 
            //return the removed item 
            //return the extra child link associated with the item
            Item remove(int index, TwoThreeTreeNode*& p) throw(SetException)
            {
                
                if(type==OneNode)
                {
                    if(leaf())
                    { 
                        type = EmptyNode;
                        return items[0];
                    }
                }
                else
                if(type==TwoNode)
                {
                    type = OneNode;
                    if(index == 0)
                    {
                        Item tmp = items[0];
                        items[0] = items[1];
                        p = ptr[0]; //the left child link is returned 
                        ptr[0] = ptr[1];
                        ptr[1] = ptr[2];
                        ptr[2] = NULL;
                        return tmp;
                    }
                    else
                    if(index == 1)
                    {
                        p = ptr[2];
                        ptr[2] = NULL;
                        return items[1];
                    }
                }
                
                throw SetException("unknown remove here");
            }
            
            //add a new item into the node
            //@item - the new payload to add into the node
            //@lchild - the left child attached to this payload
            //@rchild - the right child attached to this payload
            void add(const Item& item, TwoThreeTreeNode *lchild, TwoThreeTreeNode *rchild) throw(SetException)
            {
                switch(type)
                {
                    case EmptyNode:
                    {
                        items[0] = item;
                        ptr[0] = lchild; 
                        ptr[1] = rchild;
                        //type = OneNode;
                        break;
                    }
                    case OneNode:
                    {
                        if( (Key)item > items[0] ) //insert as right item
                        {
                            items[1] = item;
                            ptr[1] = lchild;
                            ptr[2] = rchild;
                        }
                        else    //insert as left item
                        {
                            items[1] = items[0];
                            ptr[2] = ptr[1];
                            items[0] = item;
                            ptr[0] = lchild;
                            ptr[1] = rchild;
                        }
                        //type = TwoNode;
                        break;
                    }
                    case TwoNode:
                    {
                        if( (Key)item < items[0] ) //insert as first 
                        {
                            items[2] = items[1];
                            items[1] = items[0];
                            ptr[3] = ptr[2];
                            ptr[2] = ptr[1];
                            
                            items[0] = item;
                            ptr[0] = lchild;
                            ptr[1] = rchild; 
                        }
                        else
                        if ( (Key)item > items[0] && (Key)item < items[1] ) //insert as mid
                        {
                            items[2] = items[1];
                            ptr[3] = ptr[2];
                            
                            items[1] = item;
                            ptr[1] = lchild;
                            ptr[2] = rchild;
                        }
                        else            //insert as third
                        {
                            items[2] = item;
                            ptr[2] = lchild;
                            ptr[3] = rchild;
                        }
                        //type = ThreeNode;
                        break;
                    }
                    default:
                    {
                        //std::cout << *this << std::endl;
                        std::cout << type << std::endl;
                        std::cout << items[0] << "&" << items[1] << "&" << items[3] << std::endl;
                        throw SetException("unknown node");
                    }
                        
                }//switch
                
                type++;
                                
                //must link back child's parent to itself!
                if(lchild)
                    lchild->parent = this;
                if(rchild)
                    rchild->parent = this;
            }
            
            bool leaf() const
            {
                for(int i=0;i<4;i++)
                    if(ptr[i])
                        return false;
                return true;
            }
            
            bool contains(const Key& key) const
            {
                for(int i=0;i<type;i++)
                    if(key == (Key)items[i])
                        return true;
                return false;
            }
            
            const Item& get(const Key& key) const throw(SetException)
            {
                for(int i=0;i<type;i++)
                    if(key == (Key)items[i])
                        return items[i];
                throw SetException("keyed item not found");
            }
            
            TwoThreeTreeNode()
            {
                for(int i=0;i<4;i++)
                    ptr[i] = NULL;
                parent = NULL;
                type = EmptyNode;
            }

            std::string string() const
            {
                std::ostringstream oss;
                oss << "{" << type << ":" << items[0] << "&" << items[1] << "&" << items[2] << "}";
                return oss.str();
            }
        };
        
        /*
        template<typename Item>
        std::ostream& operator <<(std::ostream& oss, const TwoThreeTreeNode<Item>& node)
        {
            oss << "{" << node.type << ":" << node.items[0] << "&" << node.items[1] << "&" << node.items[2] << "}";
            return oss;
        }
        */
        
        /**
         Pointer-Based Implementation of a 2-3 Balanced Search Tree
         See DAPS Chapter 12. Page 621 for discussion
         **/
        template<typename Item, typename Key>
        class TwoThreeTree : public Set<Item>
        {
        public:
            typedef TwoThreeTreeNode<Item,Key> TNode;
            enum TraverseOrder
            {
              PREORDER,INORDER,POSTORDER  
            };
            
        public:
            TwoThreeTree():root(NULL),count(0){}
            virtual ~TwoThreeTree(){ clear(); }
            TwoThreeTree& operator =(const TwoThreeTree& ttt);
            TwoThreeTree(const TwoThreeTree& ttt) : root(NULL),count(0){ *this = ttt;}
            
            void clear(){ recursive_clear(root); count = 0;}
            bool empty() const{return count==0;}
            int size() const{return count;}
            void print(TwoThreeTree<Item,Key>::TraverseOrder = INORDER);
            
            void insert(const Item& item) throw(SetException);
            void remove(const Key& key) throw(SetException);
            
            
        private:
            //recursive search for a target key node
            template<typename Func>
            void recursive_traverse(TNode* p, Func& func,TraverseOrder order = INORDER);
            
            //on found, return the found TNode
            //on failed, return the leaf node where the keyed item should be inserted conceptually
            TNode* recursive_search(TNode* p, const Key& key)
            {
                if(p)
                {
                    //if matched, or leaf node reached, return current node
                    if( p->leaf() || p->contains(key) )
                        return p;
                    
                    if(p->type==TNode::OneNode)
                    {
                        if( key < (Key)(p->items[0]) )
                            return recursive_search(p->ptr[0], key); //descend to left child
                        else 
                        if( key > (Key)(p->items[0]) )
                            return recursive_search(p->ptr[1], key);//descend to right child
                    }
                    else
                    if(p->type==TNode::TwoNode)
                    {
                        if( key < (Key)(p->items[0]) )
                            return recursive_search(p->ptr[0], key);//descend to left child
                        else
                        if ( (key > (Key)(p->items[0]))  && (key < (Key)(p->items[1])) )
                            return recursive_search(p->ptr[1], key);//descend to mid child
                        else
                        if ( key > (Key)(p->items[1]) )
                            return recursive_search(p->ptr[2], key);//descend to right child
                    }
                    else 
                        throw SetException("Invalid Node deteced here !");
                }
                
                //should never occur
                return p;
            }
            
            void recursive_split(TNode* cur);
            void recursive_fix(TNode* cur);
            void recursive_clear(TNode*& cur);
            void recursive_copy(TNode*& target, const TNode* source);
            
            //return height of tree
            int height() const
            {
                TNode* cur = root;
                int h = 0;
                while(cur!=NULL)
                {
                    cur = cur->ptr[0];
                    h++;
                }
                return h;
            }
            
        private:
            int count;
            TNode* root;
        };

        
        template<typename Item, typename Key>
        void TwoThreeTree<Item,Key>::recursive_copy(TNode*& target, const TNode* source)
        {
            if(source)
            {
                target = new TNode();
                *target = *source;
                
                for(int i=0;i <= target->type;i++)
                {
                    recursive_copy(target->ptr[i], source->ptr[i]);
                    
                    if(target->ptr[i])
                        target->ptr[i]->parent = target;
                }
                
            }
            else 
            {
                target = NULL;
            }
        }
        
        //recursive copy of the entire tree structure 
        template<typename Item, typename Key>
        TwoThreeTree<Item,Key>& TwoThreeTree<Item,Key>::operator =(const TwoThreeTree<Item,Key>& ttt)
        {
            if(this!=&ttt)
            {
                clear();
                recursive_copy(root, ttt.root);
                count = ttt.count;
            }
            return *this;
        }
        
        template<typename Item, typename Key>
        void TwoThreeTree<Item,Key>::recursive_clear(TNode*& cur)
        {
            if(cur==NULL)
                return;
            
            for(int i=0;i<=cur->type;i++)
                recursive_clear(cur->ptr[i]);
            
            delete cur;
            cur = NULL;
        }

    
        
        
        template<typename Item, typename Key>
        void TwoThreeTree<Item,Key>::remove(const Key& key) throw(SetException)
        {
            TNode* cur = recursive_search(root, key);
            if(cur)
            {
                if(!cur->leaf())
                {
                    //swap the keyed item with its inorder successor 
                    TNode* successor = cur->successor_inorder(key);
                    Item tmp = cur->get(key);
                    cur->items[ cur->index(key) ] = successor->items[0];
                    successor->items[0] = tmp;
                    cur = successor;
                }
                
                //remove the swapped in item from the leaf node
                TNode* tmp;
                cur->remove( cur->index(key) ,tmp);
                
                //if after deletion, it becomes an empty node, shall fix it
                if(cur->type==TNode::EmptyNode)
                    this->recursive_fix(cur);
                
                count--;
            }
        }
        
        template<typename Item, typename Key>
        void TwoThreeTree<Item,Key>::recursive_fix(TNode* cur)
        {
            //if root node is an empty node, remove it
            if(cur==root)
            {
                root = cur->ptr[0];
                delete cur;
            }
            else
            {
                TNode* p = cur->parent;
             
                //first attemp to redistribute among parent,
                //cur and its adjacent sibling
                //if not possible, do merge
                if(!p->redistribute(cur))
                    p->merge(cur);
                
                if(p->type==TNode::EmptyNode)
                    this->recursive_fix(p);
            }
        }
        
        template<typename Item, typename Key>
        void TwoThreeTree<Item,Key>::insert(const Item& item) throw(SetException)
        {
            
            TNode* cur = recursive_search(root, item);
        
            //if empty tree, create the root node
            if(root==NULL)
            {
                root = new TNode();
                cur = root;
            }
            
            cur->add(item,NULL,NULL); //add to leaf node
            
            if(cur->type == TNode::ThreeNode)
                this->recursive_split(cur);
            
            count++;
        }
        
        
        //
        //
        //@assume Current Node is a ThreeNode 
        template<typename Item, typename Key>
        void TwoThreeTree<Item,Key>::recursive_split(TNode* cur)
        {
            //splitting a root node
            if(cur==root)
            {
                root = new TNode();
                cur->parent = root;
            }

            //split into two child nodes
            TNode* n1 = new TNode();
            n1->add(cur->items[0],cur->ptr[0],cur->ptr[1]);
            
            TNode* n2 = new TNode();
            n2->add(cur->items[2],cur->ptr[2],cur->ptr[3]);
            
            //add mid item to parent with n1,n2 attached
            cur->parent->add(cur->items[1],n1,n2);
            
            //delete current node
            TNode* parent = cur->parent;
            delete cur;
            
            //continue split on parent
            if(parent->type == TNode::ThreeNode)
                this->recursive_split(parent);
        }
        
        
        template<typename Item, typename Key>
        template<typename Func>
        void TwoThreeTree<Item,Key>::recursive_traverse(TNode* p, Func& func,
                                                    TraverseOrder order)
        {
            if(p)
            {
                if(p->type==TNode::OneNode)
                {
                    if(order==PREORDER) func(p->items[0]);
                    recursive_traverse(p->ptr[0], func, order);
                    if(order==INORDER) func(p->items[0]);
                    recursive_traverse(p->ptr[1], func, order);
                    if(order==POSTORDER) func(p->items[0]);
                }
                else
                if(p->type==TNode::TwoNode)
                {
                    if(order==PREORDER)
                    {
                        //std::cout << "{";
                        func(p->items[0]);
                        //std::cout << "&";
                        func(p->items[1]);
                        //std::cout << "}";
                    }
                    
                    recursive_traverse(p->ptr[0], func, order);
                    if(order==INORDER) func(p->items[0]);
                    recursive_traverse(p->ptr[1], func, order);
                    if(order==INORDER) func(p->items[1]);
                    recursive_traverse(p->ptr[2], func, order);
                
                    if(order==POSTORDER)
                    {
                        func(p->items[0]);
                        func(p->items[1]);
                    }
                }
                else
                {
                    std::cout << "warning: invalid node type detected!!" << std::endl;
                    std::cout << "type: " << p->type << std::endl;
                    std::cout << p->items[0] << "&" << p->items[1] << "&" << p->items[2] << std::endl;
                    std::cout << p->ptr[0] << "&" << p->ptr[1] << "&" << p->ptr[2] << "&" << p->ptr[3] << std::endl;
                }
            }
        }
        
        
        namespace tree
        {
            template<typename Item>
            struct TwoThreeTreePrinter
            {
             void operator()(const Item& item) const
                {
                    std::cout << "{" << item << "}" << std::endl;
                }
            };
        }
        
        template<typename Item, typename Key>
        void TwoThreeTree<Item,Key>::print(TwoThreeTree<Item,Key>::TraverseOrder)
        {
            std::cout << "\ntotal items: " << count << std::endl;
            std::cout << "current height: " << height() << std::endl;
            tree::TwoThreeTreePrinter<Item> printer;
            recursive_traverse(root, printer);
        }



    }
}
#endif
