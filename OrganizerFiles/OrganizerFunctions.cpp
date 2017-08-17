#include "Organizer.h"
#include <string>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h> 
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <cassert>
#include <fcntl.h>
#include <errno.h>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <array>

#define ACR   "\x1b[31m"
#define ACG   "\x1b[32m"
#define ACRE  "\x1b[0m"

using namespace std;

string exec(const char* cmd) {
    
    array<char, 128> buffer;
    string result;
    shared_ptr<FILE> pipe(popen(cmd, "r"), pclose);
    if (!pipe) throw std::runtime_error("popen() failed!");
    while (!feof(pipe.get())) {
        if (fgets(buffer.data(), 128, pipe.get()) != nullptr)
            result += buffer.data();
    }
    return result;

}

int transfer(const char *source, const char *dest){

  char* transfer = (char*) malloc (32768 * sizeof(char));

  strcpy(transfer, "sudo cp \"");
  strcat(transfer, source);
  strcat(transfer, "\" ");
  strcat(transfer, dest);

  printf("> %s\n", transfer);
  system(transfer);

  return 0;

}

string dateOfCreation(const char *path){

  char* cmd = (char *) malloc (32768 * sizeof(char));
  strcpy(cmd, "exiftool -FileType ");
  strcat(cmd, path);

  string fileType = exec(cmd);
  fileType = fileType.substr(34,fileType.length());

  string fileDate;

  if(fileType.compare("JPEG\n") == 0){
    cout << "(jpeg) ";
    strcpy(cmd, "exiftool -CreateDate ");
    strcat(cmd, path);
    fileDate = exec(cmd); 
    return fileDate.substr(34,fileDate.length());

  }else if(fileType.compare("PNG\n") == 0){
    cout << "(png)  ";
    strcpy(cmd, "exiftool -CreateDate ");
    strcat(cmd, path);
    fileDate = exec(cmd);
    return fileDate.substr(34,fileDate.length());

  }else if(fileType.compare("AVI\n") == 0){
    cout << "(avi)  ";
    strcpy(cmd, "exiftool -DateTimeOriginal ");
    strcat(cmd, path);
    fileDate = exec(cmd);
    return fileDate.substr(34,fileDate.length());

  }else if(fileType.compare("MOV\n") == 0){
    cout << "(mov)  ";
    strcpy(cmd, "exiftool -CreateDate ");
    strcat(cmd, path);
    fileDate = exec(cmd);
    return fileDate.substr(34,fileDate.length());

  }else if(fileType.compare("WMV\n") == 0){
    cout << "(wmv)  ";
    strcpy(cmd, "exiftool -CreationDate ");
    strcat(cmd, path);
    fileDate = exec(cmd);
    return fileDate.substr(34,fileDate.length());

  }else if(fileType.compare("MP4\n") == 0){
    cout << "(mp4)  ";
    strcpy(cmd, "exiftool -CreateDate ");
    strcat(cmd, path);
    fileDate = exec(cmd);
    return fileDate.substr(34,fileDate.length());

  }else{
    return string(); // empty string

  }
  
}

