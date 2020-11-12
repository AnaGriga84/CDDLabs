 #Lab 4 Barriers
 #author Ana Griga , Student Number: C00231441
 #Tutor: Joseph Kehoe
 #version GNU AFFERO GENERAL PUBLIC LICENSE Version 3, 19 November 2007


CC=g++
CFLAGS= -std=c++11 -pthread

#This rule says that each .o file depends on a .cpp file of the same name
%.o: %.cpp
	$(CC) -c -o $@ $< $(CFLAGS) $(DEBUGFLAGS)

ALL: main.o Semaphore.o
	$(CC) -o barriers main.o Semaphore.o $(CFLAGS) $(DEBUGFLAGS)

DEBUG: DEBUGFLAGS = -DDEBUG
DEBUG: ALL

#this is customary and just deletes all .o files
CLEAN:
	rm *.o