CXX=g++
CXXFLAGS=-O2 -pedantic -Wall -Wextra -ansi -std=c++11

############################################################################################################################################
# EXECUTABLE

all: organizer

organizer: OrganizerFiles/Organizer.cpp
	$(CXX) $(CXXFLAGS) -o mediaOrganizer OrganizerFiles/Organizer.cpp OrganizerFiles/OrganizerFunctions.cpp

############################################################################################################################################
# CLEANING
clean:
	rm -f *.o mediaOrganizer mediaOrganizer.exe corruptedFiles.txt detailedTransfer.txt folderSigning.txt folderSigningDuplicate.txt duplicatesToDelete.txt