//------------------------------------------------------------------------------
// File:        meta_processor.cpp
//
// Description: Metadata manipulation and reading functions that help at
//              file ordering.
//
// License:     Copyright 2017-2020, Ioannis Tsiakkas (iantsiakkas at gmail.com)
//
//              This is software, in whole or part, is free for use in
//              non-commercial applications, provided that this copyright notice
//              is retained.  A licensing fee may be required for use in a
//              commercial application.
//
// Created:     08-12-2020 - Ioannis Tsiakkas
//------------------------------------------------------------------------------

#include "../mediarizer_hdr/processor.h"

bool files_metadata_exiv2(std::vector<std::string> files, std::string move_path, flag_struct &flags)
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
			if (flags.verbose_flag)
				std::cout << "-- exif data unavailable for:" << file << std::endl;
			// continue;
			if (flags.move_flag)
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

		if (date.empty() && flags.date_flag)
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

				for (int i = 0; i < 12; i++)
					if (g_months[i].find(date_array[1]) != std::string::npos)
					{
						if (i > 9)
							date_array[1] = to_string(i);
						else
							date_array[1] = "0" + to_string(i);

						break;
					}

				if (std::stoi(date_array[2]) < 10)
					date_array[2] = "0" + date_array[2];

				date = date_array[4] + ":" +
					   date_array[1] + ":" +
					   date_array[2] + " " +
					   date_array[3];
			}
		}

		if (date.empty() && !flags.move_flag)
			continue;

		move_directory += generate_move_directory(date);
		// create_move_directory(move_directory);
		move_image_to_directory(file, move_directory, flags.delete_flag);
	}

	return true;
}

bool file_analyzer(char *path, char *move_path, flag_struct &flags, vector<std::string> types)
{
	auto start_1 = std::chrono::high_resolution_clock::now();
	auto files = files_in_path(path, flags, types);
	auto stop_1 = std::chrono::high_resolution_clock::now();

	auto start_2 = std::chrono::high_resolution_clock::now();
	files_metadata_exiv2(files, std::string(move_path), flags);
	auto stop_2 = std::chrono::high_resolution_clock::now();

	auto duration_1 = std::chrono::duration_cast<std::chrono::microseconds>(stop_1 - start_1);
	auto duration_2 = std::chrono::duration_cast<std::chrono::microseconds>(stop_2 - start_2);

	if (flags.verbose_flag)
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

	return 0;
}