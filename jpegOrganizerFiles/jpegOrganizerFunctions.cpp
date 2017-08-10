#include "jpegOrganizer.h"
#include "exif.h"
#include <string>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string>
#include <iostream>
#include <dirent.h> 
#include <stdio.h>
#include <fstream>

using namespace std;

bool transfer(const char *source, const char *destination){
  
      std::ifstream src(source, std::ios::binary);
      std::ofstream dest(destination, std::ios::binary);
      dest << src.rdbuf();
      return src && dest;

}

//const char *dateOfCreation(const char *path){
string dateOfCreation(const char *path){

  // Read the JPEG file into a buffer
  FILE *fp = fopen(path, "rb");
  if (!fp) {
    printf("Can't open file.\n");
    return NULL;
  }
  fseek(fp, 0, SEEK_END);
  unsigned long fsize = ftell(fp);
  rewind(fp);
  unsigned char *buf = new unsigned char[fsize];
  if (fread(buf, 1, fsize, fp) != fsize) {
    printf("Can't read file.\n");
    delete[] buf;
    return NULL;
  }
  fclose(fp);

  // Parse EXIF
  easyexif::EXIFInfo result;
  int code = result.parseFrom(buf, fsize);
  delete[] buf;
  if (code) {
    printf("Error parsing EXIF: code %d\n", code);
    return NULL;
  }

  // Dump EXIF information
  return result.DateTimeOriginal.c_str();
  
}

int is_regular_file(const char *path){

    struct stat path_stat;
    stat(path, &path_stat);
    return S_ISREG(path_stat.st_mode);

}

originalDateData *dateReturn(string originalDate){

  string originalYear   ;
  string originalMonth  ; 
  string originalDay    ; 
  string originalHour   ; 
  string originalMinute ; 
  string originalSecond ;

  string div = ":";
  string divt = " ";
  size_t pos = 0;
  
  pos = originalDate.find(div);  
  originalYear = originalDate.substr(0, pos);
  originalDate.erase(0, pos + div.length());

  pos = originalDate.find(div);  
  originalMonth = originalDate.substr(0, pos);
  originalDate.erase(0, pos + div.length());

  pos = originalDate.find(divt);  
  originalDay = originalDate.substr(0, pos);
  originalDate.erase(0, pos + divt.length());

  pos = originalDate.find(div);  
  originalHour = originalDate.substr(0, pos);
  originalDate.erase(0, pos + div.length());

  pos = originalDate.find(div);  
  originalMinute = originalDate.substr(0, pos);
  originalDate.erase(0, pos + div.length());
  
  pos = originalDate.find(div);  
  originalSecond = originalDate.substr(0, pos);
  originalDate.erase(0, pos + div.length());
  
  originalDateData *origin = (originalDateData *) malloc (sizeof(originalDateData));

  origin->year   = atoi  (originalYear.c_str());
  origin->month  = atoi  (originalMonth.c_str()); 
  origin->day    = atoi  (originalDay.c_str()); 
  origin->hour   = atoi  (originalHour.c_str()); 
  origin->minute = atoi  (originalMinute.c_str());
  origin->second = atoi  (originalSecond.c_str());

  return origin;

}

void jpegVersion(const char *path){

  string originalDate = dateOfCreation(path);

  cout << "JPEGER: Original date/time   : " << originalDate << endl;
  
  originalDateData *originalDateStruct = (originalDateData *) malloc (sizeof(originalDateData));
  originalDateStruct = dateReturn(originalDate);
  
  cout << "originalYear:    " << originalDateStruct->year << endl;
  cout << "originalMonth:   " << originalDateStruct->month << endl;
  cout << "originalDay:     " << originalDateStruct->day << endl;
  cout << "originalHour:    " << originalDateStruct->hour << endl;
  cout << "originalMinute:  " << originalDateStruct->minute << endl;
  cout << "originalSecond:  " << originalDateStruct->second << endl;

}

void folderVersion(const char *path){

  printf("FOLDERER: ");
  DIR           *d;
  struct dirent *dir;
  d = opendir(path);
  
  if (d) {
    while ((dir = readdir(d)) != NULL){
      printf("%s\n", dir->d_name);
    }
    closedir(d);
    
  }
  
}