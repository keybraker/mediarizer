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

#include <exception>
#include <filesystem>
#include <iostream>
#include <fstream>

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
	PhotoInfoClass &operator==(const PhotoInfoClass &photo_info);

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
	bool execute_folder_creation(void);

	// 	PhotoInfoClass& operator=(const PhotoInfoClass& photo_info) {
	//        return *this;
	//    }
};

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

#endif