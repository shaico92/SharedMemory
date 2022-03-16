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
            SuperSize);

        DataBuffer_ = (char*)MapViewOfFile(hMapFile2,   // handle to map object
            FILE_MAP_ALL_ACCESS, // read/write permission
            0,
            0,
            SuperSize);



        char** Address = &DataBuffer_;
        int i = 0;
        char* ptr = new char[8];
        while (i<SuperSize)
        {
            std::cout << (char)&AddressBuffer_ << std::endl;
            bool aboutToTouch = false;
           
            Structs_enum T_ = Structs_enum::INVALID;
            memcpy_s(&T_, sizeof(Structs_enum), AddressBuffer_, sizeof(Structs_enum));
            if (T_ == typeEnum)
            {
                aboutToTouch = true;


            }
            AddressBuffer_ += sizeof(Structs_enum);
            i += sizeof(Structs_enum);
            memcpy_s(ptr, sizeof(char**), AddressBuffer_, sizeof(char**));
            T nodata;

            memcpy_s(&nodata, sizeof(T), ptr, sizeof(T));
          //  auto sff = (T****)nodata;




            if (aboutToTouch)
            {
             //   T typov_1 = ****sff;
             //   data.push_back(typov_1);
            }





            AddressBuffer_ += sizeof(char**);

            i += sizeof(char**);


            //ptrOfBuffer -= sizeof(T);
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
            SuperSize);

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
        while (true)
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
           
            //ptrOfBuffer -= sizeof(T);
        }
        //memcpy_s(emptyData, sizeof(Structs_enum), &typeEnum, sizeof(Structs_enum));


        memcpy_s(emptyData, sizeof(T), &TypeData, sizeof(T));
        memcpy_s(DataBuffer_, sizeof(T), &emptyData, sizeof(T));
        memcpy_s(AddressBuffer_, sizeof(Structs_enum), &typeEnum, sizeof(Structs_enum));
        AddressBuffer_ += sizeof(Structs_enum);
        memcpy_s(AddressBuffer_, sizeof(Address), &Address, sizeof(Address));


        
        char* cf = new char[600];
        memcpy_s(cf, sizeof(Address), AddressBuffer_, sizeof(Address));
    
        
      
     

        AddressBuffer_ = (char*)MapViewOfFile(hMapFile1,   // handle to map object
            FILE_MAP_ALL_ACCESS, // read/write permission
            0,
            0,
            SuperSize);

        while (*AddressBuffer_!='\0')
        {
            Structs_enum invalid = Structs_enum::INVALID;
            memcpy_s(&invalid, sizeof(Structs_enum), AddressBuffer_, sizeof(Structs_enum));
            AddressBuffer_ += sizeof(Structs_enum);

            if (invalid!= Structs_enum::INVALID)
            {
               
                memcpy_s(cf, sizeof(Address), AddressBuffer_, sizeof(Address));



                auto f = (T****)cf;
                
                cout << "f";
            }
            AddressBuffer_ += sizeof(T);

        }





    }





   




};


