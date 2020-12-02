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

#include "../mdzr_hdr/PhotoInfoClass.h"

const char *g_months[] = {
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

PhotoInfoClass::PhotoInfoClass(void) {}
PhotoInfoClass::PhotoInfoClass(std::string fileNameInput,
							   std::string fileTypeInput,
							   std::string fileSizeInput,
							   std::string fileResInput,
							   std::string source_directoryInput,
							   std::string move_directoryInput,
							   std::string createDateInput,
							   std::string modifyDateInput)
{
	fileName = fileNameInput;
	fileType = fileTypeInput;
	fileSize = fileSizeInput;
	fileRes = fileResInput;
	source_directory = source_directoryInput;
	move_directory = move_directoryInput;
	createDate = createDateInput;
	modifyDate = modifyDateInput;
}

void PhotoInfoClass::calculate_move_directory(std::string move_path)
{
	std::string date, move_path_str = std::string(move_path);

	move_directory = move_path;
	move_directory += "/";

	if (!createDate.empty())
	{
		date = std::string(createDate);
		date.resize(10);
	}
	else if (!modifyDate.empty())
	{
		date = std::string(modifyDate);
		date.resize(10);
	}

	if (date.empty() || date.size() < 10)
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
}

bool PhotoInfoClass::execute_move(void)
{
	if (move_directory.empty())
	{
		return false;
	}
	else
	{
		std::filesystem::path sourceFile = source_directory + "/" + fileName;
		std::filesystem::path target = move_directory / sourceFile.filename();
		try // If you want to avoid exception handling, then use the error code overload of the following functions.
		{
			// std::filesystem::create_directories(move_directory); // Recursively create target directory if not existing.
			std::filesystem::copy_file(sourceFile, target, std::filesystem::copy_options::skip_existing); //overwrite_existing
			return true;
		}
		catch (std::exception &e) // Not using fs::filesystem_error since std::bad_alloc can throw too.
		{
			std::cout << e.what();
			return false;
		}
	}
}

bool PhotoInfoClass::execute_folder_creation(void)
{
	if (move_directory.empty())
	{
		return false;
	}
	else
	{
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
}

T &operator=(T &&other) noexcept // move assignment
{
	if (this != &other)
	{												   // no-op on self-move-assignment (delete[]/size=0 also ok)
		delete[] mArray;							   // delete this storage
		mArray = std::exchange(other.mArray, nullptr); // leave moved-from in valid state
		size = std::exchange(other.size, 0);
	}
	return *this;
}
