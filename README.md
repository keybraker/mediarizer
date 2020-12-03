# [Mediarizer](https://github.com/keybraker/Media-Organizer)
![alt text](https://github.com/keybraker/Mediarizer/blob/updating-code-quality/img/new_mediarizer_logo.png)

Why use Media Organizer:
* Fast and easy organisation of photos / videos
* Lightweight and runs on all harware and OS

***

## How it works
```text
make       |----------------| ./mediarizer /media.file /path/to/store           |------------------| 
---------> |   mediarizer   |-------------------------------------------------> | organised photos | 
      	   |----------------| ./mediarizer /path/folder /path/to/store          | in year/month    | 
                    |                                        	                |------------------| 
                    |
                    |         ./mediarizer -dup /path/folder                    |------------------| 
                    \---------------------------------------------------------> | duplicate free   | 
      	                                                                        | folders          | 
                                                            	                |------------------| 
```

![alt text](https://raw.githubusercontent.com/keybraker/Media-Organizer/master/img/mediarizerDisplay.jpg)
<br/>**_( This is achieved in one run of the program )_**

## Installation Guide

### Prerequisites
1. Make sure you have downloaded g++ (on macOS clang++ is installed with Xcode installation).
2. If you want to achieve better performance you should download OpenMP for multithreading.
[ExifTool by Phil Harvey](http://owl.phy.queensu.ca/~phil/exiftool/) is used to parse metadata but is 
already implemented so there is no need for you to download it.

### Installation

1. Open a terminal window and cd to cloned project
```
cd .../Mediarizer
```

2. To compile the program just type:
```
make or make threaded
```

## Usage Guide

### Simple execution

a. Single image mode: Organises the one picture or video given to it.
```
./mediarizer -i /path/media.file -o /path/to/store/folder
```

b. Folder mode: Organises all the pictures and videos in a folder, and the folders in it.
```
./mediarizer -i /path/folder -o /path/to/store/folder
```

### Extreme execution (flags)

## Flags
| flag name	| flag acronym	| Description																| State		|
| :---		| :---			| :----																		| :---		|
| -photo	| -p			| _organizes *only* photos_													| working	|
| -video	| -v			| _organizes *only* videos_													| working	|
| -type		| -t			| _organizes *only* given [file type(s)](https://exiftool.org/#supported)_  | working	|
| -del		| -d			| _deletes files in source directory_										| working	|
| -dup		| -s			| _duplicates are moved into duplicate folder in move directory_			| beta		|
| -dux		| -x			| _duplicates are deleted_													| beta		|
| -hlp		| -h			| _displays a usage guide of Mediarizer_									| working	|
| -vrs		| -v			| _displays current version_												| working	|

> Multiple flags can be used in conjunction 
> Multiple [file types](https://exiftool.org/#supported)_ can be used as comma-separated string ex: -type jpg,png
> Duplicate photos are compared by type, size, date and resolution, only than are they categorized as same

***

## Additional Information 

> from photos with same name, only the first encountered is moved to new directory
> ```Makefile make clean``` will clear folder from executables
> unsupported files are not being copied
> corructed files may or may not cause the program to crash

***

![alt text](https://raw.githubusercontent.com/keybraker/Media-Organizer/master/img/mediarizerDuplicate.jpg)
<br/>**_( These is achieved in one run of the program )_**

***
#### Flag Use Examples:
##### Flags can be put in any order you wish even in the middle of the directories, like this:
```
./mediarizer -mp4 -i /path/source/folder -jpg -o /path/to/store/folder -png
```
is the same as,
```
./mediarizer -i /path/source/folder -o /path/to/store/folder -mp4 -jpg -png
```
***
##### Will only copy jpg and mp4 files:
```
./mediarizer -mp4 -jpg -i  /path/source/folder -o /path/to/store/folder
```
***
##### Will only copy photos not videos:
```
./mediarizer -i /path/source/folder -o /path/to/store/folder -photo
```
***
##### Duplicates will be deleted:
```
./mediarizer -dup -i  /path/source/folder
```
***
##### **! Only _videos_ will be copied:**
```
./mediarizer -video /path/media.file /path/to/store/folder
```
***
##### **! This is _NOT_ valid because -dup can only be used alone:**
~~```./mediarizer -dup /path/media.file /path/to/store/folder -jpg```~~
***

**If you encounter any problem report it.** ![alt text](https://raw.githubusercontent.com/keybraker/Media-Organizer/master/img/tired.gif)
**Create pull requests if you find and solve an error.** 

## Release History

* v2.0.0: 04 December 2020: Refactor application.
* v1.7.0: 22 August   2017: Memory added, for stop and restart.
* v1.6.0: 20 August   2017: Fully functional duplication deletion (BETA).
* v1.5.0: 19 August   2017: Added duplication deletion.
* v1.1.2: 18 August   2017: Added -flags for a more controlled organisation.
* v1.1.1: 17 August   2017: Now photos and videos are separated in to diffrent folders for maximum organisation.
* v1.1.0: 17 August   2017: Huge improvement using [ExifTool](http://owl.phy.queensu.ca/~phil/exiftool/) as processing tool.
Basically every file is supported, implementations, are on the way !
* v1.0.0: 12 August 2017: Full jpeg release with the help of [easyexif](http://owl.phy.queensu.ca/~phil/exiftool/)
* v0.1.0: 9  August 2017: Creation.


***
Acknowledgments - **Phil Harvey** with the exeptional [**ExifTool**](http://owl.phy.queensu.ca/~phil/exiftool/)

***
Author - **Ioannis Tsiakkas** - *(Keybraker)* - [Keybraker](https://github.com/keybraker)

***
Copyright © 2020 [Media Organizer](https://github.com/keybraker/Media-Organizer) - Released under the [GNU LICENSE](http://www.gnu.org/philosophy/free-sw.html)


