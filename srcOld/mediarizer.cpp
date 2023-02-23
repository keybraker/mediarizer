//------------------------------------------------------------------------------
// File:        mediarizer.cpp
//
// Description: A simple C++ library to organize and delete
//              duplicatehotos and video files.
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

#include "mediarizer_hdr/processor.h"

int main(int argc, char *argv[])
{
	flag_struct *flags = new flag_struct();

	flags->input_flag = false;
	flags->output_flag = false;
	flags->photo_flag = false;
	flags->video_flag = false;
	flags->type_flag = false;
	flags->recursive_flag = false;
	flags->date_flag = false;
	flags->move_flag = false;
	flags->write_flag = false;
	flags->delete_flag = false;
	flags->duplicate_flag = false;
	flags->verbose_flag = false;

	int c, option_index = 0; // getopt_long stores the option index
	char *input = NULL, *output = NULL;
	std::vector<std::string> types;

	while (1)
	{
		static struct option long_options[] = {
			{"input", required_argument, &flags->input_flag, 'i'},
			{"output", required_argument, &flags->output_flag, 'o'},
			{"type", required_argument, &flags->type_flag, 't'},
			{"photo", no_argument, &flags->photo_flag, 'p'},
			{"video", no_argument, &flags->video_flag, 'v'},
			{"recursive", no_argument, &flags->recursive_flag, 'r'},
			{"date", no_argument, &flags->date_flag, 'D'},
			{"move", no_argument, &flags->move_flag, 'm'},
			{"write", no_argument, &flags->write_flag, 'w'},
			{"delete", no_argument, &flags->delete_flag, 'x'},
			{"duplicate", no_argument, &flags->duplicate_flag, 'd'},
			{"help", no_argument, NULL, 'h'},
			{"Version", no_argument, NULL, 'V'},
			{"verbose", no_argument, &flags->verbose_flag, 's'},
			{0, 0, 0, 0}};

		c = getopt_long(argc, argv, "i:o:t:pvrDwxdmhVs", long_options, &option_index);

		if (c == -1)
			break;

		switch (c)
		{
		case 'i':
			std::cout << "input:\t" << optarg << std::endl;
			flags->input_flag = true;
			input = strdup(optarg);
			break;
		case 'o':
			std::cout << "output:\t" << optarg << std::endl;
			flags->output_flag = true;
			output = strdup(optarg);
			break;
		case 't':
			flags->type_flag = true;
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
			flags->photo_flag = true;
			break;
		case 'v':
			flags->video_flag = true;
			break;
		case 'r':
			flags->recursive_flag = true;
			break;
		case 'D':
			flags->date_flag = true;
			break;
		case 'w':
			flags->write_flag = true;
			break;
		case 'x':
			flags->delete_flag = true;
			break;
		case 'd':
			flags->duplicate_flag = true;
			break;
		case 'm':
			flags->move_flag = true;
			break;
		case 'h':
			help();
			exit(EXIT_SUCCESS);
		case 'V':
			version();
			exit(EXIT_SUCCESS);
			break;
		case 's':
			flags->verbose_flag = true;
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

	if (!flags->input_flag || !flags->output_flag)
	{
		std::cout << "input and out directories are mandatory" << std::endl;
		exit(EXIT_FAILURE);
	}

	file_analyzer(input, output, *flags, types);

	return 0;
}
