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
#include "../exif_hdr/ExifTool.h"

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

PhotoInfoClass &PhotoInfoClass::operator=(const PhotoInfoClass &photo_info)
{
	if (this != &photo_info)
	{ // self-assignment check expected
		this->fileName = photo_info.fileName;
		this->fileType = photo_info.fileType;
		this->fileSize = photo_info.fileSize;
		this->fileRes = photo_info.fileRes;
		this->source_directory = photo_info.source_directory;
		this->move_directory = photo_info.move_directory;
		this->createDate = photo_info.createDate;
		this->modifyDate = photo_info.modifyDate;
	}
	return *this;
}
bool operator==(const PhotoInfoClass &photo_info_a, const PhotoInfoClass &photo_info_b)
{
	return (photo_info_a.move_directory == photo_info_b.move_directory);
}
bool operator<(const PhotoInfoClass &photo_info_a, const PhotoInfoClass &photo_info_b)
{
	return (photo_info_a.move_directory < photo_info_b.move_directory);
}
std::ostream &operator<<(std::ostream &out, const PhotoInfoClass &photo_info)
{
	out << "PhotoInfo: { " << std::endl
		<< "\t"
		<< "fileName: " << photo_info.fileName << "," << std::endl
		<< "\t"
		<< "fileType: " << photo_info.fileType << "," << std::endl
		<< "\t"
		<< "fileSize: " << photo_info.fileSize << "," << std::endl
		<< "\t"
		<< "fileRes: " << photo_info.fileRes << "," << std::endl
		<< "\t"
		<< "source_directory: " << photo_info.source_directory << "," << std::endl
		<< "\t"
		<< "move_directory: " << photo_info.move_directory << "," << std::endl
		<< "\t"
		<< "createDate: " << photo_info.createDate << "," << std::endl
		<< "\t"
		<< "modifyDate: " << photo_info.modifyDate << "," << std::endl
		<< "}" << std::endl;
	return out;
}

void PhotoInfoClass::calculate_move_directory(std::string move_path)
{
	std::string date, move_path_str = std::string(move_path);

	move_directory = move_path;
	move_directory += "/";

	if (!createDate.empty())
	{
		// date = std::string(createDate);
		date = createDate;
		date.resize(10);
	}
	else if (!modifyDate.empty())
	{
		// date = std::string(modifyDate);
		date = modifyDate;
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
			// std::filesystem::remove(sourceFile);
			return true;
		}
		catch (std::exception &e) // Not using fs::filesystem_error since std::bad_alloc can throw too.
		{
			std::cout << e.what();
			return false;
		}
	}
}
bool PhotoInfoClass::execute_date_update(void)
{
	// create our ExifTool object
	ExifTool *et = new ExifTool();

	// set new values of tags to write
	et->SetNewValue("createDate", createDate.empty() ? createDate.c_str() : modifyDate.c_str());

	// write the information
	std::filesystem::path sourceFile = source_directory + "/" + fileName;
	if (createDate.empty() == true)
		std::cout << sourceFile << " <= " << createDate << std::endl;
	else
		std::cout << sourceFile << " <= " << modifyDate << std::endl;

	et->WriteInfo(sourceFile.c_str());

	// wait for exiftool to finish writing
	int result = et->Complete(10);

	if (result > 0)
	{
		// checking either the number of updated images or the number of update
		// errors should be sufficient since we are only updating one file,
		// but check both for completeness
		int n_updated = et->GetSummary(SUMMARY_IMAGE_FILES_UPDATED);
		int n_errors = et->GetSummary(SUMMARY_FILE_UPDATE_ERRORS);
		if (n_updated == 1 && n_errors <= 0)
		{
			return true;
		}
		else
		{
			return false;
		}
		// print any exiftool messages
		char *out = et->GetOutput();
		if (out)
			std::cout << out;
		char *err = et->GetError();
		if (err)
			std::cerr << err;
	}
	else
	{
		std::cerr << "Error executing exiftool command!" << std::endl;
	}
	delete et;
	return 0;
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