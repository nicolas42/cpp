#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdarg.h>


namespace multivector {

#define length 8
typedef double* T;
static unsigned int size = 8 * sizeof(double);

T init(void);
T scalar(double arg);
T vector(double a, double b, double c);
T bivector(double a, double b, double c);
T trivector(double arg);
T vector_spherical(double r, double theta, double phi);

T geometric_product(T a, T b);
T mul(int num, ...);

T rotate(T v, T a, T b);
T rot(T a, T b);

void print(T a);
void print_scalar(T a);
void print_vector(T a);
void print_bivector(T a);
void print_trivector(T a);

void arena_make(size_t cap);
T arena_allocate(void);
void arena_recycle(void);
void arena_free(void);
int main(void);

static T arena;
static size_t arena_size;
static size_t arena_allocated;


// === Arena Allocator =============

void arena_make(size_t n)
{
    arena_size = 0;
    arena_allocated = n * size;
    arena = (T)malloc(arena_allocated * size);
}

T arena_allocate(void)
{
    T offset = arena + arena_size * size;

    // realloc on overflow
    if (arena_size + size > arena_allocated){
        arena_allocated *= 2;
        arena = (T)realloc(arena, arena_allocated * size);
    }

    arena_size += size;
    return offset;
}

void arena_recycle(void)
{
    arena_size = 0;
}

void arena_free(void)
{
    free(arena);
}

// ===================================

T init(void)
{
    T a = arena_allocate();
    for (size_t i = 0; i < length; i++) { a[i] = 0; }
    return a;
}


T scalar(double arg)
{
    T a = arena_allocate();
    for (size_t i = 0; i < length; i++) { a[i] = 0; }
    a[0] = arg;
    return a;
}

T vector(double a, double b, double c)
{
    T arr = arena_allocate();
    for (size_t i = 0; i < length; i++) { arr[i] = 0; }
    arr[1] = a;
    arr[2] = b;
    arr[3] = c;
    return arr;
}

T bivector(double a, double b, double c)
{
    T arr = arena_allocate();
    for (size_t i = 0; i < length; i++) { arr[i] = 0; }
    arr[4] = a;
    arr[5] = b;
    arr[6] = c;
    return arr;
}

T trivector(double arg)
{
    T a = arena_allocate();
    for (size_t i = 0; i < length; i++) { a[i] = 0; }
    a[7] = arg;
    return a;
}


T geometric_product(T a, T b)
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

