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
        MemoryName[i] = theNameAsBuffer[i];

    }

    //this is Const
    TCHAR AddressBuffer[] = TEXT("Local/MyMap");
    for (size_t i = 0; i < 100 && AddressBuffer[i] != '\0'; i++)
    {
        
        AddressBufferName[i] = AddressBuffer[i];


    }

    







    char* AddressBuffer_;
    char* DataBuffer_;
    HANDLE   hMapFile1 = OpenFileMapping(
        FILE_MAP_ALL_ACCESS,   // read/write access
        FALSE,                 // do not inherit the name
        AddressBufferName);

    HANDLE  hMapFile2 = OpenFileMapping(
        FILE_MAP_ALL_ACCESS,   // read/write access
        FALSE,                 // do not inherit the name
        MemoryName);




    bool creator = false;

    if (hMapFile1 == NULL|| hMapFile2 == NULL)
    {
        std::cout << "The Shared Memory Name could not be found  will now create a new 2 file  mapping to access it" << std::endl;
        hMapFile2 = CreateFileMapping(
            INVALID_HANDLE_VALUE,    // use paging file
            NULL,                    // default security
            PAGE_READWRITE,          // read/write access
            0,                       // maximum object size (high-order DWORD)
    /*DataBuffer*/        SHARED_BUFFER_DATA,                // maximum object size (low-order DWORD)
            MemoryName); 

        if (hMapFile2 == NULL)
        {
            dataAccessed = false;
            _tprintf(TEXT("Could not create file mapping object (%d).\n"),
                GetLastError());

        }
        else {
            std::cout << "The Shared Memory :"<< MemoryName<<" was created" << std::endl;
        }
        hMapFile1 = CreateFileMapping(
            INVALID_HANDLE_VALUE,    // use paging file
            NULL,                    // default security
            PAGE_READWRITE,          // read/write access
            0,                       // maximum object size (high-order DWORD)
            SHARED_ADDRESS_BUFFER,                // maximum object size (low-order DWORD)
            AddressBufferName);
        if (hMapFile1 == NULL)
        {
            dataAccessed = false;
            _tprintf(TEXT("Could not create file mapping object (%d).\n"),
                GetLastError());

        }
        else {
            std::cout << "The Shared Memory :" << AddressBufferName << " was created" << std::endl;
        }
        // name of mapping object

        std::cout << "im the createor i will set the buffer size" << std::endl;
        creator = true;


    }







    DataBuffer_ = (char*)MapViewOfFile(hMapFile2,   // handle to map object
        FILE_MAP_ALL_ACCESS, // read/write permission
        0,
        0,
        SHARED_BUFFER_DATA);


    if (DataBuffer_ == NULL)
    {
        dataAccessed = false;
        _tprintf(TEXT("Could not map view of file (%d).\n"),
            GetLastError());

        CloseHandle(hMapFile2);


    }
    AddressBuffer_ = (char*)MapViewOfFile(hMapFile1,   // handle to map object
        FILE_MAP_ALL_ACCESS, // read/write permission
        0,
        0,
        SHARED_ADDRESS_BUFFER);


    if (AddressBuffer_ == NULL)
    {
        dataAccessed = false;
        _tprintf(TEXT("Could not map view of file (%d).\n"),
            GetLastError());

        CloseHandle(hMapFile2);


    }



   


  







    // CloseHandle(hMapFile);

}






