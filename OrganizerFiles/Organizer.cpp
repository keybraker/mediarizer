#include "Organizer.h"
#include <stdio.h>

#define ACR   "\x1b[31m"
#define ACG   "\x1b[32m"
#define ACRE  "\x1b[0m"

int main(int argc, char *argv[]) {

  if (argc == 3) {
    
    if(isRegularFile(argv[1]) == 1){ // This means that the first path is a file
      if(isRegularFile(argv[2]) == 0){ // This means that the second path is a folder
        fileVersion(argv[1], argv[2]); // So now I know the path I have to put the file in
      }else{ // if second path is a file too, I cannot put a file in a file so error
        printf(ACR "Path: ( %s ), is not a folder so pictures can't be stored there.\n" ACRE, argv[2]);
      }
      return 0;

    }else{ // This means that the first path is a folder
      if(isRegularFile(argv[2]) == 0){ // This means that the second path is a folder
        folderVersion(argv[1], argv[2]); // So now I know the path I have to put, all the files in the folder
      }else{ // if second path is a file too, I cannot put a file in a file so error
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
