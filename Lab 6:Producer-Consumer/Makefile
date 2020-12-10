

CC=g++
CFLAGS= -std=c++17 -pthread

#This rule says that each .o file depends on a .cpp file of the same name
%.o: %.cpp
	$(CC) -c -o $@ $< $(CFLAGS) $(DEBUGFLAGS)

ALL: main.o
	$(CC) -o ProducerConsumer SafeBuffer.cpp Event.cpp Semaphore.cpp main.cpp $(CFLAGS) $(DEBUGFLAGS)

DEBUG: DEBUGFLAGS = -DDEBUG
DEBUG: ALL

doc: 
	doxygen Doxyfile
#this is customary and just deletes all .o files
CLEAN:
	rm *.o