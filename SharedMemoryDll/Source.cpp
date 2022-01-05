#include "pch.h"
#include "Header.h"


void MemoryManager::AccessSharedMemory( std::string theNameForMem) {


    bool dataAccessed = true;



    char theNameAsBuffer[100];

    TCHAR ManagedMemoryName[100];


    size_t newsize = strlen(theNameAsBuffer) + 1;
    theNameForMem = "Local/" + theNameForMem;

    strcpy_s(theNameAsBuffer, 100, theNameForMem.c_str());


    for (size_t i = 0; i < 100 && theNameAsBuffer[i] != '\0'; i++)
    {
        ManagedMemoryName[i] = theNameAsBuffer[i];
        MemoryName[i] = theNameAsBuffer[i];

    }


    HANDLE hMapFile = NULL;
    char* data_;

    hMapFile = OpenFileMapping(
        FILE_MAP_ALL_ACCESS,   // read/write access
        FALSE,                 // do not inherit the name
        ManagedMemoryName);

    bool creator = false;

    if (hMapFile == NULL)
    {
        std::cout << "The Shared Memory Name could not be found  will now create a new file mapping to access it" << std::endl;
        hMapFile = CreateFileMapping(
            INVALID_HANDLE_VALUE,    // use paging file
            NULL,                    // default security
            PAGE_READWRITE,          // read/write access
            0,                       // maximum object size (high-order DWORD)
            Buffer + sizeof(int),                // maximum object size (low-order DWORD)
            ManagedMemoryName);                 // name of mapping object

        std::cout << "im the createor i will set the buffer size" << std::endl;
        creator = true;


        if (hMapFile == NULL)
        {
            dataAccessed = false;
            _tprintf(TEXT("Could not create file mapping object (%d).\n"),
                GetLastError());

        }
    }







    data_ = (char*)MapViewOfFile(hMapFile,   // handle to map object
        FILE_MAP_ALL_ACCESS, // read/write permission
        0,
        0,
        Buffer);


    if (data_ == NULL)
    {
        dataAccessed = false;
        _tprintf(TEXT("Could not map view of file (%d).\n"),
            GetLastError());

        CloseHandle(hMapFile);


    }
    mappHandle = hMapFile;


    char* pBufCopy = data_;

    memcpy_s(pBufCopy, Buffer, data_, Buffer);
    int sizeAlocated = 0;
    if (creator)
    {
        char Unallocated = '-';


        ++pBufCopy;
        int pos = 0;
        int tested = 0;
        for (size_t i = 0; i < Buffer; i++)
        {
            memcpy_s(&pBufCopy[pos], sizeof(char), &Unallocated, sizeof(char));


            memcpy_s(&tested, sizeof(char), &pBufCopy[pos], sizeof(char));
            //  std::cout << "int is " << tested << std::endl;



            pos += sizeof(char);

        }
        //writing size of buffer;
        memcpy_s(pBufCopy, sizeof(int), &Buffer, sizeof(int));



        memcpy_s(data_, Buffer, pBufCopy, Buffer);
        // delete[] pBufCopy;
       //  memcpy_s(pBufCopy, Buffer - (sizeof(unsigned int)), &Unallocated, sizeof(unsigned int));


    }



    memcpy_s(&sizeAlocated, sizeof(int), data_, sizeof(int));
    if (sizeAlocated < 1 && !creator)
    {
        std::cout << "Data Was not set by the creator of the sharedmemory segment" << std::endl;
        dataAccessed = false;
    }







    // CloseHandle(hMapFile);

}


char* MemoryManager::GetBufferStart() {
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
    return data_;
}

