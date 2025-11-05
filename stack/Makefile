stack: main.o
	gcc -o stack main.o userlib.o stacklib.o murmurhash.o

main.o: murmurhash.o stacklib.o userlib.o main.c
	gcc -c main.c murmurhash.o stacklib.o userlib.o

userlib.o: murmurhash.o stacklib.o userlib.c
	gcc -c userlib.c murmurhash.o stacklib.o

stacklib.o: murmurhash.o stacklib.c
	gcc -c stacklib.c murmurhash.o

murmurhash.o: murmurhash.c
	gcc -c murmurhash.c