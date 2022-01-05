
#include "Header.h"

#include "../structs_lib/temp.h"
#include "../structs_lib/temp2.h"
#include <stdio.h>
void my_int_func(int x)
{
    printf("%d\n", x);
}

int main()
{
    
    void (*foo)(int);
    /* the ampersand is actually optional */
    foo = &my_int_func;
    
    foo(214);
    MemoryManager mem;
    mem.setBufferSize(1000);
    mem.AccessSharedMemory("fff");

    //mem.GetBuffer();

    

    while (true)
    {
      //  auto tf = mem.printObjectsOfType<Wawa2>(Types::Wawa_2);
    }
    std::cout << "exiting";
    return 0;


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
