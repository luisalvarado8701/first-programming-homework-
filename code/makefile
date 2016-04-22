OBJS = main.cpp cache.o
CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG) -pedantic
LFLAGS = -Wall $(DEBUG) -pedantic
TARGET = main
$(TARGET) : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o $(TARGET)
cache.o : cache.hh cache.cpp
	$(CC) $(CFLAGS) cache.cpp
clean:
	rm -f *.o *~ $(TARGET)
