rsh: rsh.c
	gcc -g -o rsh -Wall -std=gnu11 rsh.c

myspawn: myspawn.c
	gcc -g -o myspawn -Wall -std=gnu11 myspawn.c

@PHONY: clean

clean:
	rm -f rsh
