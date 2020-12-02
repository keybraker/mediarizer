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

std::ostream &operator<<(std::ostream &os, const PhotoInfoClass &photo_info)
{
	os << "PhotoInfo: { " << std::endl
	   << "fileName: " << photo_info.fileName << "," << std::endl
	   << "fileType: " << photo_info.fileType << "," << std::endl
	   << "fileSize: " << photo_info.fileSize << "," << std::endl
	   << "fileRes: " << photo_info.fileRes << "," << std::endl
	   << "source_directory: " << photo_info.source_directory << "," << std::endl
	   << "move_directory: " << photo_info.move_directory << "," << std::endl
	   << "createDate: " << photo_info.createDate << "," << std::endl
	   << "modifyDate: " << photo_info.modifyDate << "," << std::endl
	   << "}" << std::endl;
	return os;
}