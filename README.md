# [Mediarizer](https://github.com/keybraker/Media-Organizer)
Organises all your media in a chronological order.

![alt text](https://raw.githubusercontent.com/keybraker/Media-Organizer/master/img/mediarizerLogo.png)

## How it works
```text
make       |----------------| ./mediaOrganizer /media.file /path/to/store       |------------------| 
---------> | mediaOrganizer |-------------------------------------------------> | organised photos | 
      	   |----------------| ./mediaOrganizer /path/folder /path/to/store      | in year/month    | 
                    |                                        	                |------------------| 
                    |
                    |         ./mediaOrganizer -dup /path/folder                |------------------| 
                    \---------------------------------------------------------> | duplicate free   | 
      	                                                                        | folders          | 
                                                            	                |------------------| 
```

![alt text](https://raw.githubusercontent.com/keybraker/Media-Organizer/master/img/mediarizerDisplay.jpg)
<br />**_( These is achieved in one run of the program )_**

Why use Media Organizer:
* Organises photos / videos extremly fast, the only limitation is your hardware
* Cleans your library from duplicates
* Lightweight and runs everywhere
***

## Installation Guide
#### 1. Clone this repository with ( or download zip ):
```
git clone https://github.com/keybraker/Mediarizer.git
```

#### 2. Install ExifTool by Phil Harvey
Download and install from here [ExifTool](http://owl.phy.queensu.ca/~phil/exiftool/).
<br />This program may very well be the best exif parser in the world (nj).
<br />This is the heart of the program and the essential tool that helped create this project.

## Usage Guide
#### 1. Open a terminal window and cd to cloned project
```
cd .../Mediarizer
```

#### 2. To compile the program just type:
```
make 
```

#### 3. Run the program:
##### a. Single image mode: Organises the one picture or video given to it.
```
./mediaOrganizer /path/media.file /path/to/store/folder
```
##### b. Folder mode: Organises all the pictures and videos in a folder, and the folders in it.
```
./mediaOrganizer /path/folder /path/to/store/folder
```
##### c. Duplicate mode: Deletes all duplicate pictures and videos in a folder, and the folders in it.
```
./mediaOrganizer -dup /path/folder
```
***

> Photos are copied to the new path if date information is available. <br />Same photos with same names, from diffrent folders are not being copied.

> To clean the program type ``` make clean ``` in ``` /Media-Organizer ```.

> All corrupted or unsupported files are not being copied. If even one file is copputed or unsupported, a txt file is created called ``` corruptedFiles ```, in which every corrupted or unsupported file is listed by its full path, so that you can handle it manually.

> Better run duplicate mode after organizing. It may be more cpu and time consuming but you can guarantee a fully, free of duplicates library due to the siple fact that duplicate files are only searched in current folder.

> Keep in mind that duplicate mode is in its early stages of production so better use it in small folders. Works best when you have already used media organizer and than done some more organizing of events due to making folders smaller.
***

_Duplicate Mode Output:_
```
> |-is file.        
> |-same size.      
> |-same date.      
> |-same res.       
> '-rm -rf "/path/to/file.type" ( deleted ).
```
![alt text](https://raw.githubusercontent.com/keybraker/Media-Organizer/master/img/mediarizerDuplicate.jpg)
<br />**_( These is achieved in one run of the program )_**

## Flags
Category | Explanation
---------| -------------
-photo	 | _for photo organization only_
-video	 | _for video organization only_
-jpg   	 | _for jpg organization only_
-png   	 | _for png organization only_
-avi   	 | _for avi organization only_
-mov   	 | _for mov organization only_
-wmv   	 | _for wmv organization only_
-mp4   	 | _for mp4 organization only_
-mts   	 | _for mts organization only_
-hlp   	 | _for Media Organizer User Guide_
-vrs   	 | _for Version infromation_
-dup   	 | _duplicate mode stores duplicates in file duplicatesToDelete.txt_
		 | _and than askes you to check the duplicates and delete them (use with caution)_
-dux   	 | _duplicate mode deletes duplicate when it finds the faster than normal verison_
		 | _but the machine will decide what last copy will be (use with caution)_
-del   	 | _deletion mode deletes all source files keeping only the copys in destination path_

* **You can use multiple flags, in order to transfer only the selected file types**

***
#### Flag Use Examples:
##### Flags can be put in any order you wish even in the middle of the directories, like this:
```
./mediaOrganizer -mp4 /path/source/folder -jpg /path/to/store/folder -png
```
is the same as,
```
./mediaOrganizer /path/source/folder /path/to/store/folder -mp4 -jpg -png
```
***
##### Will only copy jpg and mp4 files:
```
./mediaOrganizer -mp4 -jpg /path/source/folder /path/to/store/folder
```
is the same as,
```
./mediaOrganizer -mp4 /path/source/folder -jpg /path/to/store/folder
```
***
##### Will only copy photos not videos:
```
./mediaOrganizer /path/source/folder /path/to/store/folder -photo
```
***
##### Duplicates will be deleted:
```
./mediaOrganizer -dup /path/source/folder
```
***
##### **! Only _videos_ will be copied:**
```
./mediaOrganizer -video /path/media.file /path/to/store/folder -jpg
```
***
##### **! This is _NOT_ valid because -dup can only be used alone:**
~~```./mediaOrganizer -dup /path/media.file /path/to/store/folder -jpg```~~
***

## File support list 
### Photos: 
* jpeg
* png

### Videos: 
* avi
* mov
* wmv
* mp4
* m2ts

## Release History

* v1.7.0: 22 August 2017: Memory added, for stop and restart.
* v1.6.0: 20 August 2017: Fully functional duplication deletion.
* v1.5.0: 19 August 2017: Added duplication deletion.
* v1.1.2: 18 August 2017: Added -flags for a more controlled organisation.
* v1.1.1: 17 August 2017: Now photos and videos are separated in to diffrent folders for maximum organisation.
* v1.1.0: 17 August 2017: Huge improvement using [ExifTool](http://owl.phy.queensu.ca/~phil/exiftool/) as processing tool.
						  Basically everyfile is supported, implementations,
						  are on the way !
* v1.0.0: 12 August 2017: Full jpeg release with the help of [easyexif](http://owl.phy.queensu.ca/~phil/exiftool/)
* v0.1.0: 9  August 2017: Creation.

***
Future Improvements and features:
1. Threads
2. Support for more files
3. GPS location organization

***
Acknowledgments - **Phil Harvey** with the exeptional [**ExifTool**](http://owl.phy.queensu.ca/~phil/exiftool/)

***
Author - **Ioannis Tsiakkas** - *(Keybraker)* - [Keybraker](https://github.com/keybraker)

***
Copyright © 2017 [Media Organizer](https://github.com/keybraker/Media-Organizer) - Released under the [GNU LICENSE](http://www.gnu.org/philosophy/free-sw.html)


