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

string  dateOfCreation  (const char *path);
int     is_regular_file (const char *path);
originalDateData *dateReturn(string originalDate);
void    jpegVersion     (const char *path);
void    folderVersion   (const char *path);

#endif
