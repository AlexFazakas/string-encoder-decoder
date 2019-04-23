build: encoder.o
	gcc -Wall encoder.o -o encoder
run: encoder
	./encoder
encoder.o: encoder.c
	gcc -Wall -c encoder.c -o encoder.o
clean:
	rm -f encoder.o
	rm -f encoder
