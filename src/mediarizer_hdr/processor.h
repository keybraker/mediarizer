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
#include <regex>
#include <exception>
#include <filesystem>
#include <fstream>
#include <iostream>

#include <exiv2/exiv2.hpp>

using namespace std;

typedef struct
{
    int input_flag;
    int output_flag;
    int photo_flag;
    int video_flag;
    int type_flag;
    int recursive_flag;
    int date_flag;
    int move_flag;
    int write_flag;
    int delete_flag;
    int duplicate_flag;
    int verbose_flag;
} flag_struct;

// string_processor.cpp
extern std::string g_months[12];
extern std::string image_types[26];
extern std::string video_types[26];
bool replace(std::string &str, const std::string &from, const std::string &to);
std::vector<std::string> split(std::string types, std::string delimiter);
int type(const std::filesystem::path &dir_path);
void version(void);
void help(void);

// file_processor.cpp
bool is_in_file_list(bool photo_flag, bool video_flag, std::string type);
bool is_file_image(std::string file_name);
bool is_file_video(std::string file_name);
bool is_file_supported(std::filesystem::path file_name, bool photo_flag, bool video_flag, std::vector<std::string> types);
std::vector<std::string> files_in_path(const std::filesystem::path &dir_path, flag_struct &flags, vector<std::string> types);
std::string generate_move_directory(std::string date);
bool create_move_directory(std::string move_directory);
bool move_image_to_directory(std::string source_directory, std::string move_directory, bool delete_flag);

// meta_processor.cpp
bool files_metadata_exiv2(std::vector<std::string> files, std::string move_path);
void file_analyzer(char *path, char *move_path, flag_struct &flags, vector<std::string> types);

#endif