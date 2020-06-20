cat $0
clang -c -Isrc `ls src/*.c `
ar rcs lib.a *.o
rm *.o
