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
				std::cout << endl;
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

	std::cout << "done (processed " << photo_list.size() << " photos)" << endl;
	std::cout << "vectorization: " << duration0.count() << endl;

	auto start = std::chrono::high_resolution_clock::now();

	// std::unordered_set<PhotoInfoClass> setaki;
    // std::copy(photo_list.begin(),
    //         photo_list.end(),
    //         std::inserter(setaki, setaki.end()));
 
    // for (PhotoInfoClass i: setaki) {
	// 	std::cout << "DUO) " << i.fileName << endl;
    // }

	int i;
	#pragma omp parallel for private(i)
	for (i = 0; i < (int)photo_list.size(); ++i)
	{
		cout << photo_list[i];
		#pragma omp task
		photo_list[i].calculate_move_directory(move_path);
		#pragma omp taskwait
		#pragma omp task
		photo_list[i].execute_folder_creation();
		#pragma omp taskwait
		photo_list[i].execute_move();
	}
	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

	// auto start2 = std::chrono::high_resolution_clock::now();
	// #pragma omp parallel
	// #pragma omp single
	// for (PhotoInfoClass photo2 : photo_list)
	// {
	// #pragma omp task firstprivate(photo2)
	// #pragma omp critical(std::cout)
	// 		std::cout << "THREAD " << omp_get_thread_num() << "/" << omp_get_num_threads() << endl;
	// photo2.calculate_move_directory(move_path);
	// }
	// auto stop2 = std::chrono::high_resolution_clock::now();
	// auto duration2 = std::chrono::duration_cast<std::chrono::microseconds>(stop2 - start2);

	std::cout << "copy and move: " << duration.count() << endl;
	// std::cout << "duo: " << duration2.count() << endl;
	// std::cout << duration.count() << "/" << duration2.count() << "=" << duration.count() / duration2.count() << endl;

	return;
}