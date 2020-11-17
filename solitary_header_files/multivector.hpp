#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdarg.h>


namespace multivector {


typedef double* type;

static const double t = 2*M_PI;

static size_t length;
static size_t allocated;
static type memory;


type allocate(void);

type scalar(double arg);
type vec(double a, double b, double c);
type vec_s(double r, double theta, double phi);
type bivector(double a, double b, double c);
type trivector(double arg);

type geometric_product(type a, type b);
type mul(int num, ...);

void print(type a);

int main(void);


type allocate(void)
{
    const unsigned int multivector_size = 8 * sizeof(double);

    // Initialize globals on first execution.
    length = 0;
    allocated = 10;
    memory = (type)malloc(allocated * multivector_size);



    type new_location = memory + length * multivector_size;

    // realloc on overflow
    if (length > allocated){
        allocated *= 2;
        memory = (type)realloc(memory, allocated * multivector_size);
    }

    length += 1;
    return new_location;
}


// ===================================

type scalar(double arg)
{
    type a = allocate();
    for (size_t i = 0; i < 8; i++) { a[i] = 0; }
    a[0] = arg;
    return a;
}

type vec(double a, double b, double c)
{
    type arr = allocate();
    for (size_t i = 0; i < 8; i++) { arr[i] = 0; }
    arr[1] = a;
    arr[2] = b;
    arr[3] = c;
    return arr;
}



type vec_s(double r = 1, double theta = 0, double phi = t/4)
{
    // Spherical coordinates
    // x = cos(theta)*sin(phi); y = cos(theta-90)*sin(phi); z = cos(phi); 
    return vec(
        r*cos(theta)*sin(phi), 
        r*sin(theta)*sin(phi), 
        r*cos(phi)
    );
}

type bivector(double a, double b, double c)
{
    type arr = allocate();
    for (size_t i = 0; i < 8; i++) { arr[i] = 0; }
    arr[4] = a;
    arr[5] = b;
    arr[6] = c;
    return arr;
}

type trivector(double arg)
{
    type a = allocate();
    for (size_t i = 0; i < 8; i++) { a[i] = 0; }
    a[7] = arg;
    return a;
}


type geometric_product(type a, type b)
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

    type c = allocate();
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
    return c;
}


void print(type a)
{

    printf("multivector( ");
    for (size_t i = 0; i < 8; i++)
    {
        if (abs(trunc(a[i]) - a[i]) < 1e-10){
            printf("%.0f ", a[i]);
        } else {
            printf("%.3f ", a[i]);
        }
        
    }
    printf(")\n");
}


type mul(int num, ...)
{

   va_list valist;
   type result = scalar(1);
   int i;

   /* initialize valist for num number of arguments */
   va_start(valist, num);

   /* access all the arguments assigned to valist */
   for (i = 0; i < num; i++) {
      result = geometric_product(result, va_arg(valist, type));
   }
	
   /* clean memory reserved for valist */
   va_end(valist);

    print(result); printf("\n");

   return result;
}


int main(void)
{

    mul(2, vec(1,1,0), vec(1,1,0));
    mul(2, vec_s(1, t/8, t/4), vec_s(1, t/8, t/4));
    mul(2, vec(1,0,0), vec(0,1,0));
    mul(2, vec_s(1, 0, t/8), vec_s(1, 0, t/4));
    mul(3, vec(1,0,0), vec(0,1,0), vec(0,0,1));
    mul(3, vec(1,0,0), vec(1,0,0), vec_s(1,0,t/8));

    type v, a, b, spinor1, spinor2;

    v = vec(1,0,0);
    a = vec_s(1, t/8, t/4);
    b = vec_s(1, t/8, t/8);
    mul(5, b,a,v,a,b);

    spinor1 = mul(2, vec(1,0,0), vec_s(1,t/8,t/4));
    spinor2 = mul(2, vec(1,0,0), vec_s(1,t/8,t/4));
    mul(3, vec(1,0,0), spinor1, spinor2);

    mul(2, trivector(3), trivector(4));
    

    free(memory);
    return 0;

}


} // end multivector namespace
