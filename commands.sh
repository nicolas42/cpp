run(){
        make ; clang $1 lib.a -Isrc ; ./a.out
}

# run demos/mandelbrot_main.c
# run a.c

push(){
	git add . ; git status ; git commit -m $1 ; git push
}