int isRegularFile(const char *path){

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

bool dirEx(const char* directory){
    
  DIR* dir = opendir(directory);
  if (dir) {
    closedir(dir);
    return true;
  }

  return false;

}

char *destinationFinder(int year, int month, const char *pathToStore){
  
  char *destinationPath = (char *) malloc (32768 * sizeof(char));
  char *destinationPathFolder = (char *) malloc (32768 * sizeof(char));

  strcpy(destinationPathFolder, "mkdir ");
  strcat(destinationPathFolder, pathToStore);
  strcat(destinationPathFolder, "/");

  strcpy(destinationPath, pathToStore);
  strcat(destinationPath, "/");

  if(year >= 1989 && year <= 2040){
    char yearStr[12];
    sprintf(yearStr, "%d", year);

    strcat(destinationPath, yearStr);
    strcat(destinationPath, "/");
    strcat(destinationPathFolder, yearStr);
    strcat(destinationPathFolder, "/");

    if(!dirEx(destinationPath))
      system(destinationPathFolder);

  }else{
    strcat(destinationPath, "unknownDate"); // peritti apla gia to fainestai
    strcat(destinationPathFolder, destinationPath);
    
    if(!dirEx(destinationPath))
      system(destinationPathFolder);

    return destinationPath;
  }

  switch(month) {
    case 1 :
      strcat(destinationPath, "January");
      strcat(destinationPathFolder, "January");
      break;
    case 2 :
      strcat(destinationPath, "February");
      strcat(destinationPathFolder, "February");
      break;
    case 3 :
      strcat(destinationPath, "March");
      strcat(destinationPathFolder, "March");
      break;
    case 4 :
      strcat(destinationPath, "April");
      strcat(destinationPathFolder, "April");
      break;
    case 5 :
      strcat(destinationPath, "May");
      strcat(destinationPathFolder, "May");
      break;
    case 6 :
      strcat(destinationPath, "June");
      strcat(destinationPathFolder, "June");
      break;
    case 7 :
      strcat(destinationPath, "July");
      strcat(destinationPathFolder, "July");
      break;
    case 8 :
      strcat(destinationPath, "August");
      strcat(destinationPathFolder, "August");
      break;
    case 9 :
      strcat(destinationPath, "September");
      strcat(destinationPathFolder, "September");
      break;
    case 10 :
       strcat(destinationPath, "October");
      strcat(destinationPathFolder, "October");
      break;
    case 11 :
      strcat(destinationPath, "November");
      strcat(destinationPathFolder, "November");
      break;
    case 12 :
      strcat(destinationPath, "December");
      strcat(destinationPathFolder, "December"); 
      break;

    default:
      strcat(destinationPath, "unknown");
      strcat(destinationPathFolder, "unknown");
      break;
  }

  if(!dirEx(destinationPath))
    system(destinationPathFolder);

  return destinationPath;

}

void fileVersion(const char *path, const char *pathToStore){

  string originalDate = dateOfCreation(path);
  
  if(originalDate.empty()){ 
    
    FILE *corruptedFiles = fopen("corruptedFiles.txt", "a");
    if(corruptedFiles == NULL){printf("Error while opening file.\n");}
    fprintf(corruptedFiles,"%s\n",path);            

    return;

  }

  originalDateData *originalDateStruct = (originalDateData *) malloc (sizeof(originalDateData));
  originalDateStruct = dateReturn(originalDate);
  char *destinationPath = destinationFinder(originalDateStruct->year, originalDateStruct->month, pathToStore);
 
  transfer(path, destinationPath);
  
  return;

  // cout << "originalYear   : " << originalDateStruct->year   << endl;
  // cout << "originalMonth  : " << originalDateStruct->month  << endl;
  // cout << "originalDay    : " << originalDateStruct->day    << endl;
  // cout << "originalHour   : " << originalDateStruct->hour   << endl;
  // cout << "originalMinute : " << originalDateStruct->minute << endl;
  // cout << "originalSecond : " << originalDateStruct->second << endl;

}

void folderVersion(const char *path, const char *pathToStore){

  int j = 1;
  DIR           *d;
  struct dirent *dir;
  d = opendir(path);
  
  string dirFile;
  string jpegOJ = ".jpg";
  string jpegTJ = ".JPG";
  string jpegOP = ".png";
  string jpegTP = ".PNG";
  string jpegOA = ".avi";
  string jpegTA = ".AVI";
  string jpegOM = ".mov";
  string jpegTM = ".MOV";  
  string jpegOW = ".wmv";
  string jpegTW = ".WMV";
  string jpegOMP = ".mp4";
  string jpegTMP = ".MP4";

  size_t foundOJ = 0, foundTJ = 0;
  size_t foundOP = 0, foundTP = 0;
  size_t foundOA = 0, foundTA = 0;
  size_t foundOM = 0, foundTM = 0;
  size_t foundOW = 0, foundTW = 0;
  size_t foundOMP = 0, foundTMP = 0;

  char* imagePath   = (char*) malloc (32768 * sizeof(char));
  char* unknownPath = (char*) malloc (32768 * sizeof(char));

  strcpy(imagePath, path);
  strcat(imagePath, "/");

  strcpy(unknownPath, path);
  strcat(unknownPath, "/");

  if (d) {
    
    while ((dir = readdir(d)) != NULL){

      dirFile = dir->d_name;
      foundOJ = dirFile.find(jpegOJ);
      foundTJ = dirFile.find(jpegTJ);
      foundOP = dirFile.find(jpegOP);
      foundTP = dirFile.find(jpegTP);
      foundOA = dirFile.find(jpegOA);
      foundTA = dirFile.find(jpegTA);
      foundOM = dirFile.find(jpegOM);
      foundTM = dirFile.find(jpegTM);
      foundOW = dirFile.find(jpegOW);
      foundTW = dirFile.find(jpegTW);
      foundTMP = dirFile.find(jpegTMP);

      strcat(unknownPath, dir->d_name);

      if (foundOJ != string::npos || foundTJ != string::npos 
        || foundOP != string::npos || foundTP != string::npos 
        || foundOA != string::npos || foundTA != string::npos 
        || foundOM != string::npos || foundTM != string::npos 
        || foundOW != string::npos || foundTW != string::npos 
        || foundOMP != string::npos || foundTMP != string::npos ){

        strcat(imagePath, dir->d_name);

        int length = (int) strlen(imagePath);
        for(int i = 0; i < length; i++){
          if(imagePath[i] == '.' 
            && i+1 <= length 
            && (imagePath[i+1] == '_' || imagePath[i+1] == 'D')){
            j = 0; break; 
          }
        }

        if(j)
          fileVersion(imagePath, pathToStore);

        j = 1;
        strcpy(imagePath, path);
        strcat(imagePath, "/");

      }else if(!isRegularFile(unknownPath) 
        && (dirFile.find('.') == std::string::npos)){
        folderVersion(unknownPath, pathToStore);

      }

      strcpy(unknownPath, path);
      strcat(unknownPath, "/");

    }

    closedir(d);
    return ;
    
  }
  
}