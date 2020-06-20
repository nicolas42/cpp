/*
// compile and run (linux)
g++ main.cpp sha1.cpp -o sha1_sample && ./sha1_sample

source: http://www.zedwood.com/article/cpp-sha1-function
*/

#include <iostream>
#include "sha1.h"
 
using namespace std;
 
int main(int argc, char *argv[])
{
    cout << "sha1('grape'):" << sha1("grape") << endl;
    return 0;
}
