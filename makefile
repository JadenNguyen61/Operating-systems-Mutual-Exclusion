CC = g++
CFLAGS = -std=c++11 -pthread

all:  main 

main:  main.cpp  Peterson.cpp  TT.cpp  Peterson.h  TT.h  TAS.h FAI.h
	$(CC) main.cpp Peterson.cpp TT.cpp -o main $(CFLAGS)
  
PetersonAlgo:  Peterson.cpp Peterson.h
	$(CC) main.cpp Peterson.cpp TT.cpp $(CFLAGS)
  
TournamentTree:  TT.cpp TT.h Peterson.h
	$(CC) main.cpp Peterson.cpp TT.cpp $(CFLAGS)
  
clean:
	rm -f main PetersonAlgo TournamentTree

