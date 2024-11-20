collatz: collatz.c cache.c
	gcc -o collatz collatz.c cache.c -Wall -Wextra -O2

clean:
	rm -f collatz
