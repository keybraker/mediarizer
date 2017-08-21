/*************************************************************
  Organizer.h  -- A simple C++ library to organize and delete
  				  duplicate media files.
*/

#ifndef __ORGANIZER_H
#define __ORGANIZER_H

#include <string>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h> 
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <cassert>
#include <fcntl.h>
#include <errno.h>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <array>
#include <sys/stat.h>

#define ACBO  "\033[1m"
#define ACR   "\x1b[31m"
#define ACG   "\x1b[32m"
#define ACY   "\x1b[33m"
#define ACBL  "\x1b[36m"
#define ACRE  "\x1b[0m"

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

void help();
////////////////////////////////////
int hundredPercent(const char* path);
void percentige(int version);

void detailedFile(const char* string);
void folderSigning(const char* string, int version);
bool folderAlreadyOrganized(const char* string, int version);

string exec(const char* cmd);
int transfer (char *source, char *dest);

string dateOfCreation (const char *path);
bool isDir(const char* path);
int isFile (const char *path);
originalDateData *dateReturn(string originalDate);

bool typeOfFile(const char* path);
int typeOfFileInt(const char* path);
char *destinationFinder(int year, int month, const char *pathToStore);

void fileVersion (const char *path, const char *pathToStore);
void folderVersion(const char *path, const char *pathToStore, int *arg);
void duplicateVersion(const char *path);
void duplicateCleaner(const char *master, const char *path, int type);
void duplicateCleanerExecution(const char* imagePathMaster, const char* imagePathCandidate);

#endif

