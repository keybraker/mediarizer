/*****************************************************************
  Organizer.h  -- A simple ISO C++ library to organize and delete
  				  duplicate media files.
*/

#ifndef __ORGANIZER_H
#define __ORGANIZER_H

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
void duplicateCleanerExecution(const char* path, const char* master, char* name);
void duplicateCleaner(const char *path, const char *imagePath, int type);
void duplicateVersion(const char *path);

#endif
