// Test.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <string>
#include <tchar.h>
#include <iostream>


#include <tchar.h>
#include "atlstr.h"
#include <windows.h>
#include <memoryapi.h>
#include <handleapi.h>
#include <vector>

#define BUFFDATA_ 36000

TCHAR AddressBuffer[] = TEXT("Local\\MyMap");
TCHAR DataBuffer[] = TEXT("Local\\Mfff");

struct S{
    int id = 2;
    char mem[100];
};
struct Mo
{
    int ids = 31;
    char mom[22];
};
enum Structs_enum
{
    INVALID = -1,
    Mo_e=0,
    S_e=1
};

char* GetEmpty(char* buffer) {
    int i = 0;
    char* current=NULL;
    while (buffer[i]!='\0')
    {
        current = &buffer[i];
        ++i;

    }
    return current;
}

//template<typename T>
void SharedMemoryStuff(/*T type*/) {

    char* AdressesBuffer;
    char* ptrOfBuffer;
    HANDLE hMapFile_1;
    HANDLE hMapFile_2;

    HANDLE   hMapFile1 = OpenFileMapping(
        FILE_MAP_ALL_ACCESS,   // read/write access
        FALSE,                 // do not inherit the name
        AddressBuffer);

    HANDLE  hMapFile2 = OpenFileMapping(
        FILE_MAP_ALL_ACCESS,   // read/write access
        FALSE,                 // do not inherit the name
        DataBuffer);
    if (NULL!= hMapFile1||NULL!= hMapFile2)
    {
        return;
    }

    hMapFile_2 = CreateFileMapping(
        INVALID_HANDLE_VALUE,    // use paging file
        NULL,                    // default security
        PAGE_READWRITE,          // read/write access
        0,                       // maximum object size (high-order DWORD)
        BUFFDATA_,                // maximum object size (low-order DWORD)
        DataBuffer);

    hMapFile_1 = CreateFileMapping(
        INVALID_HANDLE_VALUE,    // use paging file
        NULL,                    // default security
        PAGE_READWRITE,          // read/write access
        0,                       // maximum object size (high-order DWORD)
        360,                // maximum object size (low-order DWORD)
        AddressBuffer);



}


