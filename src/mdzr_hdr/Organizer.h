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

#include <exiv2/exiv2.hpp>

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

inline void version(void)
{
    std::cout << "Mediarizer Version: 2.0.0" << std::endl
              << "A project by Keybraker (https://github.com/keybraker)" << std::endl
              << "License - Released under the GNU LICENSE (https://www.gnu.org/philosophy/free-sw.html)" << std::endl
              << "Copyrights © Keybraker 2020, All rights reserved" << std::endl;
}

inline void help(void)
{
    std::cout << "There are three modes to choose from:" << std::endl
              << "=====================================" << std::endl
              << std::endl
              << "1. File Mode" << std::endl
              << " ./mediarizer /path/media.file /path/to/store/folder" << std::endl
              << std::endl

              << "2. Folder Mode" << std::endl
              << " ./mediarizer /source/path/folder /path/to/store/folder" << std::endl
              << std::endl

              // << "3. Duplication Cleaning Mode" << std::endl
              // << " ./mediarizer -d /source/path/folder" << std::endl << std::endl

              << "Flags:" << std::endl
              << "======" << std::endl
              << std::endl
              << "flag name  "
              << " | flag acronym "
              << " | Argument     "
              << " | Description                                                              " << std::endl
              << "-input     "
              << " | -i           "
              << " | path / file  "
              << " | gives path to file or directory                                        " << std::endl
              << "-output    "
              << " | -o           "
              << " | path         "
              << " | path to output directory                                               " << std::endl
              << "-type      "
              << " | -t           "
              << " | tp1, tp2, .. "
              << " | organizes *only* given file type(s) (https://exiftool.org/#supported)  " << std::endl
              << "-photo     "
              << " | -p           "
              << " | none         "
              << " | organizes *only* photos                                                " << std::endl
              << "-video     "
              << " | -f           "
              << " | none         "
              << " | organizes *only* videos                                                " << std::endl
              << "-recursive "
              << " | -r           "
              << " | none         "
              << " | recursively process sub-directories                                    " << std::endl
              << "-delete    "
              << " | -x           "
              << " | none         "
              << " | deletes files in source directory                                      " << std::endl
              << "-duplicate "
              << " | -d           "
              << " | none         "
              << " | duplicates are moved into duplicate folder in move directory           " << std::endl
              << "-help      "
              << " | -h           "
              << " | none         "
              << " | displays a usage guide of Mediarizer                                   " << std::endl
              << "-version   "
              << " | -v           "
              << " | none         "
              << " | displays current version                                               " << std::endl
              << "-verbose   "
              << " | -s           "
              << " | none         "
              << " | outputs execution information while running                            " << std::endl
              << std::endl

              << "a. Multiple flags can be used in conjunction" << std::endl
              << "b. Multiple file types (https://exiftool.org/#supported) can be used as comma-separated string ex: -type jpg,png" << std::endl
              << "c. Duplicate photos are compared by type, size, date and resolution, only than are they categorized as same" << std::endl;
}

std::string get_date_path(char *date);
std::vector<PhotoInfoClass> linked_list_to_vector(char *path);
void *calculate_move_directory(PhotoInfo photo_info, char *move_path);
void file_analyzer(char *path, char *move_path, const char *arguments);

std::vector<std::string> files_in_path(const std::filesystem::path &dir_path, bool isRecursive);
bool files_metadata_exiv2(std::vector<std::string> files, std::string move_path);

#endif