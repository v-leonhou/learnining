#include <iostream>
using namespace std;

void foo(char *ch)
{
    cout<<"calll foo(char*)"<<endl;
}

void foo(int i)
{
    cout<<"called foo(int i)"<<endl;
}


int main()
{
    foo(0);
    // foo(NULL);
    foo(nullptr);
    // std::cout << sizeof(b) <<endl;
    // std::cout << sizeof(c) <<endl;
    // std::cout << sizeof(d) <<endl;
    // cout << sizeof(e) <<endl;

    return 0;
}

