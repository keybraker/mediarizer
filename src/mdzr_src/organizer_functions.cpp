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

inline bool replace(std::string &str, const std::string &from, const std::string &to)
{
	size_t start_pos = str.find(from);
	if (start_pos == std::string::npos)
		return false;
	str.replace(start_pos, from.length(), to);
	return true;
}

inline std::vector<std::string> split(std::string types, std::string delimiter)
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

inline int type(const std::filesystem::path &dir_path)
{
	return std::filesystem::is_directory(dir_path)
			   ? 0
			   : std::filesystem::is_regular_file(dir_path)
					 ? 1
					 : -1;
}

inline bool is_in_file_list(bool photo_flag, bool video_flag, std::string type)
{
	if (photo_flag && !video_flag)
	{
		for (auto image_type : image_types)
			if (image_type == type)
				return true;
	}
	else if (!photo_flag && video_flag)
	{
		for (auto video_type : video_types)
			if (video_type == type)
				return true;
	}
	else if (photo_flag && video_flag)
	{
		for (auto image_type : image_types)
			if (image_type == type)
				return true;
		for (auto video_type : video_types)
			if (video_type == type)
				return true;
	}
	return false;
}

inline bool is_file_image(std::string file_name)
{
	for (auto image_type : image_types)
	{
		std::regex rx("^.*\\.(" + image_type + ")$");
		if (std::regex_match(file_name, rx))
			return true;
	}
	return false;
}

inline bool is_file_video(std::string file_name)
{
	for (auto video_type : video_types)
	{
		std::regex rx("^.*\\.(" + video_type + ")$");
		if (std::regex_match(file_name, rx))
			return true;
	}
	return false;
}

inline bool is_file_supported(
	std::filesystem::path file_name,
	bool photo_flag,
	bool video_flag,
	std::vector<std::string> types)
{
	if (std::string(file_name.filename())[0] == '.')
	{
		return false;
	}

	if (photo_flag && !video_flag)
	{
		if (is_file_image(file_name.filename()))
			return true;
	}
	else if (!photo_flag && video_flag)
	{
		if (is_file_video(file_name.filename()))
			return true;
	}
	else if (photo_flag && video_flag)
	{
		if (is_file_image(file_name.filename()))
			return true;
		if (is_file_video(file_name.filename()))
			return true;
	}

	if (types.size())
		for (auto type : types)
		{
			return is_in_file_list(photo_flag, video_flag, type);
		}
	else
	{
		return true;
	}

	return false;
}

std::vector<std::string> files_in_path(
	const std::filesystem::path &dir_path,
	bool photo_flag,
	bool video_flag,
	std::vector<std::string> types,
	bool isRecursive)
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
				std::vector<std::string> files_recursive = files_in_path(entry, photo_flag, video_flag, types, isRecursive);
				files.insert(files.end(), files_recursive.begin(), files_recursive.end());
			}
			else if (type(entry) == 1)
			{
				if (is_file_supported(entry.path(), photo_flag, video_flag, types))
					files.push_back(entry.path());
			}
		}
		break;
	case 1:
		if (is_file_supported(dir_path, photo_flag, video_flag, types))
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
		move_directory += std::string("undetermined");
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

bool move_image_to_directory(
	std::string source_directory,
	std::string move_directory,
	bool delete_flag)
{
	if (move_directory.empty())
		return false;

	std::filesystem::path sourceFile = source_directory;
	std::filesystem::path target = move_directory / sourceFile.filename();
	try // If you want to avoid exception handling, then use the error code overload of the following functions.
	{
		std::filesystem::create_directories(move_directory);										  // Recursively create target directory if not existing.
		std::filesystem::copy_file(sourceFile, target, std::filesystem::copy_options::skip_existing); //overwrite_existing
		if (delete_flag)
			std::filesystem::remove(sourceFile);
		return true;
	}
	catch (std::exception &e)
	{
		std::cout << e.what();
		return false;
	}
}

