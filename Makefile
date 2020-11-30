CPP = g++
OPT = -g -O2 -pedantic -Wall -Wextra -std=c++11 -Xclang -fopenmp

EXIF = -I exif_hdr
MDRZ = -I mdzr_hdr 

OBJ_EXIF = src/exif_src/ExifTool.o src/exif_src/ExifToolPipe.o src/exif_src/TagInfo.o
HDR_EXIF = src/exif_hdr/ExifTool.h src/exif_hdr/ExifToolPipe.h src/exif_hdr/TagInfo.h
OBJ_MDZR = src/mdzr_src/organizer_functions.o
HDR_MDZR = src/mdzr_hdr/organizer.h

all: organizer

organizer: src/organizer.o $(OBJ_EXIF) $(OBJ_MDZR)
	$(CPP) $(OPT) -v -o mediarizer src/organizer.o $(OBJ_EXIF) $(OBJ_MDZR)

clean:
	rm -f mediarizer src/*.o src/exif_src/*.o src/mdzr_src/*.o \
		corruptedFiles.txt detailedTransfer.txt folderSigning.txt \
		folderSigningDuplicate.txt duplicatesToDelete.txt

%.o: %.cpp $(HDR_EXIF)
	$(CPP) $(OPT) $(EXIF) -o $@ -c $<

%.o: %.cpp $(HDR_MDZR)
	$(CPP) $(OPT) $(MDRZ) -o $@ -c $<