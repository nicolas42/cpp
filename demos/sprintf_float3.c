/*
Use this if you can't print floats - in an embedded system for example.
*/

#include <stdio.h>
#include <math.h>

void sprint_float3(char* str, float arg){

  // sprint float to 3 decimal places
  // to change decimal places change 1000 and %03d
  // from https://stackoverflow.com/questions/905928/using-floats-with-sprintf-in-embedded-c

  char *sign;
  float val;
  int a;
  int b;

  // arg = 678.0123;

  sign = (arg < 0) ? "-" : "";
  val = (arg < 0) ? -arg : arg;

  a = val;                  // Get the integer (678).
  b = trunc((val - a) * 1000);  // Get fraction then turn into integer (123).

  // Print as parts, note that you need 0-padding for fractional bit.

  if (b == 0){
    sprintf (str, "%s%d", sign, a);
  } else {
    sprintf (str, "%s%d.%03d", sign, a, b);  
  }
  // puts(str);

}


int main(){

  char str[100];

  sprint_float3(str, 0.01234);
  puts(str);
  sprint_float3(str, 3.1415926535);
  puts(str);
  sprint_float3(str, 3234);
  puts(str);

  return 0;
}








