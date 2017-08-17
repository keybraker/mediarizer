CXX=g++
CXXFLAGS=-O2 -pedantic -Wall -Wextra -ansi -std=c++11

############################################################################################################################################
# NORMAL VERSION

all: organizer

organizer: organizerFiles/organizer.cpp
	$(CXX) $(CXXFLAGS) -o organizer organizerFiles/organizer.cpp organizerFiles/organizerFunctions.cpp

run:
	./organizer /Users/Keybraker/github

############################################################################################################################################
# CLEANING
clean:
	rm -f *.o organizer organizer.exe corruptedFiles.txt