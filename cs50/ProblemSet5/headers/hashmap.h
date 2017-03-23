#ifndef HASHMAP_H
#define HASHMAP_H

#include <cstddef>
#include <iostream>
#include <stdexcept>
#include "arraylist.h"


template<class K, class V, template< class > class Container>
class HashMap
{
private:
long map_size;
Container<K> *keys;
Container<V> *values;


//===============================================================================================================
long indexOfKey(K key)//check for
{
 for(long i=0;i<map_size;i++)
 {
     if(keys->getValue(i)==key)
     {
         return i;
     }
 }
 return -1;
}
//===============================================================================================================
long indexOfValue(V value)
{
 for(long i=0;i<map_size;i++)
 {
     if(values->getValue(i)==value)
     {
         return i;
     }
 }
 return -1;
}
//===============================================================================================================
public:
//===============================================================================================================
HashMap()//constructor 10 elements
{
 keys=new Container<K>;
 values=new Container<V>;
}
//===============================================================================================================
~HashMap()//destructor
{
     delete [] keys;
     delete [] values;
}
//===============================================================================================================
bool containsOf(V value)//check for contains in array
{
    if(indexOfValue(value)>=0)
    {
        return true;
    }
    return false;
}
//===============================================================================================================
V findElement(K key)//find element by index
{
   long temp_key_index=indexOfKey(key);
   if (temp_key_index>=0)
   {
       return values->getValue(temp_key_index);
   }
   else
   {
       return NULL;
   }
}
//===============================================================================================================
void removeElement(K key)//remove element by index
{
    long temp_key_index=indexOfKey(key);
    if(temp_key_index>=0)
    {
        keys->removeElement(temp_key_index);
        values->removeElement(temp_key_index);
    }
    map_size--;
}
//===============================================================================================================
void insertElement(K key, V value)//add element to array
{
 long temp_key_index=indexOfKey(key);
 if(temp_key_index==-1)
 {
     keys->addElement(key);
     values->addElement(value);
 }
 else
 {
     values->insertElement(temp_key_index, value);
 }
 map_size++;
}
//===============================================================================================================
};

#endif // HASHMAP_H
