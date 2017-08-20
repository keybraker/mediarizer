#include "Organizer.h"

using namespace std;

int detailed = -1;

void detailedFile(const char* string){

  // printf("%s > ", string);
  return;

  if(detailed){
    FILE *detFile = fopen("detailedTransfer.txt", "a");
    if(detFile == NULL){ printf("Error while opening file.\n"); }
    fprintf(detFile,"%s\n",string);
  }

}

string exec(const char* cmd) { detailedFile("exec"); 
detailedFile("⬇︎");
    
    array<char, 32768> buffer;
    string result;
    shared_ptr<FILE> pipe(popen(cmd, "r"), pclose);
    //if (!pipe) throw runtime_error("popen() failed!");
    if (!pipe){
      printf("popen() failed!");
      return string();
    }
    while (!feof(pipe.get())) {
        if (fgets(buffer.data(), 32768, pipe.get()) != nullptr)
            result += buffer.data();
    }
    
    return result;

}

int transfer(const char *source, const char *dest){ 
  detailedFile("transfer"); detailedFile("⬇︎");

  char* transfer = (char*) malloc (32768 * sizeof(char));

  strcpy(transfer, "sudo cp \"");
  strcat(transfer, source);
  strcat(transfer, "\" ");
  strcat(transfer, dest);

  system(transfer);

  printf("> %s\n", transfer);
  detailedFile(transfer);
  detailedFile("\n===========");

  return 0;

}

string dateOfCreation(const char *path){ 
  detailedFile("dateOfCreation"); detailedFile("⬇︎");
  
  char* cmd = (char *) malloc (32768 * sizeof(char));
  strcpy(cmd, "exiftool -FileType \"");
  strcat(cmd, path);
  strcat(cmd, "\"");

  string fileType = exec(cmd);

  if(!fileType.empty()){
    fileType = fileType.substr(34,fileType.length());
  }else{
    return string();
  }

  string fileDate;

  if(fileType.compare("JPEG\n") == 0){
    // cout << "(JPG)  ";
    strcpy(cmd, "exiftool -CreateDate \"");
    strcat(cmd, path);
    strcat(cmd, "\"");
    fileDate = exec(cmd);

    if(!fileDate.empty())    
      return fileDate.substr(34,fileDate.length());

  }else if(fileType.compare("PNG\n") == 0){
    // cout << "(PNG)  ";
    strcpy(cmd, "exiftool -CreateDate \"");
    strcat(cmd, path);
    strcat(cmd, "\"");
    fileDate = exec(cmd);

    if(!fileDate.empty())
      return fileDate.substr(34,fileDate.length());

  }else if(fileType.compare("AVI\n") == 0){
    // cout << "(AVI)  ";
    strcpy(cmd, "exiftool -DateTimeOriginal \"");
    strcat(cmd, path);
    strcat(cmd, "\"");
    fileDate = exec(cmd);

    if(!fileDate.empty())
      return fileDate.substr(34,fileDate.length());

  }else if(fileType.compare("MOV\n") == 0){
    // cout << "(MOV)  ";
    strcpy(cmd, "exiftool -CreateDate \"");
    strcat(cmd, path);
    strcat(cmd, "\"");
    fileDate = exec(cmd);

    if(!fileDate.empty())
      return fileDate.substr(34,fileDate.length());

  }else if(fileType.compare("WMV\n") == 0){
    // cout << "(WMV)  ";
    strcpy(cmd, "exiftool -CreationDate \"");
    strcat(cmd, path);
    strcat(cmd, "\"");
    fileDate = exec(cmd);

    if(!fileDate.empty())
      return fileDate.substr(34,fileDate.length());

  }else if(fileType.compare("MP4\n") == 0){
    // cout << "(MP4)  ";
    strcpy(cmd, "exiftool -CreateDate \"");
    strcat(cmd, path);
    strcat(cmd, "\"");
    fileDate = exec(cmd);

    if(!fileDate.empty())    
      return fileDate.substr(34,fileDate.length());

  }else if(fileType.compare("M2TS\n") == 0){
    // cout << "(M2TS) ";
    strcpy(cmd, "exiftool -DateTimeOriginal \"");
    strcat(cmd, path);
    strcat(cmd, "\"");
    fileDate = exec(cmd);

    if(!fileDate.empty())
      return fileDate.substr(34,fileDate.length());

  }

  return string(); // empty string
    
}

