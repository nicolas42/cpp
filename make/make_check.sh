cat $0
clang *.h main.c -Weverything -Wfatal-errors -fsanitize=address
rm *.gch
# ./a.out

