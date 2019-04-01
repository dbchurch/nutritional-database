nutritiondiary:	main.c functions.c
	gcc -Wall -std=c11 -o main main.c functions.c

clean:
	rm -f  main