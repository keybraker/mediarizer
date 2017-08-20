#include "Organizer.h"

int main(int argc, char *argv[]) {

int arg[11] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
int *argp = arg;
char *sourcePath = NULL, *destPath = NULL, *filePath = NULL;   

if(argc > 2){

  for(int i = 1; i < argc; i++){
    
    if(!strcmp(argv[i], "-jpg")){ 
      arg[0] = 1;      
    }else if(!strcmp(argv[i], "-png")){ 
      arg[1] = 1;
    }else if(!strcmp(argv[i], "-avi")){
     arg[2] = 1;
    }else if(!strcmp(argv[i], "-mov")){ 
      arg[3] = 1;
    }else if(!strcmp(argv[i], "-wmv")){ 
      arg[4] = 1;
    }else if(!strcmp(argv[i], "-mp4")){ 
      arg[5] = 1;
    }else if(!strcmp(argv[i], "-mts")){
      arg[6] = 1;
    }else if(!strcmp(argv[i], "-det")){ 
      arg[7] = 1;
    }else if(!strcmp(argv[i], "-photo")){ 
      arg[8] = 1;
    }else if(!strcmp(argv[i], "-video")){ 
      arg[9] = 1;
    }else if(!strcmp(argv[i], "-dup")){ 
      arg[10] = 1;
    }else if(argv[i][0] == '-'){
      printf(ACR "%s: is an unrecognizable argument.\n", argv[i]);
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
      printf(" -mts -> for mts organization only\n" ACRE);
      return -1;

    }else{

      if(isRegularFile(argv[i])){ 

        if(sourcePath == NULL && filePath == NULL){
          filePath = (char *) malloc (32768 * sizeof(char));
          filePath = argv[i];

        }else{
          printf(ACR "Usage: jpegOrganizer <jpeg file / source path> <destination path>\n");
          printf("       jpegOrganizer -dup < source path>\n" ACRE);
          return -1;

        }

      }else if(!isRegularFile(argv[i])){ 

        if(sourcePath == NULL && filePath == NULL){ 
          sourcePath = (char *) malloc (32768 * sizeof(char));
          sourcePath = argv[i];

        }else if(sourcePath != NULL || filePath != NULL ){ 
          destPath = (char *) malloc (32768 * sizeof(char));
          destPath = argv[i];

        }else{
          printf(ACR "Usage: jpegOrganizer <jpeg file / source path> <destination path>\n");
          printf("       jpegOrganizer -dup < source path>\n" ACRE);
          return -1;

        }

      }

    }

  }

}else {
  printf(ACR "Usage: jpegOrganizer <jpeg file / source path> <destination path>\n");
  printf("       jpegOrganizer -dup < source path>\n" ACRE);
  return -1;

}

int sum = 0;
for(int i = 0; i < 10; i++){ sum += arg[i]; }
if(arg[10] == 1 && sum != arg[10]){
  printf(ACR "-dup can only be used solely.\n" ACRE);
  return -1;

}

if(filePath != NULL && sourcePath == NULL && destPath != NULL ){ // file version initiation
  fileVersion(filePath, destPath);

}else if(filePath == NULL && sourcePath != NULL && destPath != NULL){ // folder version initiation
  folderVersion(sourcePath, destPath, argp); 

}else if(filePath == NULL && sourcePath != NULL && destPath == NULL && arg[10] == 1){
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
  printf("DELETE A WRONG FILE BUT THE CHANCES ARE MINIMAL TO NONE. \n\n" ACRE);

  string answer;
  cout << "Proceed on your own risk (y/n): ";
  cin  >> answer;

  if(answer.compare("y") == 0){
    duplicateVersion(sourcePath);
  }

}

return 1;

}
