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

#include "../mediarizer_hdr/processor.h"

bool is_in_file_list(bool photo_flag, bool video_flag, std::string type)
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

bool is_file_image(std::string file_name)
{
	for (auto image_type : image_types)
	{
		std::regex rx("^.*\\.(" + image_type + ")$");
		if (std::regex_match(file_name, rx))
			return true;
	}
	return false;
}

bool is_file_video(std::string file_name)
{
	for (auto video_type : video_types)
	{
		std::regex rx("^.*\\.(" + video_type + ")$");
		if (std::regex_match(file_name, rx))
			return true;
	}
	return false;
}

bool is_file_supported(std::filesystem::path file_name, bool photo_flag, bool video_flag, std::vector<std::string> types)
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

std::vector<std::string> files_in_path(const std::filesystem::path &dir_path, flag_struct &flags, vector<std::string> types)
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
				std::vector<std::string> files_recursive = files_in_path(entry, flags, types);
				files.insert(files.end(), files_recursive.begin(), files_recursive.end());
			}
			else if (type(entry) == 1)
			{
				if (is_file_supported(entry.path(), flags.photo_flag, flags.video_flag, types))
					files.push_back(entry.path());
			}
		}
		break;
	case 1:
		if (is_file_supported(dir_path, flags.photo_flag, flags.video_flag, types))
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
		int month_number = std::stoi(date_month);
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

bool move_image_to_directory(std::string source_directory, std::string move_directory, bool delete_flag)
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