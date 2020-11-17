/*
g++ -std=c++11 main.cpp; ./a.out
*/

// #include "lib.hpp"
// #include "opencv_demos.hpp"
#include "multivector.hpp"
#include <iostream>



int main(){

    namespace mv = multivector;
    // multivector::main();

    std::cout << mv::allocated;

    const double t = 2*M_PI;

    mv::type x = mv::vec(1,0,0);

    mv::mul(2, mv::vec(1,1,0), mv::vec(1,1,0));
    mv::mul(2, mv::vec_s(1, t/8, t/4), mv::vec_s(1, t/8, t/4));
    mv::mul(2, x, mv::vec(0,1,0));
    mv::mul(2, mv::vec_s(1, 0, t/8), mv::vec_s(1, 0, t/4));
    mv::mul(3, x, mv::vec(0,1,0), mv::vec(0,0,1));
    mv::mul(3, x, x, mv::vec_s(1,0,t/8));

    mv::type v, a, b, spinor1, spinor2;

    v = x;
    a = mv::vec_s(1, t/8, t/4);
    b = mv::vec_s(1, t/8, t/8);
    mv::mul(5, b,a,v,a,b);

    spinor1 = mv::mul(2, x, mv::vec_s(1,t/8,t/4));
    spinor2 = mv::mul(2, x, mv::vec_s(1,t/8,t/4));
    mv::mul(3, x, spinor1, spinor2);

    mv::mul(2, mv::trivector(3), mv::trivector(4));
    

    free(mv::memory);

}

