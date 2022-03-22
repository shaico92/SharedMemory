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

    auto fc = mem.GetAllElements<Wawa>(Structs_enum::Wawa_);

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
     string name = "affff";
     strcpy_s(wc.name, 100, name.c_str());


     mem.AddToBuffer<Wawa>(obj, Structs_enum::Wawa_);
     obj.s = 41;
     mem.AddToBuffer<WithChars>(wc, Structs_enum::WithChars_t);
     mem.AddToBuffer<Wawa>(obj, Structs_enum::Wawa_);
        _gettc;
     auto f=mem.GetAllElements<Wawa>(Structs_enum::Wawa_);
      f = mem.GetAllElements<Wawa>(Structs_enum::Wawa_);




      



      while (true)
      {

      }
    // mem.AddToBuffer<Wawa2>(arr, 5,Structs_enum::Wawa_2);
    // mem.AddToBuffer<Wawa2>(typeTwo, Structs_enum::Wawa_2);
    // mem.AddToBuffer<Wawa>(obdj, Structs_enum::Wawa_);
    //auto tf= mem.GetAllElements<Wawa>(Structs_enum::Wawa_);
    // tf = mem.GetAllElements<Wawa>(Structs_enum::Wawa_);
 

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
