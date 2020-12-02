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

const char *g_months2[] = {
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

std::string get_date_path(std::string date)
{
	cout << "ERRORAT=>" << __LINE__ << "/" << date << endl;
	if (date.empty() || date.size() < 10)
		return std::string("Undetermined");

	cout << "ERRORAT=>" << __LINE__ << "/" << date << endl;
	std::string date_year = date.substr(0, 4);
	cout << "ERRORAT=>" << __LINE__ << "/" << date << endl;
	cout << "date.substr(, 2): " << date.substr(date.find_first_of(":") + 1, 2) << endl;
	cout << "stoi(date.substr(5, 2)): " << stoi(date.substr(5, 2)) << endl;
	int month_number = stoi(date.substr(5, 2));
	cout << "ERRORAT=>" << __LINE__ << "/" << date << endl;
	std::string date_month = g_months2[month_number - 1];
	cout << "ERRORAT=>" << __LINE__ << "/" << date << endl;

	return date_year + "/" + date_month;
}

std::vector<PhotoInfoClass> linked_list_to_vector(char *path)
{
	ExifTool *et = new ExifTool();
	TagInfo *tag_info = et->ImageInfo(path, NULL, 5);
	std::vector<PhotoInfoClass> photo_list;

	if (tag_info)
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
				cout << "fileName: " << i->value << endl;
				new_photo.fileName = std::string(i->value);
			}
			else if (strcmp(i->name, "FileType") == 0)
			{
				cout << "FileType" << i->value << endl;
				new_photo.fileType = std::string(i->value);
			}
			else if (strcmp(i->name, "FileSize") == 0)
			{
				cout << "FileSize" << i->value << endl;
				new_photo.fileSize = std::string(i->value);
			}
			else if (strcmp(i->name, "ImageSize") == 0)
			{
				cout << "ImageSize" << i->value << endl;
				new_photo.fileRes = std::string(i->value);
			}
			else if (strcmp(i->name, "CreateDate") == 0)
			{
				cout << "CreateDate" << i->value << endl;
				new_photo.createDate = std::string(i->value);
			}
			else if (strcmp(i->name, "ModifyDate") == 0)
			{
				cout << "ModifyDate" << i->value << endl;
				new_photo.modifyDate = std::string(i->value);
			}
			else if (strcmp(i->name, "FileModifyDate") == 0)
			{
				cout << "FileModifyDate" << i->value << endl;
				new_photo.modifyDate = std::string(i->value);
			}
			else if (strcmp(i->name, "Directory") == 0)
			{
				cout << "Directory" << i->value << endl;
				new_photo.source_directory = std::string(i->value);
			}
		}
		photo_list.push_back(new_photo);
		delete tag_info;
	}
	else if (et->LastComplete() <= 0)
	{
		cerr << "Error executing exiftool!" << endl;
		return photo_list;
	}

	char *err = et->GetError();
	if (err)
		cerr << err;
	delete et;

	return photo_list;
}

void file_analyzer(char *path, char *move_path)
{
	std::cout << "analyzing photos and vectorizing";
	auto start0 = std::chrono::high_resolution_clock::now();

	// std::vector<PhotoInfo> photo_list = linked_list_to_vector(path);
	std::vector<PhotoInfoClass> photo_list = linked_list_to_vector(path);

	auto stop0 = std::chrono::high_resolution_clock::now();
	auto duration0 = std::chrono::duration_cast<std::chrono::microseconds>(stop0 - start0);

	std::cout << "..done (processed " << photo_list.size() << " photos)" << endl;

	auto start = std::chrono::high_resolution_clock::now();

	int i;
	// #pragma omp parallel for private(i)
	for (i = 0; i < (int)photo_list.size(); ++i)
	{
		std::cout << i << ") " << endl;
		cout << "BEFOREPhotoInfo: { " << std::endl
			 << "fileName: " << photo_list[i].fileName << "," << std::endl
			 //  << "fileType: " << photo_list[i].fileType << "," << std::endl
			 //  << "fileSize: " << photo_list[i].fileSize << "," << std::endl
			 //  << "fileRes: " << photo_list[i].fileRes << "," << std::endl
			 << "source_directory: " << photo_list[i].source_directory << "," << std::endl
			 << "move_directory: " << photo_list[i].move_directory << "," << std::endl
			 << "createDate: " << photo_list[i].createDate << "," << std::endl
			 << "modifyDate: " << photo_list[i].modifyDate << "," << std::endl
			 << "}" << std::endl;
		photo_list[i].calculate_move_directory(move_path);
		cout << "AFTERPhotoInfo: { " << std::endl
			 << "fileName: " << photo_list[i].fileName << "," << std::endl
			 //  << "fileType: " << photo_list[i].fileType << "," << std::endl
			 //  << "fileSize: " << photo_list[i].fileSize << "," << std::endl
			 //  << "fileRes: " << photo_list[i].fileRes << "," << std::endl
			 << "source_directory: " << photo_list[i].source_directory << "," << std::endl
			 << "move_directory: " << photo_list[i].move_directory << "," << std::endl
			 << "createDate: " << photo_list[i].createDate << "," << std::endl
			 << "modifyDate: " << photo_list[i].modifyDate << "," << std::endl
			 << "}" << std::endl
			 << std::endl;
	}
	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

	// auto start2 = std::chrono::high_resolution_clock::now();
	// #pragma omp parallel
	// #pragma omp single
	// 	for (PhotoInfo photo2 : photo_list)
	// 	{
	// #pragma omp task firstprivate(photo2)
	// #pragma omp critical(std::cout)
	// 		std::cout << "THREAD " << omp_get_thread_num() << "/" << omp_get_num_threads() << endl;
	// 	}
	// auto stop2 = std::chrono::high_resolution_clock::now();
	// auto duration2 = std::chrono::duration_cast<std::chrono::microseconds>(stop2 - start2);

	std::cout << "mhden: " << duration0.count() << endl;
	std::cout << "ena: " << duration.count() << endl;
	// std::cout << "duo: " << duration2.count() << endl;
	// std::cout << duration.count() << "/" << duration2.count() << "=" << duration.count() / duration2.count() << endl;

	return;
}