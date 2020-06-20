src contains object files which are compiled to lib.a
examples and demos contain main functions which use lib.a

Make lib.a

	make

Compile other stuff

	clang demos/mandelbrot_main.c lib.a -Isrc

Run the thing, test it

	./a.out
	open mandelbrot.ppm


Once lib.a is created it can be reused obviously.

All together now.

run(){
    clang lib.a -Isrc $@ ; ./a.out
}

# run demos/mandelbrot_main.c
# run a.c

push()
{
	git add . ; git status ; git commit -m '$1' ; git push
}
