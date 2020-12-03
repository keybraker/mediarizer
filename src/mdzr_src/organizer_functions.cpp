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

std::vector<PhotoInfoClass> linked_list_to_vector(char *path)
{
	ExifTool *et = new ExifTool();
	TagInfo *tag_info = et->ImageInfo(path, NULL, 5);
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

void file_analyzer(char *path, char *move_path)
{
	auto start0 = std::chrono::high_resolution_clock::now();

	std::vector<PhotoInfoClass> photo_list = linked_list_to_vector(path);

	auto stop0 = std::chrono::high_resolution_clock::now();
	auto duration0 = std::chrono::duration_cast<std::chrono::microseconds>(stop0 - start0);

	std::cout << "processed " << photo_list.size() << " photos in\t\t\t\t" << duration0.count() << " ms" << endl;

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

	std::cout << "calculated move path in\t\t\t\t" << duration.count() << " ms" << endl;

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
				std::cout << e.what();
			}
		}
	}

	auto stop1 = std::chrono::high_resolution_clock::now();
	auto duration1 = std::chrono::duration_cast<std::chrono::microseconds>(stop1 - start1);

	std::cout << "created " << unique_paths.size() << " unique move paths in\t\t\t" << duration1.count() << " ms" << endl;

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

	std::cout << "moved " << photo_list.size() << " photos\t\t\t\t\t" << duration2.count() << " ms" << endl;

	return;
}