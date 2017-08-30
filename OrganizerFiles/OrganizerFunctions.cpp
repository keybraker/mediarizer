#include "Organizer.h"

using namespace std;

#define SPACING 110

int     hundredP = -1,
        currentP = 0,
        deleteMode = 0,
        duplicateSimple = 1,
        singlePresisionFiles = -1;
float   currentSize = 0;

int hundredPercent(const char* path){

  char *cmd = (char *) malloc (128 * sizeof(char));

  strcpy(cmd, "find \"");
  strcat(cmd, path);
  strcat(cmd, "\" -type f | wc -l");

  return (stoi(exec(cmd)));

}

void percentige(){

  currentP += 1;

  if(((currentP * 100)/(hundredP)) > 100){
    if(currentSize < 1024){
      printf(ACY "\r[%3d%%][%7.2f Mb]" ACRE, 100, (float) currentSize);
    }else{
      printf(ACY "\r[%3d%%][%7.2f Gb]" ACRE, 100, (float) currentSize / 1024);
    }
  }else{
    if(currentSize < 1024){
      printf(ACY "\r[%3d%%][%7.2f Mb]" ACRE, ((currentP*100) / (hundredP)), (float) currentSize);
    }else{
      printf(ACY "\r[%3d%%][%7.2f Gb]" ACRE, ((currentP*100) / (hundredP)), (float) currentSize / 1024);
    }
  }

}

void duplicateFound(const char* string, const char* string2){

  FILE *dupFile = fopen("duplicatesToDelete.txt", "a");
  if(dupFile == NULL){ printf("Error while opening file.\n"); }
  fprintf(dupFile, "%s\n", string);
  fprintf(dupFile, "%s (saved)\n", string2);
  fclose(dupFile);

}

void duplicateRmer(void){

  FILE* dupFile = fopen("duplicatesToDelete.txt", "r");
  if(dupFile == NULL) return;
  char line[256];

  int i = 1;
  while (fgets(line, sizeof(line), dupFile)) {
    if(strlen(line) != 0){

      if(i == 1){
        line[strlen(line) - 1] = 0;
        char* rmcmd = (char*) malloc (8096 * sizeof(char));
                
        strcpy(rmcmd, "rm -rf \"");
        strcat(rmcmd, line);
        strcat(rmcmd, "\"");

        exec(rmcmd);
        
        printf(ACG "%-38s%-20s\n" ACRE, " deleting file ... ", rmcmd);

      }

    }
    i++;
    if(i == 3) i = 1;
  }
  fclose(dupFile);

  exec("rm -rf duplicatesToDelete.txt");
  printf(ACG "%-38s%-20s\n" ACRE, "", "rm -rf duplicatesToDelete.txt");

}

void folderSigning(const char* path, int version){ 

  if(version == 1){
    printf(ACY "%-22s%-1s%-50s\n" ACRE, "[----organized---]> sign ", "[ ", path); //"> organized & signed"
    //printf(ACY ">> Path %s, organized and signed.\n" ACRE, path);
    FILE *folderSigning = fopen("folderSigning.txt", "a");
    if(folderSigning == NULL){ printf("Error while opening file.\n"); }
    fprintf(folderSigning, "%s\n", path);
    fclose(folderSigning);
  }else{
    printf(ACY "%-37s%-1s%-121s\n" ACRE, "[-----cleaned----]> signed path: ", "[ ", path);
    //printf(ACY ">> Path %s, cleaned and signed.\n" ACRE, path);
    FILE *folderSigningDuplicate = fopen("folderSigningDuplicate.txt", "a");
    if(folderSigningDuplicate == NULL){ printf("Error while opening file.\n"); }
    fprintf(folderSigningDuplicate, "%s\n", path);
    fclose(folderSigningDuplicate);
  }

}