char* MemoryManager::GetBuffer() {
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

    char emptyMemory = '-';
    int pos = 0;
    const char memoryNone = '-';
    pos += sizeof(int);


    //if (NULL != UnAllocatedDataPtr)
    //{
    //    return UnAllocatedDataPtr;
    //}
    SizeToCheckForAllocation = sizeof(char) + sizeof(Types) + SizeOfCurrentType + sizeof(char);

    if (NULL!= UnAllocatedDataPtr)
    {
        return UnAllocatedDataPtr;
    }


    for (size_t i = 0; i < Buffer; i++)
    {
        
        memcpy_s(&emptyMemory, sizeof(char), &data_[pos], sizeof(char));
        //     std::cout << emptyMemory << std::endl;
        //std::cout << memcmp(&emptyMemory, &memoryNone, sizeof(int)) << endl;
        int tempPosition = pos;
        if (emptyMemory == memoryNone)
        {
            for (size_t i = 0; i < SizeToCheckForAllocation; i++)
            {
                char current = '-';
                memcpy_s(&current, sizeof(char), &data_[tempPosition], sizeof(char));

                if (current != '-')
                {
                    cout << " memory" << &data_[pos] << " is not valid as empty: " << data_[pos] << endl;
                }
                tempPosition += sizeof(char);
            }


            std::cout << &emptyMemory << ':'<<pos << std::endl;
            UnAllocatedDataPtr = &data_[pos];
            return UnAllocatedDataPtr;
        }


        pos += sizeof(char);
    }
    return NULL;


}

//template <typename T>
//char* MemoryManager::validBufferFormat(char* pbuff, Types typeWanted, bool& IsParsable) {
//
//    //booleans
//
//
//    IsParsable = false;
//    //check if start of object with char 's'
//    Types temp = Types::invalid;
//
//    char Nll = '\0';
//    bool matchingEnums = temp == typeWanted;
//    bool matchEndOfObject = Nll == 'e';
//    bool matchStartOfObject = Nll == 's';
//    //check if start of object with char 's'
//    memcpy_s(&Nll, sizeof(char), pbuff, sizeof(char));
//    if (matchStartOfObject)
//    {
//        cout << "starting object" << endl;
//
//        pbuff += sizeof(char);
//    }
//    //check if enum is in object 
//    memcpy_s(&temp, sizeof(Types), pbuff, sizeof(Types));
//    if (matchingEnums)
//    {
//        cout << "getting enum object" << temp << endl;
//
//        pbuff += sizeof(Types);
//    }
//    //check struct  object 
//
//    T* someType = (T*)pbuff;
//    pbuff += sizeof(T);
//
//    //check struct  object ends with 'e'
//    memcpy_s(&Nll, sizeof(char), pbuff, sizeof(char));
//    if (matchEndOfObject)
//    {
//        cout << "getting  object end" << endl;
//
//        pbuff -= sizeof(T);
//        // pbuff += sizeof(char);
//    }
//
//    //returning charBuffer to the point of the struct
//
//    IsParsable = matchStartOfObject && matchEndOfObject && matchingEnums;
//    return pbuff;
//}
//
//template <typename T>
//std::vector<T> MemoryManager::printObjectsOfType(Types type)
//
//{
//    std::vector<T> allPtrs;
//
//    char* pbuff = GetBufferStart();
//    Types temp = Types::invalid;
//    memcpy_s(&Buffer, sizeof(int), pbuff, sizeof(int));
//    pbuff += sizeof(int);
//    for (int i = 0;i < Buffer; ++i)
//    {
//
//
//
//        bool parsed = false;
//        validBufferFormat<T>(pbuff, type, parsed);
//        if (parsed)
//        {
//            pbuff = validBufferFormat<T>(pbuff, type, parsed);
//            T* someType = (T*)pbuff;
//            allPtrs.push_back(*someType);
//        }
//
//        //   pbuff +=sizeof(char);
//
//
//
//       //    memcpy_s(&temp, sizeof(Types), pbuff, sizeof(Types));
//       //    if (temp==type)
//       //    {
//
//       ///*        std::cout << "about to touch a object" <<temp<< std::endl;
//       //        
//       //       
//       //        pbuff += sizeof(Types);
//
//
//
//       //        T* someType = (T*)pbuff;
//       //        allPtrs.push_back(*someType);*/
//       //      
//       //    }
//          /* pbuff+=sizeof(int);*/
//    }
//
//
//    //    memcpy_s(&someType, sizeof(theType), pbuff, sizeof(theType));
//    return allPtrs;
//
//}
void  MemoryManager::setBufferSize(int size_)
{
    Buffer = size_;
}






MemoryManager* GetTheMemManager() { return new MemoryManager(); }