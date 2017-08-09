#include <stdio.h>
#include "exif.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string>
#include <iostream>
#include <dirent.h> 
#include <stdio.h>

int is_regular_file(const char *path){

    struct stat path_stat;
    stat(path, &path_stat);
    return S_ISREG(path_stat.st_mode);
}

int main(int argc, char *argv[]) {

  if(argc == 1){
    printf("Usage: jpegOrganizer <jpeg file>\n");
    return -1;

  }else if (argc == 2) {
    if(is_regular_file(argv[1]) == 1){

      printf("jpeg version initiated for: %s\n",argv[1]);
      //return 0;

    }else{

      printf("folder version\n");
      
      DIR           *d;
      struct dirent *dir;
      d = opendir(argv[1]);
      
      if (d) {
        while ((dir = readdir(d)) != NULL){
          printf("%s\n", dir->d_name);
        }
        closedir(d);

      }

      return 0;


    }

  } else {
    printf("Too much info\n");

  }













  // Read the JPEG file into a buffer
  FILE *fp = fopen(argv[1], "rb");
  if (!fp) {
    printf("Can't open file.\n");
    return -1;
  }
  fseek(fp, 0, SEEK_END);
  unsigned long fsize = ftell(fp);
  rewind(fp);
  unsigned char *buf = new unsigned char[fsize];
  if (fread(buf, 1, fsize, fp) != fsize) {
    printf("Can't read file.\n");
    delete[] buf;
    return -2;
  }
  fclose(fp);

  // Parse EXIF
  easyexif::EXIFInfo result;
  int code = result.parseFrom(buf, fsize);
  delete[] buf;
  if (code) {
    printf("Error parsing EXIF: code %d\n", code);
    return -3;
  }



  // Dump EXIF information
  printf("Original date/time   : %s\n", result.DateTimeOriginal.c_str());

  return 0;
}
