#include "organizer.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

void
hlp()
{
	printf("\nThere are three modes to choose from:\n"
	"=====================================\n\n" 
	"1) File Mode\n   ---------\n" 
	" ./mediarizer /path/media.file /path/to/store/folder\n\n" 

	"2) Folder Mode\n   -----------\n" 
	" ./mediarizer /source/path/folder /path/to/store/folder\n\n" 

	"3) Duplication Cleaning Mode\n   -------------------------\n" 
	" ./mediarizer -dup /source/path/folder\n\n" 

	"Flags:\n======\n\n" 
	" Category\n --------\n" 
	" -photos: for photo organization only.\n" 
	" -video:  for video organization only.\n\n" 

	" File type\n ---------\n" 
	" -jpg:    for jpg organization only.\n" 
	" -png:    for png organization only.\n" 
	" -avi:    for avi organization only.\n" 
	" -mov:    for mov organization only.\n" 
	" -wmv:    for wmv organization only.\n" 
	" -mp4:    for mp4 organization only.\n" 
	" -mts:    for mts organization only.\n\n" 

	" Informative\n -----------\n" 
	" -hlp:    for the Media Organizer User Guide.\n" 
	" -vrs:    for version information.\n\n"  

	" Mode\n ----\n" 
	" -dup:    for deletion of duplicates file check and then delete (caution)\n"   
	" -dux:    for deletion of duplicates with completly diffrent as they are found (caution)\n" 
	" -del:    for deletion of source files.\n\n" 

	"(Multiple flags can be used. Path input and out are mandatory) \n\n" ACRE);
}

/* Flag set by ‘--verbose’. */
static int 
	verbose_flag, version_flag, photo_flag, video_flag,
	jpg_flag, png_flag, avi_flag, mov_flag, wmv_flag, 
	mp4_flag, mts_flag, help_flag, dup_flag, dup_dlt_flag,
	dlt_flag, input_flag, output_flag;

int *argp = (int *) malloc (14 * sizeof(int));

