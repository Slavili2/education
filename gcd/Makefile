
cleanResult:
	rm -f gcd

userMath.o: userMath.c
	gcc -c userMath.c

userLib.o: userLib.c
	gcc -c userLib.c

main.o: main.c
	gcc -c main.c

gcd: main.o userLib.o userMath.o 
	gcc -o gcd main.o userLib.o userMath.o

clean.o:
	rm -f *.o
