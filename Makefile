all: integral

integral: main.o calculations.o arg_parser.o
	gcc -o integral main.o calculations.o arg_parser.o

main.o: main.c calculations.h arg_parser.h
	gcc -c -o main.o main.c

calculations.o: calculations.c
	gcc -c -o calculations.o calculations.c

arg_parser.o: arg_parser.c
	gcc -c -o arg_parser.o arg_parser.c

clean:
	del -rf *.o *.exe