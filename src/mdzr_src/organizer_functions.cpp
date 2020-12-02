#include "../mdzr_hdr/organizer.h"

bool isDir(const char *path)
{
	struct stat sb;
	if (stat(path, &sb) == 0 && S_ISDIR(sb.st_mode))
		return true;
	return false;
}

int isFile(const char *path)
{
	struct stat path_stat;
	stat(path, &path_stat);
	return S_ISREG(path_stat.st_mode);
}

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
	"December" 
};

std::string get_date_path(std::string date)
{
	if (date.empty() || date.size() < 10)
		return std::string("Undetermined");
		
	std::string date_year = date.substr(0, 4);
	int month_number = stoi(date.substr(4, 2));
	std::string date_month = g_months[month_number - 1];

	return date_year + "/" + date_month;
}

std::vector<PhotoInfo> linked_list_to_vector(char *path)
{
	ExifTool *et = new ExifTool();
	TagInfo *tag_info = et->ImageInfo(path, NULL, 5);
	std::vector<PhotoInfo> photo_list;

	if (tag_info)
	{
		PhotoInfo *new_photo = (PhotoInfo *)malloc(sizeof(PhotoInfo));
		bool first = true;
		for (TagInfo *i = tag_info; i; i = i->next)
		{
			// std::cout << "name: " << i->name << " = 0, value: " << i->value << endl;
			if (strcmp(i->name, "FileName") == 0)
			{
				std::cout << endl;
				if (!first)
				{
					photo_list.push_back(*new_photo);
					new_photo = (PhotoInfo *)malloc(sizeof(PhotoInfo));
				}
				else
				{
					first = false;
				}
				new_photo->fileName = strdup(i->value);
			}
			else if (strcmp(i->name, "FileType") == 0)
			{
				new_photo->fileType = strdup(i->value);
			}
			else if (strcmp(i->name, "FileSize") == 0)
			{
				new_photo->fileSize = strdup(i->value);
			}
			else if (strcmp(i->name, "ImageSize") == 0)
			{
				new_photo->fileRes = strdup(i->value);
			}
			else if (strcmp(i->name, "CreateDate") == 0)
			{
				new_photo->createDate = strdup(i->value);
			}
			else if (strcmp(i->name, "ModifyDate") == 0)
			{
				new_photo->modifyDate = strdup(i->value);
			}
			else if (strcmp(i->name, "FileModifyDate") == 0)
			{
				new_photo->modifyDate = strdup(i->value);
			}
			else if (strcmp(i->name, "Directory") == 0)
			{
				new_photo->source_directory = strdup(i->value);
			}
		}
		photo_list.push_back(*new_photo);
		delete tag_info;
	}
	else if (et->LastComplete() <= 0)
	{
		cerr << "Error executing exiftool!" << endl;
		return photo_list;
	}

	char *err = et->GetError();
	if (err)
		cerr << err;
	delete et;

	return photo_list;
}

void *calculate_move_directory(PhotoInfo photo_info, char *move_path)
{
	std::string date, move_path_str = std::string(move_path);

	if (photo_info.createDate != NULL)
	{
		date = std::string(photo_info.createDate);
		std::cout << "B photo_info.createDate: " << date << endl;
		date.resize(10);
		std::cout << "A photo_info.createDate: " << date << endl;
	}
	else if (photo_info.modifyDate != NULL)
	{
		date = std::string(photo_info.modifyDate);
		std::cout << "B photo_info.modifyDate: " << date << endl;
		date.resize(10);
		std::cout << "A photo_info.modifyDate: " << date << endl;
	}
	else
	{
		return (void *)date.c_str();
	}

	photo_info.move_directory = std::string(move_path);
	photo_info.move_directory += "/";
	photo_info.move_directory += get_date_path(date);

	std::cout << "photo_info.move_directory: "
			  << photo_info.move_directory
			  << endl;

	return NULL;
}

void file_analyzer(char *path, char *move_path)
{
	std::cout << "analyzing photos and vectorizing";
	auto start0 = std::chrono::high_resolution_clock::now();

	std::vector<PhotoInfo> photo_list = linked_list_to_vector(path);

	auto stop0 = std::chrono::high_resolution_clock::now();
	auto duration0 = std::chrono::duration_cast<std::chrono::microseconds>(stop0 - start0);

	std::cout << "..done (processed " << photo_list.size() << " photos)" << endl;

	auto start = std::chrono::high_resolution_clock::now();

	int i;
	#pragma omp parallel for private(i)
	for (i = 0; i < (int)photo_list.size(); ++i)
	{
		// std::cout << "THREAD " << omp_get_thread_num() << "/" << omp_get_num_threads() << endl
		//   << "fileName: "
		//   << "\t" << (photo_list[i].fileName ? photo_list[i].fileName : "NULL") << endl
		//   << "fileType: "
		//   << "\t" << (photo_list[i].fileType ? photo_list[i].fileType : "NULL") << endl
		//   << "fileSize: "
		//   << "\t" << (photo_list[i].fileSize ? photo_list[i].fileSize : "NULL") << endl
		//   << "fileRes: "
		//   << "\t" << (photo_list[i].fileRes ? photo_list[i].fileRes : "NULL") << endl
		//   << "source_directory: "
		//   << "\t" << (photo_list[i].source_directory ? photo_list[i].source_directory : "NULL") << endl
		//   << "createDate: "
		//   << "\t" << (photo_list[i].createDate ? photo_list[i].createDate : "NULL") << endl
		//   << "modifyDate: "
		//   << "\t" << (photo_list[i].modifyDate ? photo_list[i].modifyDate : "NULL") << endl
		//   << endl;
		calculate_move_directory(photo_list[i], move_path);
	}
	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

	// auto start2 = std::chrono::high_resolution_clock::now();
	// #pragma omp parallel
	// #pragma omp single
	// 	for (PhotoInfo photo2 : photo_list)
	// 	{
	// #pragma omp task firstprivate(photo2)
	// #pragma omp critical(std::cout)
	// 		std::cout << "THREAD " << omp_get_thread_num() << "/" << omp_get_num_threads() << endl
	// 				  << "fileName: " << (photo2.fileName ? photo2.fileName : "NULL") << endl
	// 				  //   << "fileType: " << (photo2.fileType ? photo2.fileType : "NULL") << endl
	// 				  //   << "fileSize: " << (photo2.fileSize ? photo2.fileSize : "NULL") << endl
	// 				  //   << "fileRes: " << (photo2.fileRes ? photo2.fileRes : "NULL") << endl
	// 				  //   << "createDate: " << (photo2.createDate ? photo2.createDate : "NULL") << endl
	// 				  //   << "source_directory: " << (photo2.source_directory ? photo2.source_directory : "NULL") << endl
	// 				  //   << "modifyDate: " << (photo2.modifyDate ? photo2.modifyDate : "NULL") << endl
	// 				  << endl;
	// 	}
	// auto stop2 = std::chrono::high_resolution_clock::now();
	// auto duration2 = std::chrono::duration_cast<std::chrono::microseconds>(stop2 - start2);
	std::cout << "mhden: " << duration0.count() << endl;
	std::cout << "ena: " << duration.count() << endl;
	// std::cout << "duo: " << duration2.count() << endl;
	// std::cout << duration.count() << "/" << duration2.count() << "=" << duration.count() / duration2.count() << endl;

	return;
}