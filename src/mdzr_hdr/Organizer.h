//------------------------------------------------------------------------------
// File:        Organizer.h
//
// Description: A simple C++ library to organize and delete
//				duplicate media files.
//
// License:     Copyright 2017-2020, Ioannis Tsiakkas (iantsiakkas at gmail.com)
//
//              This is software, in whole or part, is free for use in
//              non-commercial applications, provided that this copyright notice
//              is retained.  A licensing fee may be required for use in a
//              commercial application.
//
// Created:     02-12-2020 - Ioannis Tsiakkas
//------------------------------------------------------------------------------

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
#include <string.h>
#include <pthread.h>
#include <iomanip>
#include <stdlib.h>
#include <ctime>
#include <iostream>
#include <filesystem>
#include <vector>
#include <set>
#include <unordered_set>
#include <omp.h>
#include <algorithm>
#include <chrono>

#include "../exif_hdr/ExifTool.h"
#include "../mdzr_hdr/PhotoInfoClass.h"

#define a_c_r "\x1b[31m"
#define a_c_g "\x1b[32m"
#define a_c_y "\x1b[33m"
#define a_c_b "\x1b[34m"
#define a_c_m "\x1b[35m"
#define a_c_c "\x1b[36m"
#define a_c_re "\x1b[0m"
#define under "\e[4m"
#define under_re "\e[0m"
#define italic "\e[3m"
#define italic_re "\e[0m"
#define bold "\e[1m"
#define bold_re "\e[0m"

#define ACBO "\033[1m"
#define ACR "\x1b[31m"
#define ACG "\x1b[32m"
#define ACY "\x1b[33m"
#define ACBL "\x1b[36m"
#define ACRE "\x1b[0m"

using namespace std;

#define exit_err(FILE, LINE, ERR)                                                           \
	{                                                                                       \
		fprintf(stderr, a_c_r "ERROR: %-30s" a_c_re " | [%-20s, %-5d]\n", ERR, FILE, LINE); \
		exit(EXIT_FAILURE);                                                                 \
	}

#define prnt_scs(FILE, LINE, MSG)                                                              \
	{                                                                                          \
		fprintf(stdout, "SUCCS: " a_c_g "%-30s" a_c_re " | [%-20s, %-5d]\n", MSG, FILE, LINE); \
	}

#define prnt_inf(FILE, LINE, MSG)                                                              \
	{                                                                                          \
		fprintf(stdout, "MESSG: " a_c_y "%-30s" a_c_re " | [%-20s, %-5d]\n", MSG, FILE, LINE); \
	}

typedef struct originalDateData originalDateData;
typedef struct threader threader;

struct threader
{
	const char *source;
	const char *dest;
};

struct originalDateData
{
	int year;
	int month;
	int day;
	int hour;
	int minute;
	int second;
};

void help();

bool isDir(const char *path);
int isFile(const char *path);

std::string get_date_path(char *date);
std::vector<PhotoInfoClass> linked_list_to_vector(char *path);
void *calculate_move_directory(PhotoInfo photo_info, char *move_path);

void fileVersion(const char *path, const char *pathToStore);
void folderVersion(const char *path, const char *pathToStore, int *arg);
void file_analyzer(char *path, char *move_path);

#endif