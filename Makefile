CXX=g++
CXXFLAGS=-O2 -pedantic -Wall -Wextra -ansi -std=c++11

all: jpegOrganizer

exif.o: jpegOrganizerFiles/exif.cpp
	$(CXX) $(CXXFLAGS) -c jpegOrganizerFiles/exif.cpp

jpegOrganizer: exif.o jpegOrganizerFiles/jpegOrganizer.cpp
	$(CXX) $(CXXFLAGS) -o jpegOrganizer exif.o jpegOrganizerFiles/jpegOrganizer.cpp jpegOrganizerFiles/jpegOrganizerFunctions.cpp

clean:
	rm -f *.o jpegOrganizer jpegOrganizer.exe