int isRegularFile(const char *path){ 
  detailedFile("isRegularFile"); detailedFile("⬇︎");
    
    struct stat path_stat;
    stat(path, &path_stat);
    return S_ISREG(path_stat.st_mode);

}

originalDateData *dateReturn(string originalDate){ 
  detailedFile("dateReturn"); detailedFile("⬇︎");
  
  if(originalDate.empty())
    return NULL;

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
  detailedFile("dirEx"); detailedFile("⬇︎");
    
  DIR* dir = opendir(directory);
  if (dir) {
    closedir(dir);
    return true;
  }
  return false;

}

char *destinationFinder(int year, int month, const char *pathToStore, bool type){ 
  detailedFile("destinationFinder"); detailedFile("⬇︎");
  
  char *destinationPath             = (char *) malloc (32768 * sizeof(char));
  char *destinationPathToExec       = (char *) malloc (32768 * sizeof(char));
  char *destinationPathFolder       = (char *) malloc (32768 * sizeof(char));
  char *destinationPathFolderToExec = (char *) malloc (32768 * sizeof(char));

  strcpy(destinationPathFolder, "mkdir \"");
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

    strcpy(destinationPathFolderToExec, destinationPathFolder);
    strcat(destinationPathFolderToExec, "\"");

    if(!dirEx(destinationPath))
      system(destinationPathFolderToExec);

  }else{
    strcat(destinationPath, "unknownDate"); // peritti apla gia to fainestai
    strcat(destinationPathFolder, destinationPath);

    strcpy(destinationPathFolderToExec, destinationPathFolder);
    strcat(destinationPathFolderToExec, "\"");

    if(!dirEx(destinationPath))
      system(destinationPathFolderToExec);

    if(type){
      strcat(destinationPath, "/photos");
      strcat(destinationPathFolder, "/photos");
    }else{
      strcat(destinationPath, "/videos");      
      strcat(destinationPathFolder, "/videos");      
    }

    strcpy(destinationPathFolderToExec, destinationPathFolder);
    strcat(destinationPathFolderToExec, "\"");

    if(!dirEx(destinationPath))
      system(destinationPathFolderToExec);

    strcpy(destinationPathToExec, "\"");
    strcat(destinationPathToExec, destinationPath);
    strcat(destinationPathToExec, "\"");

    return destinationPathToExec;
    
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

  strcpy(destinationPathFolderToExec, destinationPathFolder);
  strcat(destinationPathFolderToExec, "\"");

  if(!dirEx(destinationPath))
    system(destinationPathFolderToExec);

  if(type){
    strcat(destinationPath, "/photos");
    strcat(destinationPathFolder, "/photos");
  }else{
    strcat(destinationPath, "/videos");      
    strcat(destinationPathFolder, "/videos");      
  }

  strcpy(destinationPathFolderToExec, destinationPathFolder);
  strcat(destinationPathFolderToExec, "\"");

  if(!dirEx(destinationPath))
    system(destinationPathFolderToExec);

  strcpy(destinationPathToExec, "\"");
  strcat(destinationPathToExec, destinationPath);
  strcat(destinationPathToExec, "\"");

  return destinationPathToExec;

}

bool typeOfFile(const char* path){ 
  detailedFile("typeOfFile"); detailedFile("⬇︎");

  char* cmd = (char *) malloc (32768 * sizeof(char));
  strcpy(cmd, "exiftool -FileType \"");
  strcat(cmd, path);
  strcat(cmd, "\"");

  string fileType = exec(cmd);
  if(!fileType.empty()){
    fileType = fileType.substr(34,fileType.length());
  }else{
    return -1;
  }

  if(fileType.compare("JPEG\n") == 0){
    return true;

  }else if(fileType.compare("PNG\n") == 0){
    return true;

  }else if(fileType.compare("AVI\n") == 0){
    return false;

  }else if(fileType.compare("MOV\n") == 0){
    return false;

  }else if(fileType.compare("WMV\n") == 0){
    return false;

  }else if(fileType.compare("MP4\n") == 0){
    return false;

  }else if(fileType.compare("M2TS\n") == 0){
    return false;

  }else{
    return -1;

  }

}

