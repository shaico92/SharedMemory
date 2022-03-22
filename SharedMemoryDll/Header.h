#pragma once
#include <string>
#include <tchar.h>
#include <iostream>


#include <tchar.h>
#include "atlstr.h"
#include <windows.h>
#include <memoryapi.h>
#include <handleapi.h>
#include <vector>
#ifdef SHARED_MEMORY_DLL_EXPORTS
#  define EXPORT __declspec(dllexport)
#else
#  define EXPORT __declspec(dllimport)

#endif


using namespace std;
enum  EXPORT Structs_enum {
    INVALID =-1,
	Wawa_ = 22,
	Wawa_2=23,
    WithChars_t=15,
};
namespace SHARED_ {
    TCHAR MemoryName[100];
    TCHAR AddressName[100];
    HANDLE hMapFile1;
    HANDLE hMapFile2;
#  define SuperSize  5000
#  define Size  500
}
  class EXPORT   MemoryManager

{
private:
	int Buffer = 0;

    HANDLE hMapFile1;
    HANDLE hMapFile2;
    TCHAR MemoryName[100];
    TCHAR MemoryNameAdd[100];
 


public:





	void   AccessSharedMemory( std::string theNameForMem);



    template<typename T>
    std::vector<T> GetAllElements(Structs_enum typeEnum) {
        std::vector<T> data;
    
        char* AddressBuffer_;
        char* DataBuffer_;
        

        AddressBuffer_ = (char*)MapViewOfFile(hMapFile1,   // handle to map object
            FILE_MAP_ALL_ACCESS, // read/write permission
            0,
            0,
            Size);

        DataBuffer_ = (char*)MapViewOfFile(hMapFile2,   // handle to map object
            FILE_MAP_ALL_ACCESS, // read/write permission
            0,
            0,
            SuperSize);

        char* cf = new char[600];
        memcpy_s(cf, sizeof(char**), AddressBuffer_, sizeof(char**));










        int index = 0;
        while (index <Size|| (AddressBuffer_[index]) != '\0')
        {
            Structs_enum invalid = Structs_enum::INVALID;
            memcpy_s(&invalid, sizeof(Structs_enum), &AddressBuffer_[index], sizeof(Structs_enum));
          //  AddressBuffer_ += sizeof(Structs_enum);
            index += sizeof(Structs_enum);
            cout << *&(AddressBuffer_[index]);
         
            if (invalid == typeEnum)
            {
               
               
                //for some reason its not saving the pointers after releasing the application

                auto f = ((T**)&(AddressBuffer_[index]));


                T types;
                memcpy_s(&types, sizeof(T), &**f, sizeof(T));
              //  AddressBuffer_ += sizeof(char**);
                index += sizeof(char**);
                memcpy_s(cf, sizeof(char**), &(AddressBuffer_[index]), sizeof(char**));
              //  AddressBuffer_ += sizeof(char**);
                index += sizeof(char**);
                data.push_back(types);
            }
            else {

             //   AddressBuffer_ += sizeof(char**);
                index += sizeof(char**);
              //  AddressBuffer_ += sizeof(char**);
                index += sizeof(char**);
            }


        }

        return data;
    }

    template<typename T>
    void AddToBuffer(T* TypeData, unsigned int HowManyObjects, Structs_enum typeEnum) {





        for (size_t i = 0; i < HowManyObjects; i++)
        {
            AddToBuffer<T>(TypeData[i], typeEnum);
        }







    }


    template<typename T>
    void AddToBuffer(T TypeData, Structs_enum typeEnum) {
    
        char* AddressBuffer_;
        char* DataBuffer_;



        AddressBuffer_ = (char*)MapViewOfFile(hMapFile1,   // handle to map object
            FILE_MAP_ALL_ACCESS, // read/write permission
            0,
            0,
            Size);

        DataBuffer_ = (char*)MapViewOfFile(hMapFile2,   // handle to map object
            FILE_MAP_ALL_ACCESS, // read/write permission
            0,
            0,
            SuperSize);
        char** Address = &DataBuffer_;

        //memcpy_s(DataBuffer_, sizeof(T), &TypeData, sizeof(T));

        if (NULL==DataBuffer_||NULL== AddressBuffer_)
        {
            cout << "No Mapping was good" << endl;
            return;
        }
        char* emptyData;
        char** Address_;
        char* ptr = new char[sizeof(char**)];
        bool thereisData = false;
        while (*AddressBuffer_!='\0')
        {
            std::cout << (char)&AddressBuffer_ << std::endl;

            
            bool aboutToTouch = false;




            memcpy_s(ptr, sizeof(Address_), AddressBuffer_, sizeof(Address_));
            
            if ('\0' == (*ptr))
            {
                emptyData = ptr;
               
                break;
            }




            AddressBuffer_ += sizeof(Structs_enum);
            AddressBuffer_ += sizeof(Address_);
            AddressBuffer_ += sizeof(Address_);
            thereisData = true;
           
            //ptrOfBuffer -= sizeof(T);
        }
        //memcpy_s(emptyData, sizeof(Structs_enum), &typeEnum, sizeof(Structs_enum));
        emptyData = AddressBuffer_;
        const int TypeSize = sizeof(TypeData);
  
        if (thereisData)
        {
            AddressBuffer_ -= sizeof(Address_);
            
            Address_ = (char**)AddressBuffer_;
            DataBuffer_ = *Address_;
            memcpy_s(DataBuffer_, sizeof(T), &TypeData, sizeof(T));
            AddressBuffer_ += sizeof(Address_);
            //memcpy_s(&AddressBuffer_, sizeof(T), &TypeData, sizeof(T));
        }
        else {
            memcpy_s(DataBuffer_, sizeof(T), &TypeData, sizeof(T));
        }
       
        memcpy_s(AddressBuffer_, sizeof(Structs_enum), &typeEnum, sizeof(Structs_enum));

        AddressBuffer_ += sizeof(Structs_enum);
  

        //start address
        memcpy_s(AddressBuffer_, sizeof(Address), &DataBuffer_, sizeof(Address));
        AddressBuffer_ += sizeof(Address);
        //allocate end address
        DataBuffer_ += sizeof(T);
        memcpy_s(AddressBuffer_, sizeof(Address), &DataBuffer_, sizeof(Address));
        
        // {enum=4,ptrS=8,ptrE=8}
        //{if enum, get ptr,then use ptr + sizeofdata to get the next available space}







    }





   




};


