// CA2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Header.h"

#include "../structs_lib/temp.h"
#include "../structs_lib/temp2.h"
#include "../structs_lib/SmthingElse.h"




int main()
{

    MemoryManager mem;
    mem.AccessSharedMemory("fff");



     Wawa obj;
     obj.s = 51;
     obj.t = 420;

     Wawa2 typeTwo;
     typeTwo.ds = 55.151;
     typeTwo.lt = 64586461;
     Wawa obdj;

     obdj.s = 555;
   //  obdj.t = 369;

     Wawa2 arr[5];
     for (size_t i = 0; i < 5; i++)
     {
         arr[i].ds = 0.511651 + i;
         arr[i].lt = 3434 + i;

     }


     WithChars wc;
     wc.id = 143;
  
     strcpy_s(wc.name, 100, name.c_str());


     mem.AddToBuffer<Wawa>(obj, Types::Wawa_);

     mem.AddToBuffer<Wawa>(obj,Types::Wawa_);

     mem.AddToBuffer<WithChars>(wc, Types::WithChars_t);
     mem.AddToBuffer<Wawa2>(arr, Types::Wawa_2,5);
     mem.AddToBuffer<Wawa2>(typeTwo, Types::Wawa_2);
     mem.AddToBuffer<Wawa>(obdj, Types::Wawa_);
    auto tf= mem.printObjectsOfType<Wawa>( Types::Wawa_);

    auto tff = mem.printObjectsOfType<WithChars>(Types::WithChars_t);

    auto tff_ptr = mem.printObjectsOfTypePtr<WithChars>(Types::WithChars_t);
   
    auto tfk = mem.printObjectsOfType<Wawa2>(Types::Wawa_2);
 

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
