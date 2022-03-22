#include "pch.h"
#include "Header.h"


void MemoryManager::AccessSharedMemory( std::string theNameForMem) {


    bool dataAccessed = true;



    char theNameAsBuffer[100];

    TCHAR ManagedMemoryName[100];


    size_t newsize = strlen(theNameAsBuffer) + 1;
    theNameForMem = "Global/M" + theNameForMem;

    strcpy_s(theNameAsBuffer, 100, theNameForMem.c_str());

    int stop = 0;
    for (size_t i = 0; i < 100 && theNameAsBuffer[i] != '\0'; i++)
    {
      
        MemoryName[i] = theNameAsBuffer[i];
        stop = i;
    }
    for (size_t i = stop+1; i < 100-stop ; i++)
    {

        MemoryName[i] = '\0';

    }

    //this is Const
    TCHAR AddressBuffer[] = TEXT("Global/MyMap");
    for (size_t i = 0; i < 100 && AddressBuffer[i] != '\0'; i++)
    {
        
        MemoryNameAdd[i] = AddressBuffer[i];

        stop = i;
    }

    for (size_t i = stop+1; i < 100 - stop; i++)
    {

        MemoryNameAdd[i] = '\0';

    }
    







    char* AddressBuffer_;
    char* DataBuffer_;
    hMapFile1 = OpenFileMapping(
        FILE_MAP_ALL_ACCESS,   // read/write access
        FALSE,                 // do not inherit the name
        MemoryNameAdd);

    hMapFile2 = OpenFileMapping(
        FILE_MAP_ALL_ACCESS,   // read/write access
        FALSE,                 // do not inherit the name
       MemoryName);




    bool creator = false;

    if (hMapFile2 == NULL|| hMapFile1 == NULL)
    {
        std::cout << "The Shared Memory Name could not be found  will now create a new 2 file  mapping to access it" << std::endl;
        hMapFile2 = CreateFileMapping(
            INVALID_HANDLE_VALUE,    // use paging file
            NULL,                    // default security
            PAGE_READWRITE,          // read/write access
            0,                       // maximum object size (high-order DWORD)
            SuperSize,              // maximum object size (low-order DWORD)
            MemoryName);

        if (hMapFile2 == NULL)
        {
            dataAccessed = false;
            _tprintf(TEXT("Could not create file mapping object (%d).\n"),
                GetLastError());

        }
        else {
            std::cout << "The Shared Memory :"<< MemoryName <<" was created" << std::endl;
        }
        hMapFile1 = CreateFileMapping(
            INVALID_HANDLE_VALUE,    // use paging file
            NULL,                    // default security
            PAGE_READWRITE,          // read/write access
            0,                       // maximum object size (high-order DWORD)
            Size,            // maximum object size (low-order DWORD)
            MemoryNameAdd);
        if (hMapFile1 == NULL)
        {
            dataAccessed = false;
            _tprintf(TEXT("Could not create file mapping object (%d).\n"),
                GetLastError());

        }
        else {
            std::cout << "The Shared Memory :" << MemoryNameAdd << " was created" << std::endl;
        }
        // name of mapping object

        std::cout << "im the createor i will set the buffer size" << std::endl;
        creator = true;


    }







    DataBuffer_ = (char*)MapViewOfFile(hMapFile2,   // handle to map object
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
        
       // databugf = DataBuffer_;
        cout << " accessing " << &DataBuffer_ << endl;
        memcpy_s(MemoryName, 100, MemoryName, 100);
    }

    AddressBuffer_ = (char*)MapViewOfFile(hMapFile1,   // handle to map object
        FILE_MAP_ALL_ACCESS, // read/write permission
        0,
        0,
        Size);
    int index = 0;
    if (creator)
    {
        while (index < Size)
        {
            AddressBuffer_[index] = '\0';
            ++index;
        }
    }
    

    if (AddressBuffer_ == NULL)
    {
        dataAccessed = false;
        _tprintf(TEXT("Could not map view of file (%d).\n"),
            GetLastError());

        CloseHandle(hMapFile2);


    }
    else {
      
        //addresbugf = AddressBuffer_;
        cout << " accessing " << &AddressBuffer_ <<endl;

        memcpy_s(MemoryNameAdd, 100, MemoryNameAdd, 100);
    }



   


  







    // CloseHandle(hMapFile);

}






