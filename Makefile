CPP = g++
CCFLAGS = -O3 -pedantic -Wall -Wextra -std=c++1z
CCLINK = -I/usr/local/include -L/usr/local/lib -lexiv2
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
		CCLINK += -lomp
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

MDRZ = -I mediarizer_hdr

OBJ_MAIN = src/mediarizer.o
OBJ_MDRZ = src/mediarizer_src/metadata.o # src/mediarizer_src/string.o src/mediarizer_src/file.o
HDR_MDRZ = src/mediarizer_hdr/metadata.h # src/mediarizer_hdr/string.h src/mediarizer_hdr/file.h

# EXIF = -I exif_hdr
# MDRZ = -I mdzr_hdr 

# OBJ_EXIF = src/exif_src/ExifTool.o src/exif_src/ExifToolPipe.o src/exif_src/TagInfo.o
# HDR_EXIF = src/exif_hdr/ExifTool.h src/exif_hdr/ExifToolPipe.h src/exif_hdr/TagInfo.h
# OBJ_MDZR = src/mdzr_src/organizer_functions.o src/mdzr_src/photoInfoClass.cpp
# HDR_MDZR = src/mdzr_hdr/Organizer.h src/mdzr_hdr/PhotoInfoClass.h

all: organizer

organizer: $(OBJ_MAIN) $(OBJ_MDRZ)
	$(CPP) $(CCFLAGS) $(CCNAME) \
	$(OBJ_MAIN) $(OBJ_MDRZ) \
	$(CCLINK)

clean:
	rm -f mediarizer src/*.o src/mediarizer_src/*.o

%.o: %.cpp $(HDR_MDRZ)
	$(CPP) $(CCFLAGS) $(MDRZ) -o $@ -c $<