CXX=g++
CXXFLAGS=-O2 -pedantic -Wall -Wextra -ansi -std=c++11

############################################################################################################################################
# EXECUTABLE

all: organizer

organizer: organizerFiles/organizer.cpp
	$(CXX) $(CXXFLAGS) -o mediaOrganizer organizerFiles/organizer.cpp organizerFiles/organizerFunctions.cpp

############################################################################################################################################
# CLEANING
clean:
	rm -f *.o mediaOrganizer mediaOrganizer.exe corruptedFiles.txt