#include "util.h"
#include <string.h>
#include <stdio.h>
#include <errno.h>

int main(void)
{
    string f = read_file("test.c");
    char* s = f.data;
    char* pos;

    // strtok uses a static for the string after it's initialized
    for (char *p = strtok(s,"\n"); p != NULL; p = strtok(NULL, "\n")){
        printf("{%s}\n", p);
    }
    
    // errno
   FILE *fp;

   fp = fopen("file.txt","r");
   if( fp == NULL ) {
      printf("Error: %s\n", strerror(errno));
   }
   
   return(0);
}