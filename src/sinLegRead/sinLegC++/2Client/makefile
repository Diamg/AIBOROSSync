CC= g++
CFLAGS = -O4 -Wall 
CFLAGS = -g -Wall

LIBS = -lurbi -ljpeg -lpthread -lrt

ALL: sinLeg	

sinLeg: sinLeg.o
	$(CC) sinLeg.o -o sinLeg $(LIBS)

sinLeg.o: sinLeg.cpp
	$(CC) $(CFLAGS) -c -o sinLeg.o sinLeg.cpp

clean:
	rm -f sinLeg.o sinLeg 
