/*
  g++ -std=c++11 main.cpp; ./a.out
*/

#include <iostream>

typedef struct coordinate {
  int x = 0;
  int y = 0;
  int z = 0;
} coordinate;

typedef struct coordinate_array
{
  int allocated = 2;
  int length = 0;
  int size = sizeof(coordinate);
  coordinate* data = (coordinate*)malloc(2 * sizeof(coordinate));
  
} coordinate_array;


coordinate_array coordinate_array_add(coordinate_array a, coordinate b)
{
  if ( a.length == a.allocated ) {
    // grow array
    a.allocated *= 2;
    a.data = (coordinate*)realloc(a.data, a.allocated * a.size);
  }
  a.data[a.length] = b;
  a.length += 1;
  return a;
}


int main(){

  coordinate_array a;
  coordinate c;
  
  for (int i=0; i<10; i+=1){
    c.x=i; c.y=2*i; c.z=3*i;
    a = coordinate_array_add(a,c);
  }

  // print array
  for (int i=0; i<a.length; i+=1){
    std::cout << a.data[i].x << " " <<  a.data[i].y << " " << a.data[i].z << " ";
  }

  free(a.data);
}
