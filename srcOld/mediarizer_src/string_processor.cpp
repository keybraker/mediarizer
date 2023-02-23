//------------------------------------------------------------------------------
// File:        string_manipulation.cpp
//
// Description: String manipulation functions that help at file ordering.
//
// License:     Copyright 2017-2020, Ioannis Tsiakkas (iantsiakkas at gmail.com)
//
//              This is software, in whole or part, is free for use in
//              non-commercial applications, provided that this copyright notice
//              is retained.  A licensing fee may be required for use in a
//              commercial application.
//
// Created:     08-12-2020 - Ioannis Tsiakkas
//------------------------------------------------------------------------------

#include "../mediarizer_hdr/processor.h"

std::string g_months[12] = {
	"January",
	"February",
	"March",
	"April",
	"May",
	"June",
	"July",
	"August",
	"September",
	"October",
	"November",
	"December"};

std::string image_types[26] = {
	"jpeg", "jpg", "exv", "cr2",
	"crw", "mrw", "tiff", "webp",
	"dng", "nef", "pef", "arw",
	"rw2", "sr2", "srw", "orf",
	"png", "pgf", "raf", "eps",
	"xmp", "gif", "psd", "tga",
	"bmp", "jp2"};

std::string video_types[26] = {
	"jpeg", "jpg", "exv", "cr2",
	"crw", "mrw", "tiff", "webp",
	"dng", "nef", "pef", "arw",
	"rw2", "sr2", "srw", "orf",
	"png", "pgf", "raf", "eps",
	"xmp", "gif", "psd", "tga",
	"bmp", "jp2"};

bool replace(std::string &str, const std::string &from, const std::string &to)
{
	size_t start_pos = str.find(from);
	if (start_pos == std::string::npos)
		return false;
	str.replace(start_pos, from.length(), to);
	return true;
}

std::vector<std::string> split(std::string types, std::string delimiter)
{
	std::vector<std::string> vector_of_types;
	size_t pos = 0;
	while ((pos = types.find(delimiter)) != std::string::npos)
	{
		vector_of_types.push_back(types.substr(0, pos));
		types.erase(0, pos + delimiter.length());
	}
	types.erase(std::remove(types.begin(), types.end(), '\n'), types.end());
	vector_of_types.push_back(types);
	return vector_of_types;
}

int type(const std::filesystem::path &dir_path)
{
	return std::filesystem::is_directory(dir_path)
			   ? 0
			   : std::filesystem::is_regular_file(dir_path)
					 ? 1
					 : -1;
}

void version(void)
{
	std::cout << "Mediarizer Version: 2.0.0" << std::endl
			  << "A project by Keybraker (https://github.com/keybraker)" << std::endl
			  << "License - Released under the GNU LICENSE (https://www.gnu.org/philosophy/free-sw.html)" << std::endl
			  << "Copyrights © Keybraker 2020, All rights reserved" << std::endl;
}
void help(void)
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
			  << " | -v           "
			  << " | none         "
			  << " | organizes *only* videos                                                " << std::endl
			  << "-recursive "
			  << " | -r           "
			  << " | none         "
			  << " | recursively process sub-directories                                    " << std::endl
			  << "-date      "
			  << " | -D           "
			  << " | none         "
			  << " | if image has no exif date filesystem data is used                      " << std::endl
			  << "-move      "
			  << " | -m           "
			  << " | none         "
			  << " | move photos that have no metadata to to undetermined folder            " << std::endl
			  << "-write     "
			  << " | -w           "
			  << " | none         "
			  << " | will add exif data to image that has none                              " << std::endl
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
			  << " | -V           "
			  << " | none         "
			  << " | displays current version                                               " << std::endl
			  << "-verbose   "
			  << " | -s           "
			  << " | none         "
			  << " | outputs execution information while running                            " << std::endl
			  << std::endl

			  << "a. Multiple flags can be used in conjunction" << std::endl
			  << "b. Multiple file types can be used as comma-separated string ex: -type jpg,png" << std::endl
			  << "   1. image: https://dev.exiv2.org/projects/exiv2/wiki/Supported_image_formats" << std::endl
			  << "   2. video: https://dev.exiv2.org/projects/exiv2/wiki/Supported_video_formats" << std::endl
			  << "c. Duplicate photos are compared by type, size, date and resolution, only than are they categorized as same" << std::endl;
}