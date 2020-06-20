The ctypes python package can be used to insert c code into python :).  There's some examples of how to do this in the darknet repo.

gcc -shared -o libhello.so -fPIC hello.c

The above line will make a shared object which can be imported into python using its ctypes module.

---------------------------------------

from https://stackoverflow.com/questions/14884126/build-so-file-from-c-file-using-gcc-command-line

To generate a shared library you need first to compile your C code with the -fPIC (position independent code) flag.

gcc -c -fPIC hello.c -o hello.o
This will generate an object file (.o), now you take it and create the .so file:

gcc hello.o -shared -o libhello.so
EDIT: Suggestions from the comments:

You can use

gcc -shared -o libhello.so -fPIC hello.c
