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

inline int type(const std::filesystem::path &dir_path)
{
	return std::filesystem::is_directory(dir_path)
			   ? 0
			   : std::filesystem::is_regular_file(dir_path)
					 ? 1
					 : -1;
}

std::vector<std::string> files_in_path(const std::filesystem::path &dir_path, bool isRecursive)
{
	std::vector<std::string> files;
	if (dir_path.empty())
		return files;

	switch (type(dir_path))
	{
	case -1:
		return files;
		break;
	case 0:
		for (const auto &entry : std::filesystem::directory_iterator(dir_path))
		{
			if (type(entry) == -1)
			{
				return files;
			}
			else if (type(entry) == 0)
			{
				std::vector<std::string> filesEncapsulated = files_in_path(entry, isRecursive);
				files.insert(files.end(), filesEncapsulated.begin(), filesEncapsulated.end());
			}
			else if (type(entry) == 1)
			{
				if (std::string(entry.path().filename())[0] == '.')
					continue;
				files.push_back(entry.path());
			}
		}
		break;
	case 1:
		if (std::string(dir_path.filename())[0] == '.')
			break;
		files.push_back(dir_path);
		break;
	}

	return files;
}

std::string generate_move_directory(std::string date)
{
	std::string move_directory = "";
	if (date == "")
	{
		move_directory += std::string("Undetermined");
	}
	else
	{
		std::string date_year = date.substr(0, 4);
		std::string date_month = date.substr(date.find(":") + 1, 4);
		int month_number = stoi(date_month);
		std::string date_month_name = g_months[month_number - 1];
		move_directory += date_year + "/" + date_month_name;
	}
	return move_directory;
}

bool create_move_directory(std::string move_directory)
{
	if (move_directory.empty())
		return false;
	try
	{
		// Recursively create target directory if not existing.
		std::filesystem::create_directories(move_directory);
		return true;
	}
	catch (std::exception &e)
	{
		std::cout << e.what();
		return false;
	}
}

bool move_image_to_directory(std::string source_directory, std::string move_directory)
{
	if (move_directory.empty())
		return false;

	std::filesystem::path sourceFile = source_directory;
	std::filesystem::path target = move_directory / sourceFile.filename();
	try // If you want to avoid exception handling, then use the error code overload of the following functions.
	{
		// std::filesystem::create_directories(move_directory); // Recursively create target directory if not existing.
		std::filesystem::copy_file(sourceFile, target, std::filesystem::copy_options::skip_existing); //overwrite_existing
		// std::filesystem::remove(sourceFile);
		return true;
	}
	catch (std::exception &e)
	{
		std::cout << e.what();
		return false;
	}
}

bool files_metadata_exiv2(std::vector<std::string> files, std::string move_path)
{
	// #pragma omp parallel for private(i)
	for (auto file : files)
	{
		Exiv2::Image::AutoPtr image = Exiv2::ImageFactory::open(file);
		assert(image.get() != 0);
		image->readMetadata();

		Exiv2::ExifData &image_exif_data = image->exifData();
		// Exiv2::IptcData &iptcData = image->iptcData();
		// Exiv2::XmpData &xmpData = image->xmpData();

		if (image_exif_data.empty())
		{
			std::cout << "no exif data for image: " << file << std::endl;
			continue;
		}

		std::string date = "";
		std::string move_directory = move_path + "/";

		auto key_pos = image_exif_data.findKey(Exiv2::ExifKey("Exif.Image.DateTime"));
		if (key_pos != image_exif_data.end())
			date = key_pos->value().toString();
		else
		{
			auto key_pos = image_exif_data.findKey(Exiv2::ExifKey("Exif.Image.DateTimeOriginal"));
			if (key_pos != image_exif_data.end())
				date = key_pos->value().toString();
			else
				continue;
		}

		// Exiv2::ExifData::iterator end = image_exif_data.end();
		// for (Exiv2::ExifData::iterator metadata = image_exif_data.begin(); metadata != end; ++metadata)
		// {
		// }

		move_directory += generate_move_directory(date);
		create_move_directory(move_directory);
		move_image_to_directory(file, move_directory);
	}

	return true;
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
	auto start_1 = std::chrono::high_resolution_clock::now();
	auto files = files_in_path(path, true); // add is recursive
	auto stop_1 = std::chrono::high_resolution_clock::now();

	auto start_2 = std::chrono::high_resolution_clock::now();
	files_metadata_exiv2(files, std::string(move_path));
	auto stop_2 = std::chrono::high_resolution_clock::now();

	auto start_3 = std::chrono::high_resolution_clock::now();
	auto stop_3 = std::chrono::high_resolution_clock::now();

	auto start_4 = std::chrono::high_resolution_clock::now();
	auto stop_4 = std::chrono::high_resolution_clock::now();

	auto start_5 = std::chrono::high_resolution_clock::now();
	auto stop_5 = std::chrono::high_resolution_clock::now();

	auto duration_1 = std::chrono::duration_cast<std::chrono::microseconds>(stop_1 - start_1);
	auto duration_2 = std::chrono::duration_cast<std::chrono::microseconds>(stop_2 - start_2);
	auto duration_3 = std::chrono::duration_cast<std::chrono::microseconds>(stop_3 - start_3);
	auto duration_4 = std::chrono::duration_cast<std::chrono::microseconds>(stop_4 - start_4);
	auto duration_5 = std::chrono::duration_cast<std::chrono::microseconds>(stop_5 - start_5);

	std::cout << std::endl
			  << std::left << std::setfill('-') << std::setw(20)
			  << "1. Indexed " << files.size() << " photo/s "
			  << std::left << std::setfill('+') << std::setw(20)
			  << duration_1.count() << " microsecs" << std::endl;
	std::cout << std::left << std::setfill('-') << std::setw(20)
			  << "2. Read " << files.size() << " photo/s "
			  << std::left << std::setfill('+') << std::setw(20)
			  << duration_2.count() << " microsecs" << std::endl;
	std::cout << std::left << std::setfill('-') << std::setw(20)
			  << "3. Read " << files.size() << " metadata "
			  << std::left << std::setfill('+') << std::setw(20)
			  << duration_3.count() << " microsecs" << std::endl;

	return;
}