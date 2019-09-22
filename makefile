output: main.o ./lib/circle.o
	gcc -o output main.o ./lib/circle.o -lglut -lGLU -lGL

main.o: main.c
	gcc -c main.c

circles.o: ./lib/circle.c ./headers/circle.h
	gcc -c ./lib/circle.c

clean:
	find . -name '*.o' -delete