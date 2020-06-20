run(){
        make ; clang lib.a -Isrc $1 ; ./a.out
}

# run demos/mandelbrot_main.c
# run a.c

push(){
	git add . ; git status ; git commit -m $1 ; git push
}