    T c = arena_allocate();
    for (size_t i = 0; i < length; i++)
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

T mul(int num, ...)
{

   va_list valist;
   T result = scalar(1);
   int i;

   /* initialize valist for num number of arguments */
   va_start(valist, num);

   /* access all the arguments assigned to valist */
   for (i = 0; i < num; i++) {
      result = geometric_product(result, va_arg(valist, T));
   }
	
   /* clean memory reserved for valist */
   va_end(valist);

   return result;
}

T rotate(T v, T a, T b)
{
    // Rotate v by twice the angle between a and b;
    return mul(5, b,a,v,a,b);
}

T rot(T a, T b)
{
    // rotate a by twice the angle between itself and b
    return mul(5,b,a,a,a,b);
}

T vector_spherical(double r, double theta, double phi)
{
    // Spherical coordinates
    // x = cos(theta)*sin(phi); y = cos(theta-90)*sin(phi); z = cos(phi); 
    return vector(
        r*cos(theta)*sin(phi), 
        r*sin(theta)*sin(phi), 
        r*cos(phi)
    );
}

void print(T a)
{

    printf("multivector( ");
    for (size_t i = 0; i < length; i++)
    {
        printf("%.3f ", a[i]);
    }
    printf(")\n");
}

void print_scalar(T a)
{
    printf( "scalar( %.3f )\n", a[0] );
}

void print_vector(T a)
{
    printf( "vector( %.3f %.3f %.3f )\n", a[1],a[2],a[3]);
}

void print_bivector(T a)
{
    printf( "bivector( %.3f %.3f %.3f )\n", a[4],a[5],a[6]);
}

void print_trivector(T a)
{
    printf( "trivector( %.3f )\n", a[7]);
}

#undef length


int main(void)
{
    #define TAU 6.28318530718

    // #include "multiline_string_literal.h"
    // printf("%s", multiline_string_literal);

    arena_make(1000);

    T v = vector(1,0,0);
    T a = vector(1,0,0);
    T b = vector(1/sqrt(2),1/sqrt(2),0);
    // T c;
    T r;
    T spinor;
    T spinor1;
    T spinor2;

    puts("\
    length\n\
    multiplying two vectors which have the same direction is equivalent to dotting them together\n\
    It gives the length squared\n");

    puts("r = mul(2, vector(1,1,0), vector(1,1,0));");
    r = mul(2, vector(1,1,0), vector(1,1,0));
    print_scalar(r);
    puts(""); getchar();


    puts("\
    In spherical coordinates (r,theta,phi) where TAU = 2*Pi\n");

    puts("r = mul(2, vector_spherical(1, TAU/8, TAU/4), vector_spherical(1, TAU/8, TAU/4));");    
    r = mul(2, vector_spherical(1, TAU/8, TAU/4), vector_spherical(1, TAU/8, TAU/4));
    print_scalar(r);
    puts(""); getchar(); 
    
    puts("\
    Area\n\
    Multiplying two vectors which are orthogonal to each other will give the area of the rectangle\n");

    puts("r = mul(2, vector(1,0,0), vector(0,1,0));");    
    r = mul(2, vector(1,0,0), vector(0,1,0));
    print_bivector(r);
    puts(""); getchar();
    
    puts("\
    Here we have two vectors in spherical coordinates.\n\
    Multiplying them gives the dot product and the wedge product (similar to the cross product.\n");

    puts("r = mul(2, vector_spherical(1, TAU/8, TAU/8), vector_spherical(1, TAU/4, TAU/4));");
    r = mul(2, vector_spherical(1, TAU/8, TAU/8), vector_spherical(1, TAU/4, TAU/4));
    print(r);
    puts(""); getchar();

    puts("\
    volume\n\
    Volume works great but you get a trivector\n");

    puts("r = mul(3, vector(1,0,0), vector(0,1,0), vector(0,0,1));");    
    r = mul(3, vector(1,0,0), vector(0,1,0), vector(0,0,1));
    print_trivector(r);
    puts(""); getchar();

    puts("\n");
    
    puts("r = mul(3, vector_spherical(1, TAU/8, TAU/4), vector_spherical(1, 3*TAU/8, TAU/4), vector(0,0,1));");
    r = mul(3, vector_spherical(1, TAU/8, TAU/4), vector_spherical(1, 3*TAU/8, TAU/4), vector(0,0,1));
    print_trivector(r);
    puts(""); getchar();

    puts("A trivector is also known as a pseudoscalar since it's a single number\n");
    puts("but it squares to give a negative scalar\n");
    puts("\n");
    puts("\n");
    puts("2D rotation (complex numbers)\n");
    puts("A vector can be rotated by multiplying it by a bivector\n");
    puts("A bivector works like a complex number\n");
    
    puts("r = mul(2, vector(1,0,0), bivector(1,0,0)); \n");
    r = mul(2, vector(1,0,0), bivector(1,0,0)); 
    print_vector(r);
    puts(""); getchar();

    puts("\n");
    
    puts("spinor = mul(2, vector(1,0,0), vector_spherical(1, TAU/12, TAU/4));");
    puts("r = mul(2, vector(1,0,0), spinor);");
    spinor = mul(2, vector(1,0,0), vector_spherical(1, TAU/12, TAU/4));
    r = mul(2, vector(1,0,0), spinor);
    print_vector(r);

    puts("\n");
    puts("\n");
    puts("3D rotation work in this way apparently\n");
    puts("To rotate a vector 'v' in the arc from vector 'a' to vector 'b'\n");
    puts("multiply(b,a,v,a,b);\n");
    puts("This will rotate v by twice the angle between a and b\n");
    puts("v = vector(1,0,0);\n");
    puts("a = vector_spherical(1, TAU/8, TAU/4);\n");
    puts("b = vector_spherical(1, TAU/8, TAU/8);\n");
    puts("r = mul(5, b,a,v,a,b);\n");

    v = vector(1,0,0);
    a = vector_spherical(1, TAU/8, TAU/4);
    b = vector_spherical(1, TAU/8, TAU/8);
    r = mul(5, b,a,v,a,b);

    print_vector(r);
    puts("\n");
    puts("Does it work just multiplying on one side? Not generally I think.\n");
    puts("spinor1 = mul(2, vector(1,0,0), vector_spherical(1,TAU/8,TAU/4))\n");
    puts("spinor2 = mul(2, vector(1,0,0), vector_spherical(1,TAU/8,TAU/4))\n");
    puts("mul(3, vector(1,0,0), spinor1, spinor2);\n");

    spinor1 = mul(2, vector(1,0,0), vector_spherical(1,TAU/8,TAU/4));
    spinor2 = mul(2, vector(1,0,0), vector_spherical(1,TAU/8,TAU/4));
    mul(3, vector(1,0,0), spinor1, spinor2);

    puts("\n");
    puts("chirality???\n");
    puts("r = mul(2, trivector(3), trivector(4));\n");
    r = mul(2, trivector(3), trivector(4));
    print(r);
    
    arena_free();

    return 0;

    #undef TAU

}

}