o=./objfiles

output: createDir ${o}/main.o ${o}/list.o ${o}/introPage.o ${o}/circle.o ${o}/constants.o ${o}/utils.o ${o}/circleSys.o ${o}/vector.o
	gcc -o output ./objfiles/* -lglut -lGLU -lGL -lm

createDir:
	mkdir -p ./objfiles

${o}/main.o: main.c
	gcc -c main.c -o ${o}/main.o

${o}/list.o: ./lib/list.c
	gcc  -o ${o}/list.o -c ./lib/list.c

${o}/introPage.o: ./lib/introPage.c
	gcc -c ./lib/introPage.c -o ${o}/introPage.o

${o}/circleSys.o: ./lib/circleSys.c
	gcc -c ./lib/circleSys.c -o ${o}/circleSys.o

${o}/utils.o: ./lib/utils.c
	gcc -c ./lib/utils.c  -o ${o}/utils.o

${o}/constants.o: ./lib/constants.c 
	gcc -c ./lib/constants.c -o ${o}/constants.o

${o}/circle.o: ./lib/circle.c
	gcc -c ./lib/circle.c  -o ${o}/circle.o

${o}/vector.o: ./lib/vector.c 
	gcc -c ./lib/vector.c -o ${o}/vector.o

clean:
	find . -name '*.o' -delete