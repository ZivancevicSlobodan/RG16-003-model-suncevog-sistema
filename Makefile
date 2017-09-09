PROGRAM = solar_system
CC      = gcc
CFLAGS  = -g -std=c99 -Wall -w -I/usr/X11R6/include -I/usr/pkg/include 
LDFLAGS = -L/usr/X11R6/lib -L/usr/pkg/lib
LDLIBS  = -lglut -lGLU -lGL -lm

$(PROGRAM): solar_system.o
	$(CC) $(LDFLAGS) -o $(PROGRAM) solar_system.o $(LDLIBS)

.PHONY: clean dist

clean:
	-rm *.o $(PROGRAM)

dist: clean
	-tar -chvj -C .. -f ../$(PROGRAM).tar.bz2 $(PROGRAM)
