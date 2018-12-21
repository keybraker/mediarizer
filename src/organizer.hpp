/*************************************************************
  Organizer.h  -- A simple C++ library to organize and delete
  				  duplicate media files.
*/

#ifndef __ORGANIZER_H
#define __ORGANIZER_H

#include <sys/types.h>
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
#include <time.h>   
#include <sys/stat.h>
#include <string>
#include <pthread.h>
#include <iomanip>
#include <stdlib.h>
#include <ctime>

#define a_c_r   "\x1b[31m"
#define a_c_g   "\x1b[32m"
#define a_c_y   "\x1b[33m"
#define a_c_b   "\x1b[34m"
#define a_c_m   "\x1b[35m"
#define a_c_c   "\x1b[36m"
#define a_c_re    "\x1b[0m"
#define under   "\e[4m"
#define under_re  "\e[0m"
#define italic    "\e[3m"
#define italic_re "\e[0m"
#define bold    "\e[1m"
#define bold_re   "\e[0m"

#define ACBO  "\033[1m"
#define ACR   "\x1b[31m"
#define ACG   "\x1b[32m"
#define ACY   "\x1b[33m"
#define ACBL  "\x1b[36m"
#define ACRE  "\x1b[0m"

using namespace std;

#define exit_err(FILE, LINE, ERR) \
{ \
  fprintf(stderr, a_c_r "ERROR: %-30s" a_c_re " | [%-20s, %-5d]\n", ERR, FILE, LINE); \
  exit(EXIT_FAILURE); \
}

#define prnt_scs(FILE, LINE, MSG) \
{ \
  fprintf(stdout, "SUCCS: " a_c_g "%-30s" a_c_re " | [%-20s, %-5d]\n", MSG, FILE, LINE); \
}

#define prnt_inf(FILE, LINE, MSG) \
{ \
  fprintf(stdout, "MESSG: " a_c_y "%-30s" a_c_re " | [%-20s, %-5d]\n", MSG, FILE, LINE); \
}

typedef struct originalDateData originalDateData;
typedef struct threader threader;

struct threader{
	const char *source;
	const char *dest;

};

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
void percentige();



void folderSigning(const char* string, int version);
bool folderAlreadyOrganized(const char* string, int version);

string exec(const char* cmd);
void *transfer(threader *threaderer);

string dateOfCreation (const char *path);
bool isDir(const char* path);
int isFile(const char *path);
originalDateData *dateReturn(string originalDate);

char *destinationFinder(int year, int month, const char *pathToStore);
bool typeOfFile(const char* path);
int typeOfFileInt(const char* path);
inline bool existance(const string& name);

void fileVersion (const char *path, const char *pathToStore);
void folderVersion(const char *path, const char *pathToStore, int *arg);

int  duplicateFoundChecker(const char* string);
void duplicateFound(const char* string);
void duplicateRmer(void);
void duplicateVersion(const char *path, int xtrm);
void duplicateCleaner(const char *master, const char *path, int type);
void duplicateCleanerExecution(const char* imagePathMaster, const char* imagePathCandidate);

#endif

