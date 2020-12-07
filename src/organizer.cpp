//------------------------------------------------------------------------------
// File:        organizer.cpp
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

#include "mdzr_hdr/Organizer.h"

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

static int
	input_flag = false,
	output_flag = false,
	photo_flag = false,
	video_flag = false,
	type_flag = false,
	recursive_flag = false,
	date_flag = false,
	move_flag = false,
	write_flag = false,
	delete_flag = false,
	duplicate_flag = false,
	verbose_flag = false;

int main(int argc, char *argv[])
{
	int c, option_index = 0; // getopt_long stores the option index
	char *input = NULL, *output = NULL;
	std::vector<std::string> types;

	while (1)
	{
		static struct option long_options[] = {
			{"input", required_argument, &input_flag, 'i'},
			{"output", required_argument, &output_flag, 'o'},
			{"type", required_argument, &type_flag, 't'},
			{"photo", no_argument, &photo_flag, 'p'},
			{"video", no_argument, &video_flag, 'v'},
			{"recursive", no_argument, &recursive_flag, 'r'},
			{"date", no_argument, &date_flag, 'D'},
			{"move", no_argument, &move_flag, 'm'},
			{"write", no_argument, &write_flag, 'w'},
			{"delete", no_argument, &delete_flag, 'x'},
			{"duplicate", no_argument, &duplicate_flag, 'd'},
			{"help", no_argument, NULL, 'h'},
			{"Version", no_argument, NULL, 'V'},
			{"verbose", no_argument, &verbose_flag, 's'},
			{0, 0, 0, 0}};

		c = getopt_long(argc, argv, "i:o:t:pvrDwxdmhVs", long_options, &option_index);

		if (c == -1)
			break;

		switch (c)
		{
		case 'i':
			std::cout << "input:\t" << optarg << std::endl;
			input_flag = true;
			input = strdup(optarg);
			break;
		case 'o':
			std::cout << "output:\t" << optarg << std::endl;
			output_flag = true;
			output = strdup(optarg);
			break;
		case 't':
			type_flag = true;
			types = split(std::string(strdup(optarg)), ",");
			for (auto type : types)
			{
				for (auto image_type : image_types)
					if (image_type == type)
						break;
				for (auto video_type : video_types)
					if (video_type == type)
						break;
				std::cout << type << " is not a supported file type" << std::endl;
				exit(EXIT_FAILURE);
			}
			break;
		case 'p':
			photo_flag = true;
			break;
		case 'v':
			video_flag = true;
			break;
		case 'r':
			recursive_flag = true;
			break;
		case 'D':
			date_flag = true;
			break;
		case 'w':
			write_flag = true;
			break;
		case 'x':
			delete_flag = true;
			break;
		case 'd':
			duplicate_flag = true;
			break;
		case 'm':
			move_flag = true;
			break;
		case 'h':
			help();
			exit(EXIT_SUCCESS);
		case 'V':
			version();
			exit(EXIT_SUCCESS);
			break;
		case 's':
			verbose_flag = true;
			break;
		case 0:
			break;
		case '?':
			std::cout << "there was an error with given flags" << std::endl;
			exit(EXIT_FAILURE);
		default:
			std::cout << "there was an error with given flags" << std::endl;
			exit(EXIT_FAILURE);
		}
	}

	if (!input_flag || !output_flag)
	{
		std::cout << "input and out directories are mandatory" << std::endl;
		exit(EXIT_FAILURE);
	}

	file_analyzer(input, output,
				  types,
				  photo_flag,
				  video_flag,
				  recursive_flag,
				  date_flag,
				  move_flag,
				  write_flag,
				  delete_flag,
				  duplicate_flag,
				  verbose_flag);
	return 1;
}
