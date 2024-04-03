make:
	gcc -ggdb -Wall -o UnixLs UnixLs.c main.c infodemo.c
clean:
	rm UnixLs