int typeOfFileInt(const char* path){ 
  detailedFile("typeOfFileInt"); detailedFile("⬇︎");

  return 0; 

  char* cmd = (char *) malloc (128 * sizeof(char));
  strcpy(cmd, "exiftool -FileType \"");
  strcat(cmd, path);
  strcat(cmd, "\"");

  string fileType = exec(cmd);

  if(!fileType.empty()){
    fileType = fileType.substr(34,fileType.length());
  }else{
    return -2;
  }
  cout << fileType << endl; 

  if(fileType.compare("JPEG\n") == 0){
    return 0;

  }else if(fileType.compare("PNG\n") == 0){
    return 1;

  }else if(fileType.compare("AVI\n") == 0){
    return 2;

  }else if(fileType.compare("MOV\n") == 0){
    return 3;

  }else if(fileType.compare("WMV\n") == 0){
    return 4;

  }else if(fileType.compare("MP4\n") == 0){
    return 5;

  }else if(fileType.compare("M2TS\n") == 0){
    return 6;

  }else{
    return -1;

  }

}

void fileVersion(const char *path, const char *pathToStore){ 
  detailedFile("fileVersion"); detailedFile("⬇︎");

  string originalDate = dateOfCreation(path);
  
  if(originalDate.empty()){ 
    
    FILE *corruptedFiles = fopen("corruptedFiles.txt", "a");
    if(corruptedFiles == NULL){ printf("Error while opening file.\n"); }
    fprintf(corruptedFiles,"%s\n",path);            

    return;

  }

  originalDateData *originalDateStruct = (originalDateData *) malloc (sizeof(originalDateData));
  originalDateStruct = dateReturn(originalDate);

  char *destinationPath = destinationFinder(originalDateStruct->year, originalDateStruct->month, pathToStore, typeOfFile(path));
 
  transfer(path, destinationPath);
  
  return;

}

void folderVersion(const char *path, const char *pathToStore, int *arg){ 
  detailedFile("folderVersion"); detailedFile("⬇︎");
  
  bool  isArgFree = true, 
        photoOnly = false,
        videoOnly = false;

  if(arg[7] == 1){ detailed  = 1; }
  if(arg[0] == 2){ photoOnly = true; }
  if(arg[0] == 3){ videoOnly = true; }

  for(int i = 0; i < 7; i++){
    if(arg[i] != -1){
      isArgFree = false;
      break;
    }
  }

  int j = 1;
  DIR           *d;
  struct dirent *dir;
  d = opendir(path);
  
  string dirFile,
  jpegOJ = ".jpg",  /**/  jpegTJ = ".JPG",
  jpegOP = ".png",  /**/  jpegTP = ".PNG",
  jpegOA = ".avi",  /**/  jpegTA = ".AVI",
  jpegOM = ".mov",  /**/  jpegTM = ".MOV",  
  jpegOW = ".wmv",  /**/  jpegTW = ".WMV",
  jpegOMP = ".mp4", /**/  jpegTMP = ".MP4",
  jpegOMT = ".mts", /**/  jpegTMT = ".MTS";

  size_t foundOJ,   /**/  foundTJ;
  size_t foundOP,   /**/  foundTP;
  size_t foundOA,   /**/  foundTA;
  size_t foundOM,   /**/  foundTM;
  size_t foundOW,   /**/  foundTW;
  size_t foundOMP,  /**/  foundTMP;
  size_t foundOMT,  /**/  foundTMT;

  char* imagePath       = (char*) malloc (32768 * sizeof(char));
  char* imagePathFinal  = (char*) malloc (32768 * sizeof(char));
  char* unknownPath     = (char*) malloc (32768 * sizeof(char));

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
      foundOMP = dirFile.find(jpegOMP);
      foundTMP = dirFile.find(jpegTMP);
      foundOMT = dirFile.find(jpegOMT);
      foundTMT = dirFile.find(jpegTMT);

      strcat(unknownPath, dir->d_name);

      if (foundOJ != string::npos || foundTJ != string::npos 
        || foundOP != string::npos || foundTP != string::npos 
        || foundOA != string::npos || foundTA != string::npos 
        || foundOM != string::npos || foundTM != string::npos 
        || foundOW != string::npos || foundTW != string::npos 
        || foundOMP != string::npos || foundTMP != string::npos 
        || foundOMT != string::npos || foundTMT != string::npos ){

        strcat(imagePath, dir->d_name);

        int length = (int) strlen(imagePath);
        for(int i = 0; i < length; i++){
          if(imagePath[i] == '.' 
            && i+1 <= length 
            && (imagePath[i+1] == '_' || imagePath[i+1] == 'D')){
            j = 0; break; 
          }
        }

        strcpy(imagePathFinal, path);
        strcat(imagePathFinal, "/");
        strcat(imagePathFinal, imagePath);

        if(j){
          if(photoOnly){
            if(typeOfFile(imagePathFinal))
              fileVersion(imagePathFinal, pathToStore);

          }else if(videoOnly){
            if(!typeOfFile(imagePathFinal))
              fileVersion(imagePathFinal, pathToStore);

          }else{
            if(isArgFree){
              fileVersion(imagePathFinal, pathToStore);
            }else if(arg[typeOfFileInt(imagePathFinal)] == 1){
              fileVersion(imagePathFinal, pathToStore);
            }

          }
          
        }

        j = 1;
        strcpy(imagePath, path);
        strcat(imagePath, "/");

      }else if(!isRegularFile(unknownPath) && (dirFile.find('.') == string::npos)){
        folderVersion(unknownPath, pathToStore, arg);

      }

      imagePath       = (char*) malloc (32768 * sizeof(char));
      imagePathFinal  = (char*) malloc (32768 * sizeof(char));
      unknownPath     = (char*) malloc (32768 * sizeof(char));

      strcpy(unknownPath, path);
      strcat(unknownPath, "/");

    }

    closedir(d);
    return ;
    
  }
  
}

