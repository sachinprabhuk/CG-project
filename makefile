output: main.o ./lib/list.o ./lib/circle.o ./lib/constants.o ./lib/utils.o ./lib/circleSys.o ./lib/vector.o
	gcc -o output ./lib/list.o ./lib/vector.o main.o ./lib/constants.o ./lib/circle.o ./lib/utils.o ./lib/circleSys.o -lglut -lGLU -lGL -lm

main.o: main.c
	gcc -c main.c

list.o: ./lib/list.c ./headers/list.h
	gcc -c ./lib/list.c ./headers/list.h

circleSys.o: ./headers/circleSys.h ./lib/circleSys.c
	gcc -c ./lib/circleSys.c ./headers/circleSys.h

utils.o: ./headers/utils.h ./lib/utils.c
	gcc -c ./lib/utils.c ./headers/utils.h

constants.o: ./lib/constants.c ./headers/constants.h
	gcc -c ./lib/constants.c -o ./headers/constants.h

circle.o: ./lib/circle.c ./headers/circle.h
	gcc -c ./lib/circle.c ./headers/circle.h

vector.o: ./lib/vector.c ./headers/vector.h
	gcc -c ./lib/vector.c ./headers/vector.h

clean:
	find . -name '*.o' -delete