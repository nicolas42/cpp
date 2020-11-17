/*
g++ -std=c++11 main.cpp; ./a.out
*/

#include <iostream>

namespace vector {

  typedef struct coordinate {
    int x;
    int y;
  } coordinate;
  
  typedef struct vector {
    int allocated;
    int length;
    int size;
    coordinate* data;
  } vector;

  vector init(vector a)
  {
    a.allocated = 10;
    a.length = 0;
    a.size = sizeof(coordinate);
    a.data = (coordinate*)malloc(a.allocated * a.size);
    return a;
  }

  vector maybe_grow(vector a)
  {
    if ( a.length == a.allocated ) {
      a.allocated *= 2;
      a.data = (coordinate*)realloc(a.data, a.allocated * a.size);
    }
    return a;
  }

  vector append(vector a, coordinate b)
  {
    a = maybe_grow(a);
    a.data[a.length] = b;
    a.length += 1;
    return a;
  }

  vector print(vector a)
  {
    for (int i=0; i<a.length; i+=1){
      std::cout << a.data[i].x << " " <<  a.data[i].y << " ";
    }
    return a;
  }
  
  
}

int main(){

  vector::vector a;
  a = vector::init(a);
  
  for (int i=0; i<20; i+=1){
    vector::coordinate c;
    c.x=1; c.y=2;
    a = vector::append(a,c);
  }
  vector::print(a);

}
