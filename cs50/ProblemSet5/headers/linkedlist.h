#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
#include <stdexcept>
#include <cstdlib>

using namespace std;

typedef unsigned long Long;

template <typename T>
class Node
{
private:
  T *data;
  Node *nextNode;
public:
//===============================================================================================================
  Node()//constructor node
  {
      data=new T;
      nextNode=NULL;
  }
//===============================================================================================================
  ~Node()//destructor node
  {
    delete this->data;
  }
//===============================================================================================================
  bool hasNext()//exist pointer to next node
  {
    return this->nextNode!=NULL;
  }
//===============================================================================================================
  void setNext(Node<T>* next)//set pointer to the next node
  {
    this->nextNode=next;
  }
//===============================================================================================================
  Node<T>* getNext()//return a pointer to next node;
  {
      return this->nextNode;
  }
//===============================================================================================================
  void setData(T value)//set value to data
  {
   *(this->data)=value;
  }
//===============================================================================================================
  T getData()//returns value of data
  {
   return *(this->data);
  }
//===============================================================================================================
};

template<typename T>
class LinkedList
{
private:
    Node<T> *node;//pointer on current node
    Node<T> *root;//pointer on first node
    Long *count;
//===============================================================================================================
    void printData(Node<T>* data_node)//recursive print data
    {
        cout<<data_node->getData()<<" ";
        if(data_node->hasNext())
        {
            printData(data_node->getNext());
        }
    }
//===============================================================================================================
    void deleteNode(Node<T>* node_for_delete)//recursive delete node
    {
        if(node_for_delete->hasNext())
        {
            deleteNode(node_for_delete->getNext());
        }
        delete node_for_delete;
    }
//===============================================================================================================
    void checkIndex(Long index)//check index for good values
    {
        if(index<0 || index>=*(this->count))
        {
            throw invalid_argument("invalid index");
        }
    }
//===============================================================================================================
    Node<T>* findNode(Long index, Node<T>* node_for_find)//find node for it index
    {
      if(index==0)
      {
        return node_for_find;
      }
      if(node_for_find->hasNext())
      {
          return findNode(index-1, node_for_find->getNext());
      }
      else
      {
         throw invalid_argument("invalid index");
      }
    }
//===============================================================================================================
    bool checkValue(T value, Node<T> * check_node) //check value on list
    {
      if(check_node->getData()==value)
      {
        return true;
      }
      if(check_node->hasNext())
      {
        return checkValue(value, check_node->getNext());
      }
      else
      {
        return false;
      }
    }
//===============================================================================================================
public:
//===============================================================================================================
   LinkedList() //constructor without parameters
   {
    this->root =new Node<T>;
    this->count=new Long;
    *(this->count)=0;
   }
//===============================================================================================================
   LinkedList(T value):LinkedList()//constructor with parameters
   {
    node=new Node<T>;
    root->setNext(node);
    node->setData(value);
    (*(this->count))++;
   }
//===============================================================================================================
   ~LinkedList()
   {
       delete count;
       deleteNode(root);
   }
//===============================================================================================================
   void showList()//print list to console
   {
     printData(root->getNext());
     cout<<endl;
   }
//===============================================================================================================
   void addElement(T value)//create new element and add value
   {
       if(root->hasNext())
       {
        Node<T> *newNode=new Node<T>;
        newNode->setData(value);
        node->setNext(newNode);
        node=newNode;
       }
       else
       {
        node=new Node<T>;
        node->setData(value);
        root->setNext(node);
       }
       (*(this->count))++;
   }
//===============================================================================================================
   Long getLenght()
   {
       return *(this->count);
   }
//===============================================================================================================
   void removeElement(Long index)//remove element for it index
   {
     checkIndex(index);
     Node<T> *temp;
     if(index==0)
     {
        temp=root->getNext();
        root->setNext(temp->getNext());
     }
     else
     {
       Node<T> *previousNode=findNode(index-1,root->getNext());
       temp=previousNode->getNext();
       previousNode->setNext(temp->getNext());       
     }
     delete temp;
      (*(this->count))--;
   }
//===============================================================================================================
   void insertElement(Long index, T value)//insert element by index
   {
     checkIndex(index);
     Node<T> *nextNode;
     Node<T> *newNode=new Node<T>;
     newNode->setData(value);
     if(index==0)
     {
        nextNode=root->getNext();
        root->setNext(newNode);
        newNode->setNext(nextNode);
     }
     else
     {
       Node<T> *previousNode=findNode(index-1,root->getNext());
       nextNode=previousNode->getNext();
       previousNode->setNext(newNode);
       newNode->setNext(nextNode);      
     }
     (*(this->count))++;
   }
//===============================================================================================================
   bool containsOf(T value)//check for contains value in array
   {
    return checkValue(value, root->getNext());
   }
//===============================================================================================================
   void clear()//clear all nodes
   {
     this->deleteNode(root->getNext());
   }
//===============================================================================================================
};


#endif // LINKEDLIST_H
