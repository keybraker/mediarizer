/*****************************************************************
  jpegOrganizer.h  -- A simple ISO C++ library to parse basic EXIF
                        information from a JPEG file.
*/

#ifndef __JPEGORGANIZER_H
#define __JPEGORGANIZER_H

#include <string>

using namespace std;

typedef struct originalDateData originalDateData;

struct originalDateData{
  int year;
  int month;
  int day;
  int hour;
  int minute;
  int second;
  
};

void detailedFile(const char* string);
int transfer (char *source, char *dest);
string dateOfCreation (const char *path);
int isRegularFile (const char *path);
originalDateData *dateReturn(string originalDate);
bool typeOfFile(const char* path);
int typeOfFileInt(const char* path);
char *destinationFinder(int year, int month, const char *pathToStore);
void fileVersion (const char *path, const char *pathToStore);
void folderVersion(const char *path, const char *pathToStore, int *arg);
void duplicateVersion(const char *path);

#endif
