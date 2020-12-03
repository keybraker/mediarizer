//------------------------------------------------------------------------------
// File:		Organizer.h
//
// Description: A simple C++ library to organize and delete
//				duplicate media files.
//
// License:		Copyright 2017-2020, Ioannis Tsiakkas (iantsiakkas at gmail.com)
//
//				This is software, in whole or part, is free for use in
//				non-commercial applications, provided that this copyright notice
//				is retained.  A licensing fee may be required for use in a
//				commercial application.
//
// Created:		02-12-2020 - Ioannis Tsiakkas
//------------------------------------------------------------------------------

#ifndef __PHOTOCLASS_H
#define __PHOTOCLASS_H

#include <exception>
#include <filesystem>
#include <fstream>
#include <iostream>

class PhotoInfoClass
{
	// PhotoInfoClass();
	// virtual ~PhotoInfoClass();
public:
	std::string fileName;		  // file name
	std::string fileType;		  // file type
	std::string fileSize;		  // file size
	std::string fileRes;		  // file resolution
	std::string source_directory; // file directory
	std::string move_directory;	  // file directory
	std::string createDate;		  // date created
	std::string modifyDate;		  // date modified

	PhotoInfoClass &operator=(const PhotoInfoClass &photo_info);
	friend bool operator==(PhotoInfoClass &photo_info_a, PhotoInfoClass &photo_info_b);
	friend bool operator<(PhotoInfoClass &photo_info_a, PhotoInfoClass &photo_info_b);
	friend std::ostream &operator<<(std::ostream &out, const PhotoInfoClass &point);

	PhotoInfoClass(void);
	PhotoInfoClass(std::string fileNameInput,
				   std::string fileTypeInput,
				   std::string fileSizeInput,
				   std::string fileResInput,
				   std::string source_directoryInput,
				   std::string move_directoryInput,
				   std::string createDateInput,
				   std::string modifyDateInput);

	void calculate_move_directory(std::string move_path);
	bool execute_move(void);
	bool execute_date_update(void);
	bool execute_folder_creation(void);
};

#endif