bool folderAlreadyOrganized(const char* string, int version){

  if(version == 1){
    FILE* file = fopen("folderSigning.txt", "r");
    if(file == NULL) return 0;
    char line[256];

    while (fgets(line, sizeof(line), file)) {
      if(strlen(line) != 0){
        line[strlen(line) - 1] = 0;
        if(!strcmp(line, string)){
          return 1;
        }
      }
    }
    fclose(file);

  }else{
    FILE* file = fopen("folderSigningDuplicate.txt", "r");
    if(file == NULL) return 0;
    char line[256];

    while (fgets(line, sizeof(line), file)) {
      if(strlen(line) != 0){
        line[strlen(line) - 1] = 0;
        if(!strcmp(line, string)){
          return 1;
        }
      }
    }
    fclose(file);

  }

  return 0;

}

string exec(const char* cmd) { 
    
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

  // ADDING SIZE TRANSFERED
  char* cmd = (char*) malloc (32768 * sizeof(char));
  strcpy(cmd, "exiftool -FileSize \""); strcat(cmd, source); strcat(cmd, "\"");
  
  char* transfer = (char*) malloc (32768 * sizeof(char));
  char* rmcmd = (char*) malloc (32768 * sizeof(char));

  /****COPY THE SOURCE TO DESTINATION*******************/
  strcpy(transfer, "sudo cp \"");
  strcat(transfer, source);
  strcat(transfer, "\" ");
  strcat(transfer, dest);

  system(transfer);

  /****DELETE THE SOURCE FILE***************************/
  if(deleteMode) {
    strcpy(rmcmd, "rm -rf \"");
    strcat(rmcmd, source);
    strcat(rmcmd, "\"");

    exec(rmcmd);
  }
  /*****************************************************/
  string destEdit = dest;
  destEdit = destEdit.substr(0, destEdit.length() - 1);
  destEdit = destEdit.substr(1).append(destEdit.substr(0,1));
  destEdit = destEdit.substr(0, destEdit.length() - 1);

  printf(ACG "> copy %-1s%-50s\n" ACRE, "[ ", source);
  printf(ACG "%-20s%-4s%-1s%-50s\n" ACRE, "", "'--> ", "[ ", destEdit.c_str());

  if(deleteMode){  
    printf(ACG "%-20s%-7s%-1s%-50s\n" ACRE, "", "> rm", "[ ", source);
  }

  string fileSize;
  fileSize = exec(cmd);
  if(fileSize.c_str()[strlen(fileSize.c_str())-3] == 'k'){
    currentSize += stof(fileSize.substr(34, fileSize.length()))/1024;

  }else if(fileSize.c_str()[strlen(fileSize.c_str())-3] == 'M'){
    currentSize += stof(fileSize.substr(34, fileSize.length()));

  }else{
    currentSize += stof(fileSize.substr(34, fileSize.length()))*1024;
    
  }

  return 0;

}