void duplicateVersion(const char *path){ 
  detailedFile("duplicateVersion"); detailedFile("with path:"); detailedFile(path); detailedFile("⬇︎");

  int j = 1;
  DIR *d;
  struct dirent *dir;
  d = opendir(path);

  string dirFile;

  char* imagePath = (char*) malloc (32768 * sizeof(char));
  
  if (d) {
    
    while ((dir = readdir(d)) != NULL){

      dirFile = dir->d_name;
      strcpy(imagePath, path); strcat(imagePath, "/"); strcat(imagePath, dir->d_name);

      if(!isRegularFile(imagePath) && (dirFile.find('.') == string::npos)){
        printf("GOING IN %s\n", imagePath);
        duplicateVersion(imagePath);

      }else if ( typeOfFileInt(imagePath) != -1 ){ 

        int length = (int) strlen (dir->d_name);
        for( int i = 0; i < length; i++){
          if( dir->d_name[i] == '.' 
            && i+1 <= length 
            && (dir->d_name[i+1] == '_' 
            || dir->d_name[i+1] == 'D') ){
            j = 0; break; 
          }
        }
        
        if(j)
          duplicateCleaner(dir->d_name, path, typeOfFileInt(imagePath));

      }

      j = 1;
    }

    closedir(d);
    return ;
    
  }

}

void duplicateCleaner(const char *master, const char *path, int type){ 
  detailedFile("duplicateCleaner"); detailedFile("⬇︎");

  DIR *d;
  struct dirent *dir;
  d = opendir(path);
  
  char* masterPath  = (char*) malloc (32768 * sizeof(char));
  char* imagePath   = (char*) malloc (32768 * sizeof(char));

  strcpy(masterPath, path); strcat(masterPath, "/"); strcat(masterPath, master);
  strcpy(imagePath,  path); strcat(imagePath,  "/");

  if (d) {
    
    printf("> MASTER : %s, COMPARED TO, %s.\n",masterPath, path);

    while ((dir = readdir(d)) != NULL){

      strcpy(masterPath, path); strcat(masterPath, "/"); strcat(masterPath, master);
      strcpy(imagePath,  path); strcat(imagePath,  "/"); strcat(imagePath, dir->d_name);

      if(strcmp(dir->d_name, master) != 0){ 

        if ( type == typeOfFileInt(imagePath) ){ 
          
          duplicateCleanerExecution(masterPath, imagePath);

        }else if ( type == typeOfFileInt(imagePath) ){ 

          strcat(imagePath, dir->d_name);
          duplicateCleanerExecution(masterPath, imagePath);

        }else if ( type == typeOfFileInt(imagePath) ){ 

          strcat(imagePath, dir->d_name);
          duplicateCleanerExecution(masterPath, imagePath);

        }else if ( type == typeOfFileInt(imagePath) ){ 

          strcat(imagePath, dir->d_name);
          duplicateCleanerExecution(masterPath, imagePath);

        }else if ( type == typeOfFileInt(imagePath) ){ 

          strcat(imagePath, dir->d_name);
          duplicateCleanerExecution(masterPath, imagePath);

        }else if ( type == typeOfFileInt(imagePath) ){ 

          strcat(imagePath, dir->d_name);
          duplicateCleanerExecution(masterPath, imagePath);

        }else if ( type == typeOfFileInt(imagePath) ){

          strcat(imagePath, dir->d_name);
          duplicateCleanerExecution(masterPath, imagePath);

        }

      }

      strcpy(imagePath, path); strcat(imagePath, "/");
      strcpy(masterPath, path); strcat(masterPath, "/");

    }

    closedir(d);
    return ;
    
  }

}