bool files_metadata_exiv2(
	std::vector<std::string> files,
	std::string move_path,
	bool date_flag,
	bool move_flag,
	bool delete_flag,
	bool verbose_flag)
{
	// #pragma omp parallel for private(i)
	for (auto file : files)
	{
		std::cout << "processing: " << file << std::endl;

		auto image = Exiv2::ImageFactory::open(file);
		assert(image.get() != 0);
		image->readMetadata();

		Exiv2::ExifData &image_exif_data = image->exifData();
		// Exiv2::IptcData &iptcData = image->iptcData();
		// Exiv2::XmpData &xmpData = image->xmpData();

		if (image_exif_data.empty())
		{
			if (verbose_flag)
				std::cout << "-- exif data unavailable for:" << file << std::endl;
			// continue;
			if (move_flag)
				std::cout << "-- moving to undetermined folder" << std::endl;
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
		}

		if (date.empty() && date_flag)
		{
			struct stat fileInfo;
			if (stat(file.c_str(), &fileInfo) != 0)
			{
				std::cout << "error: " << strerror(errno) << '\n';
			}
			else
			{
				std::string date_ctime = std::ctime(&fileInfo.st_ctime);
				replace(date_ctime, "  ", " ");
				std::vector<std::string> date_array = split(date_ctime, " ");

				// Mon Apr 23 11:16:57 2007
				// 2015:03:11 21:31:49

				for (int i = 0; i < 12; i++)
				{
					std::cout << "g_months[i]: " << g_months[i] << std::endl;
					std::cout << std::string::npos << " != " << g_months[i].find(date_array[1]) << std::endl;
					if (g_months[i].find(date_array[1]) != std::string::npos)
					{
						if (i > 9)
						{
							date_array[1] = to_string(i);
						}
						else
						{
							date_array[1] = "0";
							date_array[1] += to_string(i);
						}
						break;
					}
				}

				date = date_array[4] + ":" +
					   date_array[1] + ":" +
					   date_array[2] + " " +
					   date_array[3];
			}
		}
		// Exiv2::ExifData::iterator end = image_exif_data.end();
		// for (Exiv2::ExifData::iterator metadata = image_exif_data.begin(); metadata != end; ++metadata)
		// {
		// }

		if (date.empty() && !move_flag)
			continue;

		move_directory += generate_move_directory(date);
		// create_move_directory(move_directory);
		move_image_to_directory(file, move_directory, delete_flag);
	}

	return true;
}

void file_analyzer(char *path, char *move_path,
				   vector<std::string> types,
				   bool photo_flag,
				   bool video_flag,
				   bool recursive_flag,
				   bool date_flag,
				   bool move_flag,
				   bool write_flag,
				   bool delete_flag,
				   bool duplicate_flag,
				   bool verbose_flag)
{
	auto start_1 = std::chrono::high_resolution_clock::now();
	auto files = files_in_path(path, photo_flag, video_flag, types, recursive_flag);
	auto stop_1 = std::chrono::high_resolution_clock::now();

	auto start_2 = std::chrono::high_resolution_clock::now();
	files_metadata_exiv2(files, std::string(move_path), date_flag, move_flag, delete_flag, verbose_flag);
	auto stop_2 = std::chrono::high_resolution_clock::now();

	auto duration_1 = std::chrono::duration_cast<std::chrono::microseconds>(stop_1 - start_1);
	auto duration_2 = std::chrono::duration_cast<std::chrono::microseconds>(stop_2 - start_2);

	if (verbose_flag)
	{
		std::cout << std::endl
				  << std::left << std::setfill('-') << std::setw(20)
				  << "1. Indexed " << files.size() << " photo/s "
				  << std::left << std::setfill('+') << std::setw(20)
				  << duration_1.count() << " microsecs" << std::endl;
		std::cout << std::left << std::setfill('-') << std::setw(20)
				  << "2. Read " << files.size() << " photo/s "
				  << std::left << std::setfill('+') << std::setw(20)
				  << duration_2.count() << " microsecs" << std::endl;
	}
	return;
}

// std::vector<PhotoInfoClass> linked_list_to_vector(char *path, const char *arguments)
// {
// 	ExifTool *et = new ExifTool();
// 	TagInfo *tag_info = et->ImageInfo(path, arguments, 5);
// 	std::vector<PhotoInfoClass> photo_list;

// 	if (tag_info != NULL)
// 	{
// 		PhotoInfoClass new_photo;
// 		bool first = true;
// 		for (TagInfo *i = tag_info; i; i = i->next)
// 		{
// 			// std::cout << "name: " << i->name << " = 0, value: " << i->value << endl;
// 			if (strcmp(i->name, "FileName") == 0)
// 			{
// 				if (!first)
// 				{
// 					photo_list.push_back(new_photo);
// 				}
// 				else
// 				{
// 					first = false;
// 				}
// 				new_photo = PhotoInfoClass();
// 				new_photo.fileName = std::string(i->value);
// 			}
// 			else if (strcmp(i->name, "FileType") == 0)
// 			{
// 				new_photo.fileType = std::string(i->value);
// 			}
// 			else if (strcmp(i->name, "FileSize") == 0)
// 			{
// 				new_photo.fileSize = std::string(i->value);
// 			}
// 			else if (strcmp(i->name, "ImageSize") == 0)
// 			{
// 				new_photo.fileRes = std::string(i->value);
// 			}
// 			else if (strcmp(i->name, "CreateDate") == 0)
// 			{
// 				new_photo.createDate = std::string(i->value);
// 			}
// 			else if (strcmp(i->name, "ModifyDate") == 0)
// 			{
// 				new_photo.modifyDate = std::string(i->value);
// 			}
// 			else if (strcmp(i->name, "FileModifyDate") == 0)
// 			{
// 				new_photo.modifyDate = std::string(i->value);
// 			}
// 			else if (strcmp(i->name, "Directory") == 0)
// 			{
// 				new_photo.source_directory = std::string(i->value);
// 			}
// 		}
// 		photo_list.push_back(new_photo);
// 		delete tag_info;
// 	}

// 	if (et->LastComplete() <= 0)
// 	{
// 		cerr << "Error executing exiftool!" << endl;
// 	}

// 	char *err = et->GetError();
// 	if (err)
// 		cerr << err;
// 	delete et;

// 	return photo_list;
// }