string dateOfCreation(const char *path){ 
  
  char* cmd = (char *) malloc (32768 * sizeof(char));
  strcpy(cmd, "exiftool -FileType \"");
  strcat(cmd, path);
  strcat(cmd, "\"");

  string fileType = exec(cmd);

  if(!fileType.empty()){
    fileType = fileType.substr(34, fileType.length());
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

    if(!fileDate.empty()){
      return fileDate.substr(34, fileDate.length());

    }else{
      strcpy(cmd, "exiftool -ProfileDateTime \"");
      strcat(cmd, path);
      strcat(cmd, "\"");
      fileDate = exec(cmd);

      if(!fileDate.empty())
        return fileDate.substr(34, fileDate.length());
      
    }

  }else if(fileType.compare("PNG\n") == 0){
    // cout << "(PNG)  ";
    strcpy(cmd, "exiftool -CreateDate \"");
    strcat(cmd, path);
    strcat(cmd, "\"");
    fileDate = exec(cmd);
 
    if(!fileDate.empty()){
      return fileDate.substr(34, fileDate.length());

    }else{
      strcpy(cmd, "exiftool -ProfileDateTime \"");
      strcat(cmd, path);
      strcat(cmd, "\"");
      fileDate = exec(cmd);

      if(!fileDate.empty())
        return fileDate.substr(34, fileDate.length());
      
    }

  }else if(fileType.compare("AVI\n") == 0){
    // cout << "(AVI)  ";
    strcpy(cmd, "exiftool -DateTimeOriginal \"");
    strcat(cmd, path);
    strcat(cmd, "\"");
    fileDate = exec(cmd);

    if(!fileDate.empty())
      return fileDate.substr(34, fileDate.length());

  }else if(fileType.compare("MOV\n") == 0){
    // cout << "(MOV)  ";
    strcpy(cmd, "exiftool -CreateDate \"");
    strcat(cmd, path);
    strcat(cmd, "\"");
    fileDate = exec(cmd);

    if(!fileDate.empty())
      return fileDate.substr(34, fileDate.length());

  }else if(fileType.compare("WMV\n") == 0){
    // cout << "(WMV)  ";
    strcpy(cmd, "exiftool -CreationDate \"");
    strcat(cmd, path);
    strcat(cmd, "\"");
    fileDate = exec(cmd);

    if(!fileDate.empty())
      return fileDate.substr(34, fileDate.length());

  }else if(fileType.compare("MP4\n") == 0){
    // cout << "(MP4)  ";
    strcpy(cmd, "exiftool -CreateDate \"");
    strcat(cmd, path);
    strcat(cmd, "\"");
    fileDate = exec(cmd);

    if(!fileDate.empty())    
      return fileDate.substr(34, fileDate.length());

  }else if(fileType.compare("M2TS\n") == 0){
    // cout << "(M2TS) ";
    strcpy(cmd, "exiftool -DateTimeOriginal \"");
    strcat(cmd, path);
    strcat(cmd, "\"");
    fileDate = exec(cmd);

    if(!fileDate.empty())
      return fileDate.substr(34, fileDate.length());

  }

  return string(); // empty string
    
}

bool isDir(const char* path) {
  
  struct stat sb;
  if (stat(path, &sb) == 0 && S_ISDIR(sb.st_mode))
    return true;

  return false;

}

int isFile(const char *path){ 

  struct stat path_stat;
  stat(path, &path_stat);
  return S_ISREG(path_stat.st_mode);

}

originalDateData *dateReturn(string originalDate){ 
  
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
    
  DIR* dir = opendir(directory);
  if (dir) {
    closedir(dir);
    return true;
  }
  return false;

}

