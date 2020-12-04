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
	input_flag,
	output_flag,
	photo_flag,
	video_flag,
	type_flag,
	recursive_flag,
	delete_flag,
	duplicate_flag,
	verbose_flag;

int main(int argc, char *argv[])
{
	int c, option_index = 0;			// getopt_long stores the option index
	char *input = NULL, *output = NULL; //, *types = NULL;

	while (1)
	{
		static struct option long_options[] = {
			{"input", required_argument, &input_flag, 'i'},
			{"Input", required_argument, &input_flag, 'I'},
			{"output", required_argument, &output_flag, 'o'},
			{"Output", required_argument, &output_flag, 'O'},
			{"type", required_argument, &type_flag, 't'},
			{"Type", required_argument, &type_flag, 'T'},
			{"photo", no_argument, &photo_flag, 'p'},
			{"Photo", no_argument, &photo_flag, 'P'},
			{"video", no_argument, &video_flag, 'f'},
			{"Video", no_argument, &video_flag, 'F'},
			{"recursive", no_argument, &recursive_flag, 'r'},
			{"Recursive", no_argument, &recursive_flag, 'R'},
			{"delete", no_argument, &delete_flag, 'x'},
			{"Delete", no_argument, &delete_flag, 'X'},
			{"duplicate", no_argument, &duplicate_flag, 'd'},
			{"Duplicate", no_argument, &duplicate_flag, 'D'},
			{"help", no_argument, NULL, 'h'},
			{"Help", no_argument, NULL, 'H'},
			{"version", no_argument, NULL, 'v'},
			{"Version", no_argument, NULL, 'V'},
			{"verbose", no_argument, &verbose_flag, 's'},
			{"Verbose", no_argument, &verbose_flag, 'S'},
			{0, 0, 0, 0}};

		c = getopt_long(argc, argv, "i:o:t:pfrxdhvsI:O:T:PFRXDHVS", long_options, &option_index);

		if (c == -1)
			break;

		switch (c)
		{
		case 'i':
			std::cout << "input:\t" << optarg << std::endl;
			input_flag = true;
			input = strdup(optarg);
			break;
		case 'I':
			std::cout << "input:\t" << optarg << std::endl;
			input_flag = true;
			input = strdup(optarg);
			break;
		case 'o':
			std::cout << "output:\t" << optarg << std::endl;
			output_flag = true;
			output = strdup(optarg);
			break;
		case 'O':
			std::cout << "output:\t" << optarg << std::endl;
			output_flag = true;
			output = strdup(optarg);
			break;
		case 't':
			type_flag = true;
			// types = strdup(optarg);
			break;
		case 'T':
			type_flag = true;
			// types = strdup(optarg);
			break;
		case 'p':
			photo_flag = true;
			break;
		case 'P':
			photo_flag = true;
			break;
		case 'f':
			video_flag = true;
			break;
		case 'F':
			video_flag = true;
			break;
		case 'r':
			recursive_flag = true;
			break;
		case 'R':
			recursive_flag = true;
			break;
		case 'x':
			delete_flag = true;
			break;
		case 'X':
			delete_flag = true;
			break;
		case 'd':
			duplicate_flag = true;
			break;
		case 'D':
			duplicate_flag = true;
			break;
		case 'h':
			version();
			exit(EXIT_SUCCESS);
		case 'H':
			version();
			exit(EXIT_SUCCESS);
			break;
		case 'v':
			version();
			exit(EXIT_SUCCESS);
		case 'V':
			version();
			exit(EXIT_SUCCESS);
			break;
		case 's':
			verbose_flag = true;
			break;
		case 'S':
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

	std::string arguments = "";
	if (recursive_flag)
	{
		arguments += "-r";
	}
	// if (type_flag)
	// {
	// 	if (recursive_flag)
	// 		arguments += " ";
	// 	arguments += "-ext" + std::string(types);
	// }
	// if (verbose_flag)
	// {
	// 	if (recursive_flag || type_flag)
	// 		arguments += " ";
	// 	arguments += "-v1";
	// }

	file_analyzer(input, output, arguments.c_str());
	return 1;
}