int main(int argc, char *argv[])
{
	int c, option_index;
	char *src_path = NULL, *dst_path = NULL, *src_file = NULL;

	while (1)
	{
		static struct option long_options[] =
		{
			{"verbose",				no_argument,			&verbose_flag,			1},
			{"version",				no_argument,			&version_flag,			'f'},
			{"photo",				no_argument,			&photo_flag,			'p'},
			{"video",				no_argument,			&video_flag,			'v'},
			{"jpg",					no_argument,			&jpg_flag,				'j'},
			{"png",					no_argument,			&png_flag,				'n'},
			{"avi",					no_argument,			&avi_flag,				'a'},
			{"mov",					no_argument,			&mov_flag,				'm'},
			{"wmv",					no_argument,			&wmv_flag,				'w'},
			{"mp4",					no_argument,			&mp4_flag,				'4'},
			{"mts",					no_argument,			&mts_flag,				't'},
			{"help",				no_argument,			&help_flag,				'h'},
			{"duplicate",			no_argument,			&dup_flag,				'u'},
			{"dup_delete",			no_argument,			&dup_dlt_flag,			'e'},
			{"delete",				no_argument,			&dlt_flag,				'd'},
			{"input",				required_argument,		&input_flag,			'i'},
			{"output",				required_argument,		&output_flag,			'o'},
			{0,						0,						0,						0}
		};

		/* getopt_long stores the option index here. */
		option_index = 0;

		c = getopt_long(argc, argv, "fpvjnamw4thuedi:o:input:", long_options, &option_index);

		/* Detect the end of the options. */
		if (c == -1) break;

		switch (c)
		{
			case 0:
				/* If this option set a flag, do nothing else now. */
				if (long_options[option_index].flag != 0) break;
					printf ("option %s", long_options[option_index].name);
				if (optarg) printf (" with arg %s", optarg);
					printf ("\n");
				break;

			case 'i':
				// printf("option -i or input with %s\n", optarg);

				input_flag = true;
				if(isFile(optarg))
				{
					src_file = strdup(optarg);
					prnt_scs(__FILE__, __LINE__, "input destination is a valid file");
				}
				else if(isDir(optarg))
				{
					printf("optarg: %s\n", optarg);
					src_path = strdup(optarg);
					prnt_scs(__FILE__, __LINE__, "input destination is a valid path");
				}
				else
					exit_err(__FILE__, __LINE__, "input given is neither directory nor file");
				break;

			case 'o':
				// printf ("option -o or output %s\n", optarg);

				output_flag = true;
				if(isFile(optarg))
				{
					dst_path = strdup(optarg);
					exit_err(__FILE__, __LINE__, "output destination cannot be a file");
				}
				else if(isDir(optarg))
				{
					dst_path = strdup(optarg);
					prnt_scs(__FILE__, __LINE__, "output destination is valid directory");
				}
				else
					exit_err(__FILE__, __LINE__, "output is not a valid directory");
				break;

			case 'h':
				help_flag = true;
				prnt_inf(__FILE__, __LINE__, "help flag is set");
				hlp();
				exit(EXIT_SUCCESS);

			case '?':
				/* getopt_long already printed an error message. */
				break;

			default:
				abort ();
		}
	}

	argp[0]= jpg_flag ? 1 : 0;
	argp[1]= png_flag ? 1 : 0;
	argp[2]= avi_flag ? 1 : 0;
	argp[3]= mov_flag ? 1 : 0;
	argp[4]= wmv_flag ? 1 : 0;
	argp[5]= mp4_flag ? 1 : 0;
	argp[6]= mts_flag ? 1 : 0;
	argp[7]= photo_flag ? 1 : 0;
	argp[8]= video_flag ? 1 : 0;
	argp[9]= dlt_flag ? 1 : 0;
	argp[10]= dup_flag ? 1 : 0;
	argp[11]= dup_dlt_flag ? 1 : 0;
	argp[12]= input_flag ? 1 : 0;
	argp[13]= output_flag ? 1 : 0;

	if (verbose_flag) prnt_inf(__FILE__, __LINE__, "verbose flag is set");
	if (version_flag)
	{
		prnt_inf(__FILE__, __LINE__, "Media Organiser Version: 1.8.0\n"
			"A project by Keybraker (https://github.com/keybraker)\n"
			"GNU License: https://www.gnu.org/philosophy/free-sw.html\n\n"
			"Copyrights © Keybraker 2017, All rights reserved\n");
		exit(EXIT_SUCCESS);
	}

	printf("\nFlag list:\n");

	if(photo_flag)		prnt_inf(__FILE__, __LINE__, "photo flag: enabled");
	if(video_flag)		prnt_inf(__FILE__, __LINE__, "video flag: enabled");
	if(jpg_flag)		prnt_inf(__FILE__, __LINE__, "jpg flag: enabled");
	if(png_flag)		prnt_inf(__FILE__, __LINE__, "png flag: enabled");
	if(avi_flag)		prnt_inf(__FILE__, __LINE__, "avi flag: enabled");
	if(mov_flag)		prnt_inf(__FILE__, __LINE__, "mov flag: enabled");
	if(wmv_flag)		prnt_inf(__FILE__, __LINE__, "wmv flag: enabled");
	if(mp4_flag)		prnt_inf(__FILE__, __LINE__, "mp4 flag: enabled");
	if(mts_flag)		prnt_inf(__FILE__, __LINE__, "mts flag: enabled");
	if(dup_flag)		prnt_inf(__FILE__, __LINE__, "duplicate flag: enabled");
	if(dup_dlt_flag)	prnt_inf(__FILE__, __LINE__, "dup_delete flag: enabled");
	if(dlt_flag)		prnt_inf(__FILE__, __LINE__, "delete flag: enabled");
	if(input_flag)		prnt_inf(__FILE__, __LINE__, "input: enabled");
	if(output_flag)		prnt_inf(__FILE__, __LINE__, "output: enabled");

	/* Print any remaining command line arguments (not options). */
	if (optind < argc)
	{
 		printf ("non-option ARGV-elements: ");
		while (optind < argc)
			printf ("?%s? ", argv[optind++]);
		putchar ('\n');
	}

	//////////////////////////////////////////////////////////////////
	
	if (src_file != NULL && src_path == NULL && dst_path != NULL)
	{ 
		// file version initiation
		prnt_inf(__FILE__, __LINE__, "starting file version");
		fileVersion(src_file, dst_path);
	}
	else if(src_file == NULL && src_path != NULL && dst_path != NULL)
	{ 
		// folder version initiation
		prnt_inf(__FILE__, __LINE__, "starting folder version");
		folderVersion(src_path, dst_path, argp);
	}
	else if(src_file == NULL && src_path != NULL && dst_path == NULL /*&& arg[10] == 1*/)
	{ 
		// duplicate version initiation
		printf(ACG "# DUPLICATE MODE NORMAL\n\n"
			ACR "DISCLAIMER: USE WITH CAUTION! PLEASE BACKUP ALL YOUR FILES \n"
			"BEFORE PROCCEDING TO CLEANUP DUPLICATES\n"
			"=======================================\n"
			"THIS MODE LOOKS UP EVERY FILE IN A DIRECTORY\n"
			"AND COMPARES THE EXIF DATA TO ALL THE OTHERS.\n"
			"IF A FILE IS FOUND THAT HAS THE SAME EXIF AND\n"
			"THEIR NAME IS THE SAME EXCEPT FOR A SLIGHT\n"
			"VARIATION LIKE 'IMG.JPG' AND 'IMG (2).JPG', THE\n"
			"PHOTO WITH THE LONGER NAME WILL BE DELETED.\n"
			"THERE IS A SLIGHT CHANCE THAT THE ALGORITHM MAY,\n"
			"DELETE A WRONG FILE BUT THE CHANCES ARE MINIMAL TO NONE. \n\n" ACRE);

		string answer;
		cout << "Proceed on your own risk (y/n): ";
		cin  >> answer;

		if(answer.compare("y") == 0)
		{
			printf(ACY "\r[prc%%][total size]> exec\n------------------------\n\n");

			time_t start = time(0);
			duplicateVersion(src_path, 0);
			double seconds_since_start = difftime( time(0), start);
			if(seconds_since_start < 60)
			{
				printf(ACY "\r[%-8.1f%-7s]> execution time\n" ACRE, seconds_since_start, " seconds");
			}
			else
			{
				printf(ACY "\r[%-8.2f%-7s]> execution time\n" ACRE, seconds_since_start / 60, " minutes");
			}    

			answer = "n";
			printf(ACR "\nAll detected duplicates are stored in duplicatesToDelete.txt,\n");
			printf("first there is the one to be deleted and bellow that file that\n");
			printf("will be spared. If you want to save a file delete it, and its\n");
			printf("partner file and procced. (y/n): " ACRE);
			cin  >> answer;
			if(answer.compare("y") == 0)
			{
				duplicateRmer();
			}
		}
	}
	else if(src_file == NULL && src_path != NULL && dst_path == NULL /*&& arg[12] == 1*/)
	{ // duplicate Xtreme version initiation
		printf(ACG "# DUPLICATE MODE EXTREME\n\n"
			ACR "DISCLAIMER: USE WITH CAUTION! PLEASE BACKUP ALL YOUR FILES \n"
			"BEFORE PROCCEDING TO CLEANUP DUPLICATES\n"
			"=======================================\n"
			"THIS MODE LOOKS UP EVERY FILE IN A DIRECTORY\n"
			"AND COMPARES THE EXIF DATA TO ALL THE OTHERS.\n"
			"IF A FILE IS FOUND THAT HAS THE SAME EXIF AND\n"
			"THEIR NAME IS THE SAME EXCEPT FOR A SLIGHT\n"
			"VARIATION LIKE 'IMG.JPG' AND 'IMG (2).JPG', THE\n"
			"PHOTO WITH THE LONGER NAME WILL BE DELETED.\n"
			"THERE IS A SLIGHT CHANCE THAT THE ALGORITHM MAY,\n"
			"DELETE A WRONG FILE BUT THE CHANCES ARE MINIMAL TO NONE. \n\n" ACRE);

		string answer;
		cout << "Proceed on your own risk (y/n): ";
		cin  >> answer;

		if(answer.compare("y") == 0)
		{
			printf(ACY "\r[prc%%][total size]> "
				"exec\n------------------------\n\n");

			time_t start = time(0);
			duplicateVersion(src_path, 1);
			double seconds_since_start = difftime( time(0), start);
			if(seconds_since_start < 60)
			{
				printf(ACY "\r[%-8.1f%-7s]> execution time\n" ACRE, 
					seconds_since_start, " seconds");
			}
			else
			{
				printf(ACY "\r[%-8.2f%-7s]> execution time\n" ACRE, 
					seconds_since_start / 60, " minutes");
			}  
		}
	}
	return 1;
}