char *destinationFinder(int year, int month, const char *pathToStore, bool type){ 
  
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

  if(hundredP == -1){ hundredP = 1; }

  percentige();
  string originalDate = dateOfCreation(path);

  if(originalDate.empty()){ 
    
    printf(ACR "> crpt %-1s%-50s\n" ACRE, "[ ", path);
    FILE *corruptedFiles = fopen("corruptedFiles.txt", "a");
    if(corruptedFiles == NULL){ printf("Error while opening file.\n"); }
    fprintf(corruptedFiles,"%s\n",path);            
    fclose(corruptedFiles);

    char *destinationPath = (char *) malloc (32768 * sizeof(char));

    strcpy(destinationPath, pathToStore);
    strcat(destinationPath, "/unknown");

    if(!dirEx(destinationPath)){
      strcpy(destinationPath, "mkdir \"");
      strcat(destinationPath, pathToStore);
      strcat(destinationPath, "/unknown\"");

      system(destinationPath);
    }

    if(typeOfFile(path)){

      strcpy(destinationPath, pathToStore);
      strcat(destinationPath, "/unknown/photos");

      if(!dirEx(destinationPath)){
        strcpy(destinationPath, "mkdir \"");
        strcat(destinationPath, pathToStore);
        strcat(destinationPath, "/unknown/photos\"");

        system(destinationPath);
      }

      strcpy(destinationPath, "\"");
      strcat(destinationPath, pathToStore);
      strcat(destinationPath, "/unknown/photos\"");
      
      percentige();
      transfer(path, destinationPath);

    }else{

      strcpy(destinationPath, pathToStore);
      strcat(destinationPath, "/unknown/videos");

      if(!dirEx(destinationPath)){
        strcpy(destinationPath, "mkdir \"");
        strcat(destinationPath, pathToStore);
        strcat(destinationPath, "/unknown/videos\"");

        system(destinationPath);
      }

      strcpy(destinationPath, "\"");
      strcat(destinationPath, pathToStore);
      strcat(destinationPath, "/unknown/videos\"");

      percentige();
      transfer(path, destinationPath);

    }

    return;

  }

  originalDateData *originalDateStruct = (originalDateData *) malloc (sizeof(originalDateData));
  originalDateStruct = dateReturn(originalDate);

  char *destinationPath = destinationFinder(originalDateStruct->year, originalDateStruct->month, pathToStore, typeOfFile(path));

  /*******************************CHECKING IF FILE ALREADY EXISTS*******************************/
  int ctr;
  for(int i = 0; i < (int) strlen(path); i++)
    if(path[i] == '/') ctr = i;
  
  string begin = path, final, existance; 
  final = begin.substr (ctr, strlen(path));
  begin = destinationPath;
  begin = begin.substr(0, begin.length() - 1);
  begin = begin.substr(1).append(begin.substr(0,1));
  begin = begin.substr(0, begin.length() - 1);
  existance = begin + final;

  if(isFile(existance.c_str())){ // if file already exists 
    printf(ACG "> exst %-1s", "[ ");
    printf(ACG "%-50s\n" ACRE, existance.c_str());
    return;

  }
  /*********************************************************************************************/

  transfer(path, destinationPath);
  
  return;

}

void folderVersion(const char *path, const char *pathToStore, int *arg){ 

  if(folderAlreadyOrganized(path, 1)){
    currentP += hundredPercent(path);
    printf(ACY "Path: %s, has already been organised.\n", path);
    printf(    "If you wish to organise it again, please ");
    printf(    "delete the path reference from folderSigning.txt\n" ACRE);
    return;
  }

  if(hundredP == -1){
    hundredP = hundredPercent(path);
  }

  // else{
  //   hundredP -= 1;
  // }
  
  bool  isArgFree = true, 
        photoOnly = false,
        videoOnly = false;

  if(arg[8] == 1){ photoOnly = true; }
  if(arg[9] == 1){ videoOnly = true; }
  if(arg[11] == 1){ deleteMode = 1; }

  for(int i = 0; i < 9; i++){
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
          if(photoOnly && videoOnly){
            fileVersion(imagePathFinal, pathToStore);

          }else if(photoOnly){
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

      }else if(!isFile(unknownPath) && (dirFile.find('.') == string::npos)){
        folderVersion(unknownPath, pathToStore, arg);

      }

      imagePath       = (char*) malloc (32768 * sizeof(char));
      imagePathFinal  = (char*) malloc (32768 * sizeof(char));
      unknownPath     = (char*) malloc (32768 * sizeof(char));

      strcpy(unknownPath, path);
      strcat(unknownPath, "/");

    }

    closedir(d);
    folderSigning(path, 1);

    return ;
    
  }
  
}

