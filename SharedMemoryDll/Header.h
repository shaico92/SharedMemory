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

#define MAXIMUM_SHARED_BUFFER 500000
using namespace std;
enum  EXPORT Types {
	invalid=-1,
	Wawa_ = 22,
	Wawa_2=23,
    WithChars_t=15,
};

  class EXPORT   MemoryManager

{
private:
	int Buffer = 0;

	char* UnAllocatedDataPtr=nullptr;
	TCHAR MemoryName[100];
	HANDLE mappHandle;
    int SizeToCheckForAllocation=0;
    int SizeOfCurrentType = 0;

 


public:



	template <typename T>
	void    AddToBuffer(T& theType, Types type) {
	

        char* data_;

        data_ = (char*)MapViewOfFile(mappHandle,   // handle to map object
            FILE_MAP_ALL_ACCESS, // read/write permission
            0,
            0,
            Buffer);


        if (data_ == NULL)
        {

            _tprintf(TEXT("Could not map view of file (%d).\n"),
                GetLastError());

            CloseHandle(mappHandle);


        }
        memcpy_s(&Buffer, sizeof(int), data_, sizeof(int));

        char prefix = 's';
        char suffix = 'e';

        char forTest = ' ';
        Types t = Types::invalid;
        T* ptr;
        char* smth= new char[1000];
        SizeOfCurrentType = sizeof(theType);

        
        char* data = GetBuffer();
    

        memcpy_s(GetBuffer(), sizeof(char), &prefix, sizeof(char));
        //test if allocated 's'
      //  memcpy_s(&forTest, sizeof(char), GetBuffer() - sizeof(char), sizeof(char));
        
    
        data = (char*)UnAllocatedDataPtr;
        cout<<"start memory"<< &data <<' ' << *data << endl;
        UnAllocatedDataPtr += sizeof(char);

        memcpy_s(GetBuffer(), sizeof(Types), &type, sizeof(Types));
        //test if allocated 'Types Enum'
        Types* dataT = (Types*)UnAllocatedDataPtr;
        cout << *dataT << endl;
        UnAllocatedDataPtr += sizeof(Types);
        // memcpy_s(&t, sizeof(Types), GetBuffer() - sizeof(Types), sizeof(Types));
         //test if allocated 'T'
        auto tstartet = GetBuffer();
        memcpy_s(GetBuffer(), sizeof(theType), &theType, sizeof(theType));

        memcpy_s(smth, sizeof(theType), tstartet, sizeof(theType));
        ptr = (T*)smth;

        UnAllocatedDataPtr += sizeof(theType);

        //test if allocated 'e'
        memcpy_s(GetBuffer(), sizeof(char), &suffix, sizeof(char));
        char* dataE = (char*)UnAllocatedDataPtr;
        cout << *dataE << endl;
        UnAllocatedDataPtr += sizeof(char);

	    
	
	
	};
	template <typename T>
    void  AddToBuffer(T* theType, Types type, unsigned int Iterations) {
        for (size_t i = 0; i < Iterations; i++)
        {
            /* memcpy_s(GetBuffer(), Buffer, &type, sizeof(type));


             memcpy_s(GetBuffer(), Buffer, &theType[i], sizeof(theType));*/
            AddToBuffer<T>(theType[i], type);

          
        }
    };

	void   AccessSharedMemory( std::string theNameForMem);
	char* GetBufferStart();
	void  setBufferSize(int size_);
	char* GetBuffer();
	template <typename T>
    std::vector<T> printObjectsOfType(Types type) {


        std::vector<T> allPtrs;

        char* pbuff = GetBufferStart();
        Types temp = Types::invalid;
        memcpy_s(&Buffer, sizeof(int), pbuff, sizeof(int));
        pbuff += sizeof(int);
        for (int i = 0;i < Buffer; ++i)
        {



            bool parsed = false;
            char* beforeValidation = pbuff;
            validBufferFormat<T>(pbuff, type, parsed);
            if (parsed)
            {
                pbuff = validBufferFormat<T>(beforeValidation, type, parsed);
                T* someType = (T*)pbuff;
                allPtrs.push_back(*someType);
                pbuff += sizeof(T);
                pbuff += sizeof(char);
            }
            else {
                pbuff += sizeof(char);
            }

            //   pbuff +=sizeof(char);



           //    memcpy_s(&temp, sizeof(Types), pbuff, sizeof(Types));
           //    if (temp==type)
           //    {

           ///*        std::cout << "about to touch a object" <<temp<< std::endl;
           //        
           //       
           //        pbuff += sizeof(Types);



           //        T* someType = (T*)pbuff;
           //        allPtrs.push_back(*someType);*/
           //      
           //    }
              /* pbuff+=sizeof(int);*/
        }


        //    memcpy_s(&someType, sizeof(theType), pbuff, sizeof(theType));
        return allPtrs;

    };
    template <typename T>
    std::vector<T*> printObjectsOfTypePtr(Types type) {


        std::vector<T*> allPtrs;

        char* pbuff = GetBufferStart();
        Types temp = Types::invalid;
        memcpy_s(&Buffer, sizeof(int), pbuff, sizeof(int));
        pbuff += sizeof(int);
        for (int i = 0;i < Buffer; ++i)
        {



            bool parsed = false;
            char* beforeValidation = pbuff;
            validBufferFormat<T>(pbuff, type, parsed);
            if (parsed)
            {
                pbuff = validBufferFormat<T>(beforeValidation, type, parsed);
                T* someType = (T*)pbuff;
                allPtrs.push_back(someType);
                pbuff += sizeof(T);
                pbuff += sizeof(char);
            }
            else {
                pbuff += sizeof(char);
            }

            //   pbuff +=sizeof(char);



           //    memcpy_s(&temp, sizeof(Types), pbuff, sizeof(Types));
           //    if (temp==type)
           //    {

           ///*        std::cout << "about to touch a object" <<temp<< std::endl;
           //        
           //       
           //        pbuff += sizeof(Types);



           //        T* someType = (T*)pbuff;
           //        allPtrs.push_back(*someType);*/
           //      
           //    }
              /* pbuff+=sizeof(int);*/
        }


        //    memcpy_s(&someType, sizeof(theType), pbuff, sizeof(theType));
        return allPtrs;

    };
	template <typename T>
    char* validBufferFormat(char* pbuff, Types typeWanted, bool& IsParsable) {

        //booleans


        IsParsable = false;
        //check if start of object with char 's'
        Types temp = Types::invalid;

        char Nll = '\0';
  
  
        
        //check if start of object with char 's'
        memcpy_s(&Nll, sizeof(char), pbuff, sizeof(char));
        bool matchStartOfObject = Nll == 's';
        if (matchStartOfObject)
        {
         

            pbuff += sizeof(char);
        }
        //check if enum is in object 
        memcpy_s(&temp, sizeof(Types), pbuff, sizeof(Types));
        bool matchingEnums = temp == typeWanted;
     
        if (matchingEnums)
        {
         

            pbuff += sizeof(Types);
        }
        //check struct  object 

        T* someType = (T*)pbuff;
        pbuff += sizeof(T);

        //check struct  object ends with 'e'
        memcpy_s(&Nll, sizeof(char), pbuff, sizeof(char));
        bool matchEndOfObject = Nll == 'e';
        if (matchEndOfObject)
        {
          

            pbuff -= sizeof(T);
            // pbuff += sizeof(char);
        }

        //returning charBuffer to the point of the struct

        IsParsable = matchStartOfObject && matchEndOfObject && matchingEnums;
        return pbuff;

    };






   




};


