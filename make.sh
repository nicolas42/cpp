# cat $0
# source commands.sh
for f in `ls src/*.c `; do echo $f ;    clang   -std=c99    -Weverything -c -Isrc $f ; done
for f in `ls src/*.cpp `; do echo $f ;  clang++ -std=c++17  -Weverything -c -Isrc $f ; done
ar rcs lib.a *.o
rm *.o
echo 'created lib.a'