void duplicateVersion(const char *path, int xtrm){ 

  if(xtrm) duplicateSimple = 0;

  if(folderAlreadyOrganized(path, 2)){
    currentP += hundredPercent(path);
    printf(ACY "Path: %s, has already been searched and cleaned for duplicates.\n", path);
    printf(    "If you wish to organise it again, please ");
    printf(    "delete the path reference from folderSigningDuplicated.txt\n" ACRE);
    return;
  }

  if(hundredP == -1){
    hundredP = hundredPercent(path);
    singlePresisionFiles = hundredP;
    hundredP = hundredP*hundredP;

  }

  int j = 1, length = 0;
  DIR *d;
  struct dirent *dir;
  d = opendir(path);

  string dirFile;

  char* imagePath = (char*) malloc (32768 * sizeof(char));
  
  if (d) {

    while ((dir = readdir(d)) != NULL){

      dirFile = dir->d_name;
      strcpy(imagePath, path); strcat(imagePath, "/"); strcat(imagePath, dir->d_name);

      if(!isFile(imagePath) && (dirFile.find('.') == string::npos)){
        printf(ACG "%-18s%-20s%-1s%-50s\n" ACRE, "", "> going to path:", "[ ", imagePath);
        duplicateVersion(imagePath, xtrm);

      }else if ( typeOfFileInt(imagePath) != -1 ){ 

        length = (int) strlen (dir->d_name);
        for( int i = 0; i < length; i++){
          if( dir->d_name[i] == '.' 
            && i+1 <= length 
            && (dir->d_name[i+1] == '_' 
            || dir->d_name[i+1] == 'D') ){
            j = 0; break; 
          }
        }

        if(j)
          if(strlen(dir->d_name) > 2 || ( strlen(dir->d_name) == 1 && dir->d_name[0] != '.' ) || ( strlen(dir->d_name) == 2 && ( dir->d_name[0] != '.' || dir->d_name[1] != '.' )))
            duplicateCleaner(dir->d_name, path, typeOfFileInt(imagePath));

      }

      j = 1;
      length = 0;
    }

    closedir(d);
    folderSigning(path, 2);

    return ;
    
  }

}

void duplicateCleaner(const char *master, const char *path, int type){ 

  int j = 1, length = 0;
  DIR *d;
  struct dirent *dir;
  d = opendir(path);
  
  char* masterPath  = (char*) malloc (32768 * sizeof(char));
  char* imagePath   = (char*) malloc (32768 * sizeof(char));

  strcpy(masterPath, path); strcat(masterPath, "/"); strcat(masterPath, master);
  strcpy(imagePath,  path); strcat(imagePath,  "/");

  if (d) {
    while ((dir = readdir(d)) != NULL){

      strcpy(masterPath, path); strcat(masterPath, "/"); strcat(masterPath, master);
      strcpy(imagePath,  path); strcat(imagePath,  "/"); strcat(imagePath, dir->d_name);

      length = (int) strlen (path);
      for( int i = 0; i < length; i++){
        if( path[i] == '.' 
          && i+1 <= length 
          && (path[i+1] == '_' 
          || path[i+1] == 'D') ){
          j = 0; break; 
        }
      }

      if(j && strcmp(dir->d_name, master) != 0){ 

        percentige();
        printf(ACG "%-20s%-1s%-50s\n" ACRE, "> info check for:", "[ ", masterPath);
        printf(ACG "%-20s%-18s%-1s%-50s\n" ACRE, "", " '--------------> ", "[ ", path);

        if ( type == typeOfFileInt(imagePath) ){ 

          if ( strlen(dir->d_name) > 2 || ( strlen(dir->d_name) == 1 && dir->d_name[0] != '.' ) || ( strlen(dir->d_name) == 2 && ( dir->d_name[0] != '.' || dir->d_name[1] != '.' )  ) )
            duplicateCleanerExecution(masterPath, imagePath);

        }else if ( type == typeOfFileInt(imagePath) ){ 

          if ( strlen(dir->d_name) > 2 || ( strlen(dir->d_name) == 1 && dir->d_name[0] != '.' ) || ( strlen(dir->d_name) == 2 && ( dir->d_name[0] != '.' || dir->d_name[1] != '.' )  ) )
            duplicateCleanerExecution(masterPath, imagePath);

        }else if ( type == typeOfFileInt(imagePath) ){ 

          if ( strlen(dir->d_name) > 2 || ( strlen(dir->d_name) == 1 && dir->d_name[0] != '.' ) || ( strlen(dir->d_name) == 2 && ( dir->d_name[0] != '.' || dir->d_name[1] != '.' )  ) )
            duplicateCleanerExecution(masterPath, imagePath);

        }else if ( type == typeOfFileInt(imagePath) ){ 

          if ( strlen(dir->d_name) > 2 || ( strlen(dir->d_name) == 1 && dir->d_name[0] != '.' ) || ( strlen(dir->d_name) == 2 && ( dir->d_name[0] != '.' || dir->d_name[1] != '.' )  ) )
            duplicateCleanerExecution(masterPath, imagePath);

        }else if ( type == typeOfFileInt(imagePath) ){ 

          if ( strlen(dir->d_name) > 2 || ( strlen(dir->d_name) == 1 && dir->d_name[0] != '.' ) || ( strlen(dir->d_name) == 2 && ( dir->d_name[0] != '.' || dir->d_name[1] != '.' )  ) )
            duplicateCleanerExecution(masterPath, imagePath);

        }else if ( type == typeOfFileInt(imagePath) ){ 

          if ( strlen(dir->d_name) > 2 || ( strlen(dir->d_name) == 1 && dir->d_name[0] != '.' ) || ( strlen(dir->d_name) == 2 && ( dir->d_name[0] != '.' || dir->d_name[1] != '.' )  ) )
            duplicateCleanerExecution(masterPath, imagePath);

        }else if ( type == typeOfFileInt(imagePath) ){

          if ( strlen(dir->d_name) > 2 || ( strlen(dir->d_name) == 1 && dir->d_name[0] != '.' ) || ( strlen(dir->d_name) == 2 && ( dir->d_name[0] != '.' || dir->d_name[1] != '.' )  ) )
            duplicateCleanerExecution(masterPath, imagePath);

        }

      }

      strcpy(imagePath, path); strcat(imagePath, "/");
      strcpy(masterPath, path); strcat(masterPath, "/");
      j = 1;
      length = 0;
    }

    closedir(d);
    currentP += singlePresisionFiles;
    return ;
    
  }

}

