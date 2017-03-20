#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include <cstdlib>
#include <iostream>
#include <cstring>
#include <fstream>
#include <stdexcept>
#include <cstring>

typedef unsigned long Long;

using namespace std;

template<class T>
class ArrayList
{
private:
    Long size_of_list;
    Long allocated_memory;
    T *array;

    void checkIndex(Long index) //check index of array
    {
        if(index<0 || index>=size_of_list)
        {
          throw invalid_argument("invalid index");
        }
    }
    void fillArrayZero()//fill array 0
    {
     memset(array, 0, allocated_memory*sizeof(T));
    }
    T* removeElementByIndex(Long index) //copy array to new  array without element[index]
    {
        T* newArray= new T(allocated_memory);
        for(Long i=0;i<index;i++)
        {
            newArray[i]=this->array[i];
        }
        for(Long j=index+1;j<size_of_list;j++)
        {
          newArray[j-1]=this->array[j];
        }
        return newArray;
    }
    void reallocMemory() //allocated double more memory for array
    {
        allocated_memory+=allocated_memory;
        T* temp=new T[allocated_memory];
        for(Long i=0;i<size_of_list;i++)
        {
          temp[i]=array[i];
        }
        delete [] array;
        array=temp;
    }
    T* insertElement(Long index, T value) //copy array to new  array with new element[index]
    {
        T* newArray= new T(allocated_memory);
        for(Long i=0;i<index;i++)
        {
            newArray[i]=this->array[i];
        }
        newArray[index]=value;
        for(Long j=index+1;j<=size_of_list;j++)
        {
          newArray[j]=this->array[j-1];
        }
        return newArray;
    }

public:
    ArrayList(int number=10) //constructor with default value
    {
        allocated_memory=number;
        array=new T[allocated_memory];
        size_of_list=0;
        fillArrayZero();
    }
    ~ArrayList() //destructor
    {
        delete [] array;
    }
    bool addElement(T element) //if exists add element to array
    {
        if(size_of_list==allocated_memory)
        {
         reallocMemory();
        }
        array[size_of_list]=element;
        size_of_list++;
        return true;
    }
    Long sizeOfArray() //return size of filled array
    {
      return size_of_list;
    }
    Long sizeOfAllocatedMemory() //return size of allocated memory
    {
      return allocated_memory;
    }
    void showArray() //print array to console
    {
        for(Long i=0;i<size_of_list;i++)
        {
            cout<<this->array[i]<<" ";
        }
        cout<<endl;
    }
    void showFullArray ()//print allocated memory to console
    {
        for(Long i=0;i<allocated_memory;i++)
        {
            cout<<array[i]<<" ";
        }
        cout<<endl;

    }
    void removeElement(Long index)//copy array to new array without element[index] & array becomes new array
    {
        checkIndex(index);
        array=removeElementByIndex(index);
        size_of_list--;
    }
    void setValue(Long index, T value) //set value by index
    {
       checkIndex(index);
       array[index]=value;
    }
    T* getValue(Long index)//get value of array element by it index
    {
       checkIndex(index);
       return &array[index];
    }
    void trimToSize()//trim memory to filled area size
    {
        T* new_arr=new T[size_of_list];
        for(Long i =0;i<size_of_list;i++)
        {
            new_arr[i]=this->array[i];
        }
        delete [] array;
        this->array=new_arr;
        allocated_memory=size_of_list;
    }
    void insertValue(Long index, T value) //insert value in element[index]
    {
      checkIndex(index);
      if(size_of_list==allocated_memory || size_of_list+1==allocated_memory)
      {
          reallocMemory();
      }
      ArrayList<T> temp_array=array;
      array=insertElement(index, value);
      size_of_list++;
      delete [] temp_array;
    }
    bool containOf(T value)//check array for value
    {
        for(Long i=0;i<size_of_list;i++)
        {
            if(*(this->getValue(i))==value)
               {
                return true;
               }
        }
        return false;
    }
    bool loadStringFromFile(string file_name)//load array from file
    {
        string temp_str;
        ifstream file(file_name);
        while(getline(file, temp_str))
        {
            this->addElement(temp_str);
        }
        file.close();
        return true;
    }
    bool setAllocatedMemory(Long new_memory)//i know it unsecure-but needed for hashmap
    {
      if(new_memory<=allocated_memory)
      {
          return false;
      }
      else
      {
          allocated_memory=new_memory;
          this->reallocMemory();
      }
    }
};


#endif // ARRAYLIST_H
