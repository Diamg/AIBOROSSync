CC= g++
CFLAGS = -O4 -Wall 
CFLAGS = -g -Wall

LIBS = -lurbi -ljpeg -lpthread -lrt

ALL: aibo	

aibo: aibo.o
	$(CC) aibo.o -o aibo $(LIBS)

aibo.o: aibo.cpp
	$(CC) $(CFLAGS) -c -o aibo.o aibo.cpp

clean:
	rm -f aibo.o aibo 
