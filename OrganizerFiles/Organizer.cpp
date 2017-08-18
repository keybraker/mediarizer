#include "Organizer.h"
#include <stdio.h>

#define ACR   "\x1b[31m"
#define ACG   "\x1b[32m"
#define ACRE  "\x1b[0m"

int main(int argc, char *argv[]) {

  if (argc == 3) {
    
    if(strcmp(argv[1], "-dup") == 0){
      printf(ACG "( DUPLICATE MODE ) ~ BETA\n\n");
      printf(ACR "DISCLAIMER: USE WITH CAUTION! PLEASE BACKUP ALL YOUR FILES \n");
      printf("BEFORE PROCCEDING TO CLEANUP DUPLICATES\n");
      printf("=======================================\n");
      printf("THIS MODE LOOKS UP EVERY FILE IN A DIRECTORY\n");
      printf("AND COMPARES THE EXIF DATA TO ALL THE OTHERS.\n");
      printf("IF A FILE IS FOUND THAT HAS THE SAME EXIF AND\n");
      printf("THEIR NAME IS THE SAME EXCEPT FOR A SLIGHT\n");
      printf("VARIATION LIKE 'IMG.JPG' AND 'IMG (2).JPG', THE\n");
      printf("PHOTO WITH THE LONGER NAME WILL BE DELETED.\n");
      printf("THERE IS A SLIGHT CHANCE THAT THE ALGORITHM MAY,\n");
      printf("DELETE A WRONG FILE BUT THE CHANCES ARE MINIMAL TO NONE.\n\n" ACRE);

      if(!isRegularFile(argv[2])){
        duplicateVersion(argv[2]);
      }else{
        printf(ACR "Duplicate Cleaner: can only be used in folders.\n");
        printf("( %s , is not a directory )" ACRE, argv[2]);
      }

    }else{

      if(isRegularFile(argv[1]) == 1){ // This means that the first path is a file
        if(isRegularFile(argv[2]) == 0){ // This means that the second path is a folder
          fileVersion(argv[1], argv[2]); // So now I know the path I have to put the file in

        }else{ // if second path is a file too, I cannot put a file in a file so error
          printf(ACR "Path: ( %s ), is not a folder so pictures can't be stored there.\n" ACRE, argv[2]);

        }
        return 0;

      }else{ // This means that the first path is a folder
        int arg[8] = {-1, -1, -1, -1, -1, -1, -1, -1};
        int *argp = arg;

        if(isRegularFile(argv[2]) == 0){ // This means that the second path is a folder
          folderVersion(argv[1], argv[2], argp); // So now I know the path I have to put, all the files in the folder

        }else{ // if second path is a file too, I cannot put a file in a file so error
          printf(ACR "Path: ( %s ), is not a folder so pictures can't be stored there.\n" ACRE, argv[2]);
          
        }
        return 0;

      }

    }

  }else if (argc > 3 && argc < 10) {

    int arg[8] = {-1, -1, -1, -1, -1, -1, -1, -1};
    int *argp = arg;
    
    if(argc == 4 && strcmp(argv[3], "-photo") == 0){
      arg[0] = 2;

    }else if(argc == 4 && strcmp(argv[3], "-video") == 0){
      arg[0] = 3;

    }else{

      for(int i = 0; i+3 < argc; i++){

              if(strcmp(argv[i+3], "-jpg") == 0){ arg[0] = 1;      
        }else if(strcmp(argv[i+3], "-png") == 0){ arg[1] = 1;
        }else if(strcmp(argv[i+3], "-avi") == 0){ arg[2] = 1;
        }else if(strcmp(argv[i+3], "-mov") == 0){ arg[3] = 1;
        }else if(strcmp(argv[i+3], "-wmv") == 0){ arg[4] = 1;
        }else if(strcmp(argv[i+3], "-mp4") == 0){ arg[5] = 1;
        }else if(strcmp(argv[i+3], "-mts") == 0){ arg[6] = 1;
        }else if(strcmp(argv[i+3], "-det") == 0){ arg[7] = 1;
        }else{
          printf("%s: is an unrecognizable argument.\n", argv[i+3]);
          printf("Please consider using one of the following:\n\n");
          printf("Category:\n---------\n");
          printf(" -photos -> for photo organization only\n");
          printf(" -video -> for video organization only\n");
          printf(" ( Attention: These modes can only be used solely )\n\n");
          printf("File type:\n----------\n");
          printf(" -jpg -> for jpg organization only\n");
          printf(" -png -> for png organization only\n");
          printf(" -avi -> for avi organization only\n");
          printf(" -mov -> for mov organization only\n");
          printf(" -wmv -> for wmv organization only\n");
          printf(" -mp4 -> for mp4 organization only\n");
          printf(" -mts -> for mts organization only\n");
          return -1;
        }

      }

    }

    if(isRegularFile(argv[1]) == 1){ // This means that the first path is a file
      if(isRegularFile(argv[2]) == 0){ // This means that the second path is a folder
        fileVersion(argv[1], argv[2]); // So now I know the path I have to put the file in

      }else{ // if second path is a file too, I cannot put a file in a file so error
        printf(ACR "Path: ( %s ), is not a folder so pictures can't be stored there.\n" ACRE, argv[2]);

      }
      return 0;

    }else{ // This means that the first path is a folder
      if(isRegularFile(argv[2]) == 0){ // This means that the second path is a folder
        folderVersion(argv[1], argv[2], argp); // So now I know the path I have to put, all the files in the folder

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