template<typename T>
 std::vector<T> GetAllElements(Structs_enum typeEnum) {
     std::vector<T> data;
    HANDLE hMapFile1;
    HANDLE hMapFile2;
    char* AddressBuffer_;
    char* DataBuffer_;
    hMapFile1 = OpenFileMapping(
        FILE_MAP_ALL_ACCESS,   // read/write access
        FALSE,                 // do not inherit the name
        AddressBuffer);

    hMapFile2 = OpenFileMapping(
        FILE_MAP_ALL_ACCESS,   // read/write access
        FALSE,                 // do not inherit the name
        DataBuffer);

    AddressBuffer_ = (char*)MapViewOfFile(hMapFile1,   // handle to map object
        FILE_MAP_ALL_ACCESS, // read/write permission
        0,
        0,
        360);

    DataBuffer_ = (char*)MapViewOfFile(hMapFile2,   // handle to map object
        FILE_MAP_ALL_ACCESS, // read/write permission
        0,
        0,
        BUFFDATA_);



    char** Address = &DataBuffer_;
    int i = 0;
    while (true)
    {
        std::cout << (char)&AddressBuffer_ << std::endl;
        bool aboutToTouch = false;
        char* ptr = new char[5000];
        Structs_enum T_ = Structs_enum::INVALID;
        memcpy_s(&T_, sizeof(Structs_enum), AddressBuffer_, sizeof(Structs_enum));
        if (T_==typeEnum)
        {
            aboutToTouch = true;
        
           
        }   
        AddressBuffer_ += sizeof(Structs_enum);
     
            memcpy_s(ptr, sizeof(Address), AddressBuffer_, sizeof(Address));
            auto sff = (T**)ptr;


            

            if (NULL == (sff)|| NULL == (*sff))
            {
                break;
            }
            if (aboutToTouch)
            {
                T typov_1 = **sff;
                data.push_back(typov_1);
            }
                
            
           
            

            AddressBuffer_ += sizeof(Address);
           
        
     
      
        //ptrOfBuffer -= sizeof(T);
    }

    return data;
}

 template<typename T>
 void AddToSharedMemory(T* TypeData,unsigned int HowManyObjects ,Structs_enum typeEnum) {





     for (size_t i = 0; i < HowManyObjects; i++)
     {
         AddToSharedMemory<T>(TypeData[i], typeEnum);
     }







 }


 template<typename T>
 void AddToSharedMemory(T TypeData, Structs_enum typeEnum) {
     HANDLE hMapFile1;
     HANDLE hMapFile2;
     char* AddressBuffer_;
     char* DataBuffer_;

     hMapFile1 = OpenFileMapping(
         FILE_MAP_ALL_ACCESS,   // read/write access
         FALSE,                 // do not inherit the name
         AddressBuffer);

     hMapFile2 = OpenFileMapping(
         FILE_MAP_ALL_ACCESS,   // read/write access
         FALSE,                 // do not inherit the name
         DataBuffer);

     AddressBuffer_ = (char*)MapViewOfFile(hMapFile1,   // handle to map object
         FILE_MAP_ALL_ACCESS, // read/write permission
         0,
         0,
         360);

     DataBuffer_ = (char*)MapViewOfFile(hMapFile2,   // handle to map object
         FILE_MAP_ALL_ACCESS, // read/write permission
         0,
         0,
         BUFFDATA_);
     char** Address = &DataBuffer_;

//memcpy_s(DataBuffer_, sizeof(T), &TypeData, sizeof(T));


char* emptyData;
char** Address_;
while (true)
{
    std::cout << (char)&AddressBuffer_ << std::endl;

    char* ptr = new char[5000];
    bool aboutToTouch = false;
   
  
 
  
        memcpy_s(ptr, sizeof(Address_), AddressBuffer_, sizeof(Address_));
        auto sff = (T***)ptr;
        if (NULL == (*sff))
        {
            emptyData = ptr;
            Address_ = &emptyData;
            break;
        }
    

  
  
    AddressBuffer_ += sizeof(Structs_enum);
    AddressBuffer_ += sizeof(Address_);
    //ptrOfBuffer -= sizeof(T);
}
//memcpy_s(emptyData, sizeof(Structs_enum), &typeEnum, sizeof(Structs_enum));


memcpy_s(emptyData, sizeof(T), &TypeData, sizeof(T));
memcpy_s(AddressBuffer_, sizeof(Structs_enum), &typeEnum, sizeof(Structs_enum));
AddressBuffer_ += sizeof(Structs_enum);
memcpy_s(AddressBuffer_, sizeof(Address_), Address_, sizeof(Address_));

     


 }

int main()
{
    S type;
    type.id = 214;
    std::string f = "dfsdfsdfsdf";
    strcpy_s(type.mem, 100, f.c_str());

    SharedMemoryStuff(/*type*/);
   // GetAllElements<S>();
    S arr[5];
    for (size_t i = 0; i < 5; i++)
    {
        arr[i].id = 0.511651 + i;
        strcpy_s(arr[i].mem, 100, f.c_str());
         

    }
    S tp;
    tp.id = 213123;
    GetAllElements< S>(Structs_enum::S_e);
    AddToSharedMemory<S>(tp,Structs_enum::S_e);
    tp.id = 3434;
    Mo cd;
    cd.ids = 7765;
    AddToSharedMemory<Mo>(cd, Structs_enum::Mo_e);
    AddToSharedMemory<S>(arr,5, Structs_enum::S_e);
    AddToSharedMemory<S>(tp, Structs_enum::S_e);
    GetAllElements< S>(Structs_enum::S_e);
   auto sClasses= GetAllElements< S>(Structs_enum::S_e);
   
    
    cd.ids = 1233;
    AddToSharedMemory<Mo>(cd, Structs_enum::Mo_e);

   auto bf = GetAllElements< Mo>(Structs_enum::Mo_e);
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
