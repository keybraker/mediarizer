//------------------------------------------------------------------------------
// File:        Organizer.h
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

#ifndef __PHOTOCLASS_H
#define __PHOTOCLASS_H

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

	// 	PhotoInfoClass& operator=(const PhotoInfoClass& photo_info) {
	//        return *this;
	//    }
};

#endif