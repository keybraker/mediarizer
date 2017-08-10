#include "jpegOrganizer.h"
#include <stdio.h>

int main(int argc, char *argv[]) {

  if(argc == 1){
    printf("Usage: jpegOrganizer <jpeg file / folder path>\n");
    return -1;

  }else if (argc == 2) {
    
    if(isRegularFile(argv[1]) == 1){
      printf("jpeg version -> ");
      jpegVersion(argv[1]);
      return 0;

    }else{
      printf("folder version -> ");
      folderVersion(argv[1]);
      return 0;

    }

  } else {
    printf("Too much info\n");

  }

  return 0;
}
