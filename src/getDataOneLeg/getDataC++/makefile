CC= g++
CFLAGS = -O4 -Wall
CFLAGS = -g -Wall

LIBS = -lurbi -ljpeg -lpthread -lrt

ALL: getData

getData: getData.o
	$(CC) getData.o -o getData $(LIBS)

getData.o: getData.cpp
	$(CC) $(CFLAGS) -c -o getData.o getData.cpp

clean:
	rm -f getData.o getData 
