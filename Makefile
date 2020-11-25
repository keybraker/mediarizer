CXX=g++
CXXFLAGS=-O2 -pedantic -Wall -Wextra -ansi -std=c++11

############################################################################################################################################
# EXECUTABLE

all: organizer

organizer: src/organizer.cpp
	$(CXX) $(CXXFLAGS) -o mediarizer src/organizer.cpp \
	src/organizer_functions.cpp

############################################################################################################################################
# CLEANING
clean:
	rm -f *.o mediarizer mediarizer.exe corruptedFiles.txt \
	detailedTransfer.txt folderSigning.txt \
	folderSigningDuplicate.txt duplicatesToDelete.txt

run: organizer
	./mediarizer -i /Users/keybraker/Desktop/developer/noteOrdered -o /Users/keybraker/Desktop/developer/ordered