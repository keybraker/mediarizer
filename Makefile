CXX=g++
CXXFLAGS=-O2 -pedantic -Wall -Wextra -ansi -std=c++11

############################################################################################################################################
# NORMAL VERSION

all: Organizer

Organizer: OrganizerFiles/Organizer.cpp
	$(CXX) $(CXXFLAGS) -o Organizer OrganizerFiles/Organizer.cpp OrganizerFiles/OrganizerFunctions.cpp

run:
	./Organizer /Users/Keybraker/github

############################################################################################################################################
# CLEANING
clean:
	rm -f *.o Organizer Organizer.exe corruptedFiles.txt