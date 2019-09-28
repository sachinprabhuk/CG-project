output: main.o ./lib/circle.o ./lib/constants.o ./lib/utils.o ./lib/circleSys.o
	gcc -o output main.o ./lib/constants.o ./lib/circle.o ./lib/utils.o ./lib/circleSys.o -lglut -lGLU -lGL -lm

main.o: main.c
	gcc -c main.c

circleSys.o: ./headers/circleSys.h ./lib/circleSys.c
	gcc -c ./lib/circleSys.c

utils.o: ./headers/utils.h ./lib/utils.c
	gcc -c utils.c

constants.o: ./lib/constants.c ./headers/constants.h
	gcc -c ./lib/constants.c -o

circle.o: ./lib/circle.c ./headers/circle.h
	gcc -c ./lib/circle.c

clean:
	find . -name '*.o' -delete