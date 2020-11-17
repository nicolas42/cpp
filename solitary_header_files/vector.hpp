#include <iostream>

namespace vector {

typedef struct type {
  int allocated;
  int length;
  int size;
  double *data;
} type;

type init(type a)
{
  a.allocated = 10;
  a.length = 0;
  a.size = sizeof(double);
  a.data = (double*)malloc(a.allocated * a.size);
  return a;
}

type maybe_grow(type a)
{
  if ( a.length == a.allocated ) {
    a.allocated *= 2;
    a.data = (double*)realloc(a.data, a.allocated * a.size);
  }
  return a;
}

type append(type a, double b)
{
  a = maybe_grow(a);
  a.data[a.length] = b;
  a.length += 1;
  return a;
}

type print(type a)
{
  for (int i=0; i<a.length; i+=1){
    std::cout << a.data[i] << " ";
  }
  return a;
}
  
void main(){

  vector::type a;
  a = vector::init(a);
  
  for (int i=0; i<20; i+=1){
    a = vector::append(a,i);
  }
  vector::print(a);
}
  
}

