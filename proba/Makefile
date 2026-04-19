program: main.o libusermath.so
	gcc -o gcd main.o -L. -lusermath -Wl,-rpath,.
main.o: main.c
	gcc -c main.c
libusermath.so: usermath.o
	gcc -shared -o libusermath.so usermath.o
usermath.o: usermath.c
	gcc -c -fPIC usermath.c
clean:
	rm -f gcd *.so *.o
