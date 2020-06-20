# cat $0
source commands.sh
for f in `ls src/*.c `; do echo $f ; clang -c -Isrc $f ; done
ar rcs lib.a *.o
rm *.o
