CPP = g++
CCFLAGS = -O3 -pedantic -Wall -Wextra -std=c++1z
CCNAME = -o mediarizer

ifeq ($(OS), Windows_NT)
    CCFLAGS += -D WIN32 -fopenmp
    ifeq ($(PROCESSOR_ARCHITEW6432),AMD64)
        CCFLAGS += -D AMD64
    else
        ifeq ($(PROCESSOR_ARCHITECTURE),AMD64)
            CCFLAGS += -D AMD64
        endif
        ifeq ($(PROCESSOR_ARCHITECTURE),x86)
            CCFLAGS += -D IA32
        endif
    endif
else
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S), Linux)
        CCFLAGS += -D LINUX -fopenmp
    endif
    ifeq ($(UNAME_S), Darwin)
        CCFLAGS += -D OSX -Xclang -fopenmp 
		CCNAME = -lomp -o mediarizer
    endif
    UNAME_P := $(shell uname -p)
    ifeq ($(UNAME_P), x86_64)
        CCFLAGS += -D AMD64
    endif
    ifneq ($(filter %86,$(UNAME_P)),)
        CCFLAGS += -D IA32
    endif
    ifneq ($(filter arm%,$(UNAME_P)),)
        CCFLAGS += -D ARM
    endif
endif

EXIF = -I exif_hdr
MDRZ = -I mdzr_hdr 

OBJ_EXIF = src/exif_src/ExifTool.o src/exif_src/ExifToolPipe.o src/exif_src/TagInfo.o
HDR_EXIF = src/exif_hdr/ExifTool.h src/exif_hdr/ExifToolPipe.h src/exif_hdr/TagInfo.h
OBJ_MDZR = src/mdzr_src/organizer_functions.o src/mdzr_src/photoInfoClass.cpp
HDR_MDZR = src/mdzr_hdr/Organizer.h src/mdzr_hdr/PhotoInfoClass.h

all: organizer

organizer: src/organizer.o $(OBJ_EXIF) $(OBJ_MDZR)
	$(CPP) $(CCFLAGS) $(CCNAME) src/organizer.o $(OBJ_EXIF) $(OBJ_MDZR)

clean:
	rm -f mediarizer src/*.o src/exif_src/*.o src/mdzr_src/*.o \
		corruptedFiles.txt detailedTransfer.txt folderSigning.txt \
		folderSigningDuplicate.txt duplicatesToDelete.txt

%.o: %.cpp $(HDR_EXIF)
	$(CPP) $(CCFLAGS) $(EXIF) -o $@ -c $<

%.o: %.cpp $(HDR_MDZR)
	$(CPP) $(CCFLAGS) $(MDRZ) -o $@ -c $<