void duplicateCleanerExecution(const char* imagePathMaster, const char* imagePathCandidate){ 
  
  //currentP += 1; if currentP += hundredPercent(path); didnt exist in duplicateCleaner

  char* cmdOne    = (char*) malloc (8096 * sizeof(char));
  char* cmdTwo    = (char*) malloc (8096 * sizeof(char));

  strcpy(cmdOne,  "exiftool -FileSize -ImageSize -BrightnessValue -ThumbnailImage \""); strcat(cmdOne, imagePathMaster);     strcat(cmdOne, "\""); 
  strcpy(cmdTwo,  "exiftool -FileSize -ImageSize -BrightnessValue -ThumbnailImage \""); strcat(cmdTwo, imagePathCandidate);  strcat(cmdTwo, "\""); 

  percentige();
  printf(ACG "%-20s%-1s%-50s\n" ACRE, "> double check for:", "[ ", imagePathMaster);
  printf(ACG "%-20s%-18s%-1s%-50s\n" ACRE, "", " '--------------> ", "[ ", imagePathCandidate);

  if(duplicateSimple){ // first check is name check so that it is very fast but only looks at similar names

    if( strlen(imagePathMaster) <= strlen(imagePathCandidate) && strncmp(imagePathMaster, imagePathCandidate, strlen(imagePathMaster)-5) == 0){ 
      printf(ACG "%-38s%-20s" ACRE, "", "|--similar name.");
      // the names are equal except for a slight variation

      if( isFile(imagePathCandidate) ){ 
        printf(ACG "\n%-38s%-20s" ACRE, "", "|--is file.");
        // is file and is not hidden

          if( exec(cmdOne).compare(exec(cmdTwo)) == 0){ 
            printf(ACG "\n%-38s%-20s" ACRE, "", "|--same check.");
            // sizes are the same

              char* rmcmd = (char*) malloc (8096 * sizeof(char));
              
              strcpy(rmcmd, "rm -rf \"");
              strcat(rmcmd, imagePathCandidate);
              strcat(rmcmd, "\"");

              // string answer;
              // cout << endl << "About to delete: " << imagePathCandidate << " , to approve, press y: " ;
              // cin >> answer;
              // if(answer == "y"){
              //   exec(rmcmd);
              // }else{
              //   cout << "didn't rm" << endl;
              // }
              
              // exec(rmcmd);

              duplicateFound(imagePathCandidate, imagePathMaster);

              printf(ACG "\n%-38s'--%s ( stored for deletion ).\n\n" ACRE, "", rmcmd);

              // ADDING SIZE DELETED
              char* cmd = (char*) malloc (32768 * sizeof(char));
              strcpy(cmd, "exiftool -FileSize \""); strcat(cmd, imagePathMaster); strcat(cmd, "\"");
              
              string fileSize;
              fileSize = exec(cmd);

              if(fileSize.c_str()[strlen(fileSize.c_str())-3] == 'k'){
                currentSize += stof(fileSize.substr(34, fileSize.length()))/1024;

              }else if(fileSize.c_str()[strlen(fileSize.c_str())-3] == 'M'){
                currentSize += stof(fileSize.substr(34, fileSize.length()));

              }else{
                currentSize += stof(fileSize.substr(34, fileSize.length()))*1024;
              }

              return ;

            }
            printf(ACR "\n%-38s'--the check NOT true.\n\n" ACRE, "");
            return ;
          }
          printf(ACR "\n%-38s'--it is NOT a file.\n\n" ACRE, "");
          return ;
        }
        printf(ACR "%-38s'--names are not similar.\n\n" ACRE, "");
        return ;

  } else { // thoroughly check for every file

    if( strlen(imagePathMaster) <= strlen(imagePathCandidate) && strncmp(imagePathMaster, imagePathCandidate, strlen(imagePathMaster)-5) == 0){ 
      printf(ACG "%-38s%-20s" ACRE, "", "|--similar name.");
      // the names are equal except for a slight variation

      if( isFile(imagePathCandidate) ){ 
        printf(ACG "\n%-38s%-20s" ACRE, "", "|--is file.");
        // is file and is not hidden

        if( exec(cmdOne).compare(exec(cmdTwo)) == 0){ 
          printf(ACG "\n%-38s%-20s" ACRE, "", "|--same check.");
          // sizes are the same

          char* rmcmd = (char*) malloc (8096 * sizeof(char));
          
          strcpy(rmcmd, "rm -rf \"");
          strcat(rmcmd, imagePathCandidate);
          strcat(rmcmd, "\"");

          // string answer;
          // cout << endl << "About to delete: " << imagePathCandidate << " , to approve, press y: " ;
          // cin >> answer;
          // if(answer == "y"){
          //   exec(rmcmd);
          // }else{
          //   cout << "didn't rm" << endl;
          // }
          
          exec(rmcmd);

          printf(ACG "\n%-38s'--%s ( stored for deletion ).\n\n" ACRE, "", rmcmd);

          // ADDING SIZE DELETED
          char* cmd = (char*) malloc (32768 * sizeof(char));
          strcpy(cmd, "exiftool -FileSize \""); strcat(cmd, imagePathMaster); strcat(cmd, "\"");
          
          string fileSize;
          fileSize = exec(cmd);

          if(fileSize.c_str()[strlen(fileSize.c_str())-3] == 'k'){
            currentSize += stof(fileSize.substr(34, fileSize.length()))/1024;

          }else if(fileSize.c_str()[strlen(fileSize.c_str())-3] == 'M'){
            currentSize += stof(fileSize.substr(34, fileSize.length()));

          }else{
            currentSize += stof(fileSize.substr(34, fileSize.length()))*1024;
          }

          return ;

        }
        printf(ACR "\n%-38s'--the check NOT true.\n\n" ACRE, "");
        return ;
      }
      printf(ACR "\n%-38s'--it is NOT a file.\n\n" ACRE, "");
      return ;
    }
    printf(ACR "%-38s'--names are not similar.\n\n" ACRE, "");
    return ;

  }

}























