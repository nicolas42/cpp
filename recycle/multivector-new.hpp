#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <iostream>
#include <vector>

namespace multivector {
    
void mul(double* c, double* a, double* b)
{

    // multivector product in R3
    // c.e0     =   +a.e0*b.e0  +a.e1*b.e1  +a.e2*b.e2  +a.e3*b.e3  -a.e12*b.e12 -a.e23*b.e23 -a.e31*b.e31 -a.e123*b.e123;
    // c.e1     =   +a.e0*b.e1  +a.e1*b.e0  -a.e2*b.e12  +a.e3*b.e31  +a.e12*b.e2 -a.e23*b.e123 -a.e31*b.e3 -a.e123*b.e23;
    // c.e2     =   +a.e0*b.e2  +a.e1*b.e12  +a.e2*b.e0  -a.e3*b.e23  -a.e12*b.e1 +a.e23*b.e3 -a.e31*b.e123 -a.e123*b.e31;
    // c.e3     =   +a.e0*b.e3  -a.e1*b.e31  +a.e2*b.e23  +a.e3*b.e0  -a.e12*b.e123 -a.e23*b.e2 +a.e31*b.e1 -a.e123*b.e12;
    // c.e12    =   +a.e0*b.e12  +a.e1*b.e2  -a.e2*b.e1  +a.e3*b.e123  +a.e12*b.e0 -a.e23*b.e31 +a.e31*b.e23 +a.e123*b.e3;
    // c.e23    =   +a.e0*b.e23  +a.e1*b.e123  +a.e2*b.e3  -a.e3*b.e2  +a.e12*b.e31 +a.e23*b.e0 -a.e31*b.e12 +a.e123*b.e1;
    // c.e31    =   +a.e0*b.e31  -a.e1*b.e3  +a.e2*b.e123  +a.e3*b.e1  -a.e12*b.e23 +a.e23*b.e12 +a.e31*b.e0 +a.e123*b.e2;
    // c.e123   =   +a.e0*b.e123  +a.e1*b.e23  +a.e2*b.e31  +a.e3*b.e12  +a.e12*b.e3 +a.e23*b.e1 +a.e31*b.e2 +a.e123*b.e0;    

    // "All the pieces matter" - Lester Freamon

    // double* c = (double*)(malloc(8 * sizeof(double)));
    for (size_t i = 0; i < 8; i++)
    {
        c[i] = 0;
    }
    c[0]   =   +a[0]*b[0]  +a[1]*b[1]  +a[2]*b[2]  +a[3]*b[3]  -a[4]*b[4] -a[5]*b[5] -a[6]*b[6] -a[7]*b[7];
    c[1]   =   +a[0]*b[1]  +a[1]*b[0]  -a[2]*b[4]  +a[3]*b[6]  +a[4]*b[2] -a[5]*b[7] -a[6]*b[3] -a[7]*b[5];
    c[2]   =   +a[0]*b[2]  +a[1]*b[4]  +a[2]*b[0]  -a[3]*b[5]  -a[4]*b[1] +a[5]*b[3] -a[6]*b[7] -a[7]*b[6];
    c[3]   =   +a[0]*b[3]  -a[1]*b[6]  +a[2]*b[5]  +a[3]*b[0]  -a[4]*b[7] -a[5]*b[2] +a[6]*b[1] -a[7]*b[4];
    c[4]   =   +a[0]*b[4]  +a[1]*b[2]  -a[2]*b[1]  +a[3]*b[7]  +a[4]*b[0] -a[5]*b[6] +a[6]*b[5] +a[7]*b[3];
    c[5]   =   +a[0]*b[5]  +a[1]*b[7]  +a[2]*b[3]  -a[3]*b[2]  +a[4]*b[6] +a[5]*b[0] -a[6]*b[4] +a[7]*b[1];
    c[6]   =   +a[0]*b[6]  -a[1]*b[3]  +a[2]*b[7]  +a[3]*b[1]  -a[4]*b[5] +a[5]*b[4] +a[6]*b[0] +a[7]*b[2];
    c[7]   =   +a[0]*b[7]  +a[1]*b[5]  +a[2]*b[6]  +a[3]*b[4]  +a[4]*b[3] +a[5]*b[1] +a[6]*b[2] +a[7]*b[0];    
    // return c;
}


std::string str(double* a)
{
    std::string o = "[ ";
    for (size_t i = 0; i < 8; i++)
    {
        if ( trunc(i) - i < 1e-10 ) {
            o += std::to_string(int(a[i]));
        } else {
            o += std::to_string(a[i]);
        }
        o += " ";
    }
    o += "]";
    return o;
}


int factorial(int a)
{
    int r=1;
    for (int i=1; i<=a; i+=1 ){
        r *= i;
    }
    return r;
}

int ncr(int n, int k)
{
    // n!/k!/(n-k)!
    return factorial(n) / factorial(k) / factorial(n-k);

}

void ncr_demo()
{
    std::cout << ncr(3,0) << "\n";
    std::cout << ncr(3,1) << "\n";
    std::cout << ncr(3,2) << "\n";
    std::cout << ncr(3,3) << "\n";

}

int bubble_sort(std::vector<double> arr)
{
    int n = arr.size();
    int number_of_swaps = 0;
    
    for (int i=0; i<n-1; i+=1){
        for (int j=0; j<n-i-1; j+=1){

            for (auto i:arr){ std::cout << i << " "; }
            std::cout << "\n";

            if (arr[j] > arr[j+1]){
                number_of_swaps += 1;
                int swap = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = swap;
            }
        }
    }
    return number_of_swaps;
}



void main()
{


    double a[] = {0, 1,0,0, 0,0,0, 0};
    double b[] = {0, 0,1,0, 0,0,0, 0};
    double c[] = {0, 0,0,0, 0,0,0, 0};
    mul(c, a,b);

    std::cout << str(c) << std::endl;
    // free(c);


}



} // end namespace multivector
