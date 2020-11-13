#include <math.h>
#include <vector>
#include <string>
#include <iostream>
#include <vector>
#include <stdio.h>

// typedef unsigned long long u64;
// typedef signed long long s64;
// typedef unsigned int u32;
// typedef signed int s32;
// typedef unsigned short u16;
// typedef signed short s16;
// typedef unsigned char u8;
// typedef signed char s8;



double calculate_escape_velocity(double m, double r){
    double G,v,v_kmh; // m,G,r,v, v_kmh;
    // m = 5.972e24;
    G = 6.67e-11;
    // r = 6371e3;
    v = sqrt( 2 * G * m / r );
    return v;
}

std::vector<int> factorize(int n)
{
    int i;
    i = 2;
    std::vector<int> factors;

    while (i * i <= n) {
        if (n % i) { 
            i += 1; 
        } else { 
            n /= i;
            factors.push_back(i);
        }
    }

    if (n > 1) {
        factors.push_back(n);
    }

    return factors;
}


int calculate_escape_velocity_main(int argc, char** argv){

  double m,r;
  double v, v_kmh;

  // earth
  m = 5.972e24;
  r = 6371e3;

  if ( argc == 3 ){
    std::cout << "woo\n";
    sscanf(argv[1], "%lf", &m);
    sscanf(argv[2], "%lf", &v);
  }
  v = calculate_escape_velocity(m,r);
  v_kmh = v * 3.6;

  std::string buff;
  buff += "m = 5.972e24;\n";
  buff += "G = 6.67e-11;\n";
  buff += "r = 6371e3;\n";
  buff += "1/2 v^2 = G m / r\n";
  buff += "v = sqrt( 2 * G * m / r );\n";
  buff += "\n";
  buff += "You need to jump upwards at ";
  buff += std::to_string(v_kmh);
  buff += "km/h to completely leave Earth!\n";
  buff += "The energy of attraction of another body is inversely proportional\n";
  buff += "to the distance you are away from it.\n";

  std::cout << buff;

  return 0;
}

int factorize_main(int argc, char** argv){

  for (auto i : factorize(2009)){
    std::cout << i << " ";
  }
  return 0;
}






int escape_chars_main(int argc, char** argv){
  std::string s = "\
\n\
m = 5.972e24;\n\
G = 6.67e-11;\n\
r = 6371e3;\n\
v = sqrt( 2 * G * m / r );\n\
\n\
You need to jump upwards at %.2f km/h to completely leave Earth!\n\
The energy of attraction of another body is inversely proportional\n\
to the distance you are away from it.\n\
\n\
";

  std::cout << s;
  return 0;
}




int vector_to_array_main(int argc, char** argv){


  auto factors = factorize(2009);
  int* a = &factors[0];
  int la = factors.size();

  printf("Factors of 2009: ");
  for (int i=0; i<la; i+=1){
    printf("%d ", a[i]);
  }
  printf("\n");


  double m,r;
  double v, v_kmh;
  // earth
  m = 5.972e24;
  r = 6371e3;
  v = calculate_escape_velocity(m,r);
  v_kmh = v * 3.6;


  std::vector<std::string> b = { 
    "m = 5.972e24;\n",
    "G = 6.67e-11;\n",
    "r = 6371e3;\n",
    "1/2 v^2 = G m / r\n",
    "v = sqrt( 2 * G * m / r );\n",
    "\n",
    "You need to jump upwards at ",
    std::to_string(v_kmh),
    " km/h to completely leave Earth!\n",
    "\n",
    "The energy of attraction of another body is inversely proportional\n",
    "to how far it is away from you.\n"
  };

  for ( auto i : b ) {
    std::cout << i;
  }
  // std::cout << b;
/*
  std::string s = "";
  for(auto i : a) {
    s += std::to_string(i); 
    s += " ";
  }
  std::cout << s;
  // printf("Factors of 2009 are [%s]\n", s.c_str());
*/
  return 0;
}


int convert_strings_and_vectors_main(int argc, char** argv){

  // A c string can be converted to a cpp string with the std::string constructor
  // After this the += operator can be used to quickly join strings together.
  // The original char pointer must be constant or c++ will throw an error.

  const char* c = "Hello";
  std::string cpp;

  cpp = std::string(c);

  cpp += " World!\n";
  std::cout << cpp;



  double a[] = {12,3,123,12,3,123,12,3};
  int la = 8;
  for (int i=0; i<la; i+=1){ std::cout << a[i] << " "; } std::cout << "\n";

  std::vector<std::string> words1 = {"the", "frogurt", "is", "also", "cursed"};
  std::string buff;
  for (auto i:words1){ buff += i; buff += " "; } buff += "\n";
  std::cout << buff;


  return 0;
}


