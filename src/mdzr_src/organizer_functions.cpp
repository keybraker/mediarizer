//------------------------------------------------------------------------------
// File:        organizer_functions.cpp
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

#include "../mdzr_hdr/Organizer.h"
#include "../mdzr_hdr/PhotoInfoClass.h"

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

bool isDir(const char *path)
{
	struct stat sb;
	if (stat(path, &sb) == 0 && S_ISDIR(sb.st_mode))
		return true;
	return false;
}

int isFile(const char *path)
{
	struct stat path_stat;
	stat(path, &path_stat);
	return S_ISREG(path_stat.st_mode);
}

std::vector<PhotoInfoClass> linked_list_to_vector(char *path, const char *arguments)
{
	ExifTool *et = new ExifTool();
	TagInfo *tag_info = et->ImageInfo(path, arguments, 5);
	std::vector<PhotoInfoClass> photo_list;

	if (tag_info != NULL)
	{
		PhotoInfoClass new_photo;
		bool first = true;
		for (TagInfo *i = tag_info; i; i = i->next)
		{
			// std::cout << "name: " << i->name << " = 0, value: " << i->value << endl;
			if (strcmp(i->name, "FileName") == 0)
			{
				if (!first)
				{
					photo_list.push_back(new_photo);
				}
				else
				{
					first = false;
				}
				new_photo = PhotoInfoClass();
				new_photo.fileName = std::string(i->value);
			}
			else if (strcmp(i->name, "FileType") == 0)
			{
				new_photo.fileType = std::string(i->value);
			}
			else if (strcmp(i->name, "FileSize") == 0)
			{
				new_photo.fileSize = std::string(i->value);
			}
			else if (strcmp(i->name, "ImageSize") == 0)
			{
				new_photo.fileRes = std::string(i->value);
			}
			else if (strcmp(i->name, "CreateDate") == 0)
			{
				new_photo.createDate = std::string(i->value);
			}
			else if (strcmp(i->name, "ModifyDate") == 0)
			{
				new_photo.modifyDate = std::string(i->value);
			}
			else if (strcmp(i->name, "FileModifyDate") == 0)
			{
				new_photo.modifyDate = std::string(i->value);
			}
			else if (strcmp(i->name, "Directory") == 0)
			{
				new_photo.source_directory = std::string(i->value);
			}
		}
		photo_list.push_back(new_photo);
		delete tag_info;
	}

	if (et->LastComplete() <= 0)
	{
		cerr << "Error executing exiftool!" << endl;
	}

	char *err = et->GetError();
	if (err)
		cerr << err;
	delete et;

	return photo_list;
}

void file_analyzer(char *path, char *move_path, const char *arguments)
{
	auto start0 = std::chrono::high_resolution_clock::now();

	std::vector<PhotoInfoClass> photo_list = linked_list_to_vector(path, arguments);
	if (photo_list.empty())
	{
		return;
	}

	auto stop0 = std::chrono::high_resolution_clock::now();
	auto duration0 = std::chrono::duration_cast<std::chrono::microseconds>(stop0 - start0);

	std::cout << "1. Processed " << photo_list.size() << " photo(s)"
			  << std::setw(50 - 20 - std::to_string(photo_list.size()).length())
			  << " | " << duration0.count()
			  << std::setw(20 - std::to_string(duration0.count()).length())
			  << " microsecs" << endl;

	auto start = std::chrono::high_resolution_clock::now();

	int i;
	// #pragma omp parallel for private(i)
	for (i = 0; i < (int)photo_list.size(); ++i)
	{
		// #pragma omp task
		photo_list[i].calculate_move_directory(move_path);
		// #pragma omp taskwait
	}

	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

	std::cout << "2. Calculated move directory for " << photo_list.size() << " photo(s)"
			  << std::setw(50 - 40 - std::to_string(photo_list.size()).length())
			  << " | " << duration.count()
			  << std::setw(20 - std::to_string(duration.count()).length())
			  << " microsecs" << endl;

	auto start1 = std::chrono::high_resolution_clock::now();

	std::set<std::string> unique_paths;
	for (i = 0; i < (int)photo_list.size(); ++i)
	{
		long unsigned int num_of_uniques = unique_paths.size();
		unique_paths.insert(photo_list[i].move_directory);
		if (unique_paths.size() > num_of_uniques)
		{
			try
			{
				std::filesystem::create_directories(photo_list[i].move_directory);
			}
			catch (std::exception &e)
			{
				std::cout << e.what() << std::endl;
			}
		}
	}

	auto stop1 = std::chrono::high_resolution_clock::now();
	auto duration1 = std::chrono::duration_cast<std::chrono::microseconds>(stop1 - start1);

	std::cout << "3. Created " << unique_paths.size() << " unique move path(s)"
			  << std::setw(50 - 29 - std::to_string(unique_paths.size()).length())
			  << " | " << duration1.count()
			  << std::setw(20 - std::to_string(duration1.count()).length())
			  << " microsecs" << endl;

	auto start2 = std::chrono::high_resolution_clock::now();

	// #pragma omp parallel for private(i)
	for (i = 0; i < (int)photo_list.size(); ++i)
	{
		// #pragma omp task
		photo_list[i].execute_move();
		// #pragma omp taskwait
	}

	auto stop2 = std::chrono::high_resolution_clock::now();
	auto duration2 = std::chrono::duration_cast<std::chrono::microseconds>(stop2 - start2);

	std::cout << "4. Moved " << photo_list.size() << " photo(s)"
			  << std::setw(50 - 16 - std::to_string(photo_list.size()).length())
			  << " | " << duration2.count()
			  << std::setw(20 - std::to_string(duration2.count()).length())
			  << " microsecs" << endl;
	return;
}