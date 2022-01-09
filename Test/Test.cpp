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

#define BUFFDATA_ 36000

TCHAR szName[] = TEXT("Local\\MyMap");
TCHAR szName_[] = TEXT("Local\\Mye");

struct S{
    int id = 2;
    char mem[100];
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

template<typename T>
void SharedMemoryStuff(T type) {

    char* AdressesBuffer;
    char* ptrOfBuffer;
    HANDLE hMapFile_1;
    HANDLE hMapFile_2;


    hMapFile_2 = CreateFileMapping(
        INVALID_HANDLE_VALUE,    // use paging file
        NULL,                    // default security
        PAGE_READWRITE,          // read/write access
        0,                       // maximum object size (high-order DWORD)
        BUFFDATA_,                // maximum object size (low-order DWORD)
        szName_);

    hMapFile_1 = CreateFileMapping(
        INVALID_HANDLE_VALUE,    // use paging file
        NULL,                    // default security
        PAGE_READWRITE,          // read/write access
        0,                       // maximum object size (high-order DWORD)
        360,                // maximum object size (low-order DWORD)
        szName);

     char NoVal = '-';
     char empty = '\0';
     AdressesBuffer = (char*)MapViewOfFile(hMapFile_1,   // handle to map object
        FILE_MAP_ALL_ACCESS, // read/write permission
        0,
        0,
        360);


    ptrOfBuffer = (char*)MapViewOfFile(hMapFile_2,   // handle to map object
        FILE_MAP_ALL_ACCESS, // read/write permission
        0,
        0,
        BUFFDATA_);





    for (size_t i = 0; i < 360; i++)
    {
        //NoVal
        AdressesBuffer[i] = empty;
    }
    for (size_t i = 0; i < BUFFDATA_; i++)
    {
        //NoVal
        ptrOfBuffer[i] = empty;
    }
    S typo_;
    typo_.id = -666;
    int i = 0;
    char** Address = &ptrOfBuffer;
    memcpy_s(ptrOfBuffer, sizeof(T), &type, sizeof(T));

    

  

    memcpy_s(AdressesBuffer, sizeof(&Address), &Address, sizeof(&Address));
    auto s = (T***)AdressesBuffer;

    T typo = ***s;
    //Data
    auto typo_s = typo;


    ptrOfBuffer += sizeof(T);
    memcpy_s(ptrOfBuffer, sizeof(T), &typo_, sizeof(T));
    
    //probably remove & from &Address
    memcpy_s(AdressesBuffer, sizeof(&Address), &Address, sizeof(&Address));
  
  
   
    
    auto sf = (T***)AdressesBuffer;

    T* typov = **sf;
    //Data
    auto typo_svc = (S*)typov;
    //ptrOfBuffer -= sizeof(T);
    
    //AdressesBuffer -= sizeof(&Address);
    while (true)
    {
        char* ptr = new char[5000];
        memcpy_s(ptr, 8, AdressesBuffer, 8);
        auto sff = (T***)ptr;
        ptrOfBuffer -= sizeof(T);
    }
}

int main()
{
    S type;
    type.id = 214;
    std::string f = "dfsdfsdfsdf";
    strcpy_s(type.mem, 100, f.c_str());

    SharedMemoryStuff<S>(type);

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
