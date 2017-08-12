#include "jpegOrganizer.h"
#include <stdio.h>

#define ACR   "\x1b[31m"
#define ACG   "\x1b[32m"
#define ACRE  "\x1b[0m"

int main(int argc, char *argv[]) {

  if (argc == 3) {
    
    if(isRegularFile(argv[1]) == 1){
      if(isRegularFile(argv[2]) == 0){
        jpegVersion(argv[1], argv[2]);
      }else{
        printf(ACR "Path: ( %s ), is not a folder so pictures can't be stored there.\n" ACRE, argv[2]);
      }
      return 0;

    }else{
      if(isRegularFile(argv[2]) == 0){
        folderVersion(argv[1], argv[2]);
      }else{
        printf(ACR "Path: ( %s ), is not a folder so pictures can't be stored there.\n" ACRE, argv[2]);
      }
      return 0;

    }

  } else {
    printf("Usage: jpegOrganizer <jpeg file / folder path> <destination path>\n");
    return -1;

  }

  return 0;
}
