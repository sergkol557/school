#ifndef HASHMAP_H
#define HASHMAP_H

#include <cstddef>
#include <iostream>
#include "arraylist.h"
#include "linkedlist.h"

const int SEED=131;

typedef unsigned long Long;


template<typename K, typename V>
class HashMap
{
private:
Long *map_size;
ArrayList<LinkedList<V>> *array;
LinkedList<V> *list;

Long hashKey(int key)//hash function for int
{
    char* temp_key;
    sprintf(temp_key, "%i", key);
    return hashKey(temp_key);
}

Long hashKey(string key)//hash function for string
{
    Long hash = 0;
    for(int i = 0; i < key.length(); i++)
    {
       hash = (hash * SEED) + key[i];
    }
    return hash % (*(this->map_size));
}

public:
HashMap()
{
    this->map_size=new Long;
    this->array=new ArrayList<LinkedList<V>>;
    *(this->map_size)=array->sizeOfArray();

}
~HashMap()
{
     for (Long i=0;i<array->sizeOfArray();i++)
     {
         this->list=array->getValue(i);
         delete list;
         this->array->removeElement(i);
     }

     delete this->map_size;
}
void printKey(K key)
{
  cout<<hashKey(key);
}
void insertElement(K key, V value)
{
   Long hashed_key=hashKey(key);
   if(hashed_key>=this->array->sizeOfAllocatedMemory())
   {
       this->array->setAllocatedMemory(hashed_key);

   }
   list=array->getValue(hashed_key);
   list->addElement(value);

}
void deleteElement(K key)
{
 Long key_hash=hashKey(key);
 list=array->getValue(key_hash);
 list->clear();
}
void printElement(K key)//print element for its key
{
  Long key_hash=hashKey(key);
  list=array->getValue(key_hash);
  list->showList();
}
};


#endif // HASHMAP_H
