#include "pch.h"
#include "Header.h"


void MemoryManager::AccessSharedMemory( std::string theNameForMem) {


    bool dataAccessed = true;



    char theNameAsBuffer[100];

    TCHAR ManagedMemoryName[100];


    size_t newsize = strlen(theNameAsBuffer) + 1;
    theNameForMem = "Local/M" + theNameForMem;

    strcpy_s(theNameAsBuffer, 100, theNameForMem.c_str());


    for (size_t i = 0; i < 100 && theNameAsBuffer[i] != '\0'; i++)
    {
        ManagedMemoryName[i] = theNameAsBuffer[i];
        SHARED_::MemoryName[i] = theNameAsBuffer[i];

    }

    //this is Const
    TCHAR AddressBuffer[] = TEXT("Local/MyMap");
    for (size_t i = 0; i < 100 && AddressBuffer[i] != '\0'; i++)
    {
        
        SHARED_::AddressName[i] = AddressBuffer[i];


    }

    







    char* AddressBuffer_;
    char* DataBuffer_;
    SHARED_::hMapFile1 = OpenFileMapping(
        FILE_MAP_ALL_ACCESS,   // read/write access
        FALSE,                 // do not inherit the name
        SHARED_::AddressName);

    SHARED_::hMapFile2 = OpenFileMapping(
        FILE_MAP_ALL_ACCESS,   // read/write access
        FALSE,                 // do not inherit the name
        SHARED_::MemoryName);




    bool creator = false;

    if (SHARED_::hMapFile2 == NULL|| SHARED_::hMapFile1 == NULL)
    {
        std::cout << "The Shared Memory Name could not be found  will now create a new 2 file  mapping to access it" << std::endl;
        SHARED_::hMapFile2 = CreateFileMapping(
            INVALID_HANDLE_VALUE,    // use paging file
            NULL,                    // default security
            PAGE_READWRITE,          // read/write access
            0,                       // maximum object size (high-order DWORD)
            SuperSize,              // maximum object size (low-order DWORD)
            SHARED_::MemoryName);

        if (SHARED_::hMapFile2 == NULL)
        {
            dataAccessed = false;
            _tprintf(TEXT("Could not create file mapping object (%d).\n"),
                GetLastError());

        }
        else {
            std::cout << "The Shared Memory :"<< SHARED_::MemoryName <<" was created" << std::endl;
        }
        SHARED_::hMapFile1 = CreateFileMapping(
            INVALID_HANDLE_VALUE,    // use paging file
            NULL,                    // default security
            PAGE_READWRITE,          // read/write access
            0,                       // maximum object size (high-order DWORD)
            SuperSize  ,            // maximum object size (low-order DWORD)
            SHARED_::AddressName);
        if (SHARED_::hMapFile1 == NULL)
        {
            dataAccessed = false;
            _tprintf(TEXT("Could not create file mapping object (%d).\n"),
                GetLastError());

        }
        else {
            std::cout << "The Shared Memory :" << SHARED_::AddressName << " was created" << std::endl;
        }
        // name of mapping object

        std::cout << "im the createor i will set the buffer size" << std::endl;
        creator = true;


    }







    DataBuffer_ = (char*)MapViewOfFile(SHARED_::hMapFile2,   // handle to map object
        FILE_MAP_ALL_ACCESS, // read/write permission
        0,
        0,
        SuperSize);


    if (DataBuffer_ == NULL)
    {
        dataAccessed = false;
        _tprintf(TEXT("Could not map view of file (%d).\n"),
            GetLastError());

        CloseHandle(SHARED_::hMapFile2);


    }
    else {
        hMapFile2 = SHARED_::hMapFile2;

        memcpy_s(MemoryName, 100, SHARED_::MemoryName, 100);
    }

    AddressBuffer_ = (char*)MapViewOfFile(SHARED_::hMapFile1,   // handle to map object
        FILE_MAP_ALL_ACCESS, // read/write permission
        0,
        0,
        SuperSize);


    if (AddressBuffer_ == NULL)
    {
        dataAccessed = false;
        _tprintf(TEXT("Could not map view of file (%d).\n"),
            GetLastError());

        CloseHandle(hMapFile2);


    }
    else {
        hMapFile1 = SHARED_::hMapFile1;

        memcpy_s(MemoryNameAdd, 100, SHARED_::AddressName, 100);
    }



   


  







    // CloseHandle(hMapFile);

}