void duplicateCleanerExecution(const char* imagePathMaster, const char* imagePathCandidate){ 
  detailedFile("duplicateCleanerExecution"); detailedFile("⬇︎");

  char* cmdOne    = (char*) malloc (65536 * sizeof(char));
  char* cmdTwo    = (char*) malloc (65536 * sizeof(char));
  char* cmdThree  = (char*) malloc (65536 * sizeof(char));
  char* cmdFour   = (char*) malloc (65536 * sizeof(char));

  strcpy(cmdOne,    "exiftool -FileSize \"");   strcat(cmdOne,    imagePathMaster);     strcat(cmdOne, "\""); 
  strcpy(cmdTwo,    "exiftool -FileSize \"");   strcat(cmdTwo,    imagePathCandidate);  strcat(cmdTwo, "\""); 
  strcpy(cmdThree,  "exiftool -ImageSize \"");  strcat(cmdThree,  imagePathMaster);     strcat(cmdThree, "\""); 
  strcpy(cmdFour,   "exiftool -ImageSize \"");  strcat(cmdFour,   imagePathCandidate);  strcat(cmdFour, "\""); 

  printf("> MASTER FILE : %s, CANDIDATE FILE, %s.\n",imagePathMaster, imagePathCandidate);

  if( isRegularFile(imagePathCandidate) ){ 
    printf(ACG "> > It is a file and is not hidden\n" ACRE);
    // is file and is not hidden 
      
      if( exec(cmdOne).compare(exec(cmdTwo)) == 0){ 
        printf(ACG "> > > > The sizes are the same\n" ACRE);
        // sizes are the same

        if( !dateOfCreation(imagePathMaster).empty() 
          && !dateOfCreation(imagePathCandidate).empty() 
          && dateOfCreation(imagePathMaster).compare(dateOfCreation(imagePathCandidate)) == 0){  
          printf(ACG "> > > > > The dates of creation are the same\n" ACRE);
          // dates of creation are the same

          if( exec(cmdThree).compare(exec(cmdFour)) == 0){  
            printf(ACG "> > > > > > The resolutions are the same\n" ACRE);
            // resolutions are the same

            if( strcmp(imagePathMaster, imagePathCandidate) > 0){ 
            printf(ACG "> > > The names are equal except for a slight variation\n" ACRE);
            // the names are equal except for a slight variation

              char* rmcmd = (char*) malloc (65536 * sizeof(char));
              
              strcpy(rmcmd, "rm -rf \"");
              strcat(rmcmd, imagePathCandidate);
              strcat(rmcmd, "\"");

              exec(rmcmd);

              detailedFile(rmcmd);
              detailedFile("\n===========");

              printf(ACG "> > > > > > => ");
              printf(ACBO "%s ( DELETED )\n\n" ACRE, rmcmd);
              return ;

            }else{

              char* rmcmd = (char*) malloc (65536 * sizeof(char));
              
              strcpy(rmcmd, "rm -rf \"");
              strcat(rmcmd, imagePathMaster);
              strcat(rmcmd, "\"");

              exec(rmcmd);

              detailedFile(rmcmd);
              detailedFile("\n===========");

              printf(ACG "> > > > > > => ");
              printf(ACBO "%s ( DELETED )\n\n" ACRE, rmcmd);
              return ;

            }

          }
          printf(ACR "> > > > > > The resolutions are the NOT same\n" ACRE);
          cout << endl << endl;
          return ;
        }
        printf(ACR "> > > > > The dates of creation are NOT the same\n" ACRE);
        cout << endl << endl;
        return ;
      }
      printf(ACR "> > > > The sizes are NOT the same\n" ACRE);
      cout << endl << endl;
      return ;
    }
    printf(ACR "> > It is NOT a file and is hidden\n" ACRE);
    cout << endl << endl;
    return ;

}
























