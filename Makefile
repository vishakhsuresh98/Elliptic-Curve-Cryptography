CC = g++ -std=c++11

all: main.o key_struct.o elliptic_curve.o is_prime.o
	$(CC) main.o key_struct.o elliptic_curve.o is_prime.o
main.o: main.cpp key_struct.h is_prime.h elliptic_curve.h
	$(CC) -c main.cpp
elliptic_curve.o: elliptic_curve.cpp elliptic_curve.h
	$(CC) -c elliptic_curve.cpp
is_prime.o: elliptic_curve.cpp elliptic_curve.h
	$(CC) -c is_prime.cpp	
key_struct.o: key_struct.cpp key_struct.h	
	$(CC) -c key_struct.cpp			
clean:
	rm *.o
	rm a.out