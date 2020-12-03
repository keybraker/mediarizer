<div id="1">
  
# [Mediarizer](https://github.com/keybraker/Media-Organizer)
![alt text](https://github.com/keybraker/Mediarizer/blob/updating-code-quality/img/new_mediarizer_logo.png)

Why use Media Organizer:
* Fast and easy organisation of photos / videos
* Lightweight and runs on all harware and OS

***

![alt text](https://raw.githubusercontent.com/keybraker/Media-Organizer/master/img/mediarizerDisplay.jpg)
<br>
>These is achieved in one run of the program

1. [Mediarizer](#1)
2. [Prerequisite and Build](#2)
    1. [Prerequisites](#2-1)
    2. [Build](#2-2)
3. [Usage Guide](#3)
    1. [Flags](#3-1)
    2. [Examples](#3-2)
    3. [Additional Information](#3-3)
4. [Information](#4)
    1. [Release History](#4-1)
    2. [Acknowledgements](#4-2)

<div id="2">
  
## Building, Installing, Using and Uninstalling Mediarizer

<div id="2-1">
  
### Prerequisites
1. Make sure you have downloaded g++ (on macOS clang++ is installed with Xcode installation).
2. If you want to achieve better performance you should download OpenMP for multithreading.
[ExifTool by Phil Harvey](http://owl.phy.queensu.ca/~phil/exiftool/) is used to parse metadata but is 
already implemented so there is no need for you to download it.

<div id="2-2">
  
### Build

1. Open a terminal window and cd to cloned project (Mediarizer)
```bash
cd Mediarizer
```

2. To compile the program just type:
```bash
make or make threaded
```

<div id="3">

## Usage Guide

<div id="3-1">

### Flags
| flag name		| flag acronym	| Argument 			| Description																| State		| Mandatory |
| :---			| :---			| :---: 			| :----																		| :---		| :--		|
| -input		| -i			| path / file		| _gives path to file or directory_											| working	| yes		|
| -output		| -o			| path				| _path to output directory_												| working	| yes		|
| -photo		| -p			| none 				| _organizes *only* photos_													| working	| no		|
| -video		| -e			| none				| _organizes *only* videos_													| working	| no		|
| -type			| -t			| type1, type2, ...	| _organizes *only* given [file type(s)](https://exiftool.org/#supported)_  | working	| no		|
| -delete		| -x			| none				| _deletes files in source directory_										| working	| no		|
| -duplicate	| -d			| none				| _duplicates are moved into duplicate folder in move directory_			| beta		| no		|
| -help			| -h			| none				| _displays a usage guide of Mediarizer_									| working	| no		|
| -version		| -v			| none				| _displays current version_												| working	| no		|

> a. Multiple flags can be used in conjunction<br>
> b. Multiple _[file types](https://exiftool.org/#supported)_ can be used as comma-separated string ex: -type jpg,png<br>
> c. Duplicate photos are compared by type, size, date and resolution, only than are they categorized as same<br>

***

<div id="3-2">

### Examples
a. single file sort
```bash
./mediarizer -i /path/media.file -o /path/to/store/folder
./mediarizer --input /path/media.file --output /path/to/store/folder
```

b. directory sort
```bash
./mediarizer -i /path/folder -o /path/to/store/folder
./mediarizer --input /path/folder --output /path/to/store/folder
```

c. flags can be used in any order
```
./mediarizer -i /path/source/folder -f mp4,jpg,png -o /path/to/store/folder
./mediarizer -o /path/to/store/folder -i /path/source/folder -f mp4,jpg,png
```

d. this execution will only sort _mp4_ and _jpg_ files to move direcotry
```bash
./mediarizer -i  /path/source/folder -o /path/to/store/folder -f mp4,jpg
```

e. will only copy photos _not_ videos:
```bash
./mediarizer -i /path/source/folder -o /path/to/store/folder -p
./mediarizer -i /path/source/folder -o /path/to/store/folder --photo
```

f. will only copy photos _not_ videos:
```bash
./mediarizer -i /path/source/folder -o /path/to/store/folder -v
./mediarizer -i /path/source/folder -o /path/to/store/folder --video
```

g. duplicates files will be moved to folder _"duplicates"_:
```bash
./mediarizer -i /path/source/folder -d
```

<div id="3-3">

### Additional Information
> a. from photos with same name, only the first encountered is moved to new directory<br>
> b. ```Makefile make clean``` will clear folder from executables<br>
> c. unsupported files are not being copied<br>
> d. corructed files may or may not cause the program to crash<br>

***

>If you encounter any problem or error please report it.<br>
>Create pull requests if you find and solve an error.<br>
![alt text](https://raw.githubusercontent.com/keybraker/Media-Organizer/master/img/tired.gif)

<div id="4">

## Information

<div id="4-1">

### Release History

* v2.0.0: 04 December	2020: Refactor application.
* v1.7.0: 22 August		2017: Memory added, for stop and restart.
* v1.6.0: 20 August		2017: Fully functional duplication deletion (BETA).
* v1.5.0: 19 August		2017: Added duplication deletion.
* v1.1.2: 18 August		2017: Added -flags for a more controlled organisation.
* v1.1.1: 17 August		2017: Now photos and videos are separated in to diffrent folders for maximum organisation.
* v1.1.0: 17 August		2017: Huge improvement using [ExifTool](http://owl.phy.queensu.ca/~phil/exiftool/) as processing tool.
* v1.0.0: 12 August		2017: Full jpeg release with the help of [easyexif](https://github.com/mayanklahiri/easyexif)
* v0.1.0: 09 August		2017: Initial commit.

<div id="4-2">

### Acknowledgements

>Acknowledgments - **Phil Harvey** with the exeptional [**ExifTool**](http://owl.phy.queensu.ca/~phil/exiftool/)<br>
>Author - **Ioannis Tsiakkas** - *(Keybraker)* - [Keybraker](https://github.com/keybraker)<br>
>License -Released under the [GNU LICENSE](http://www.gnu.org/philosophy/free-sw.html)<br><br>
>Copyright © 2020 [Mediarizer](https://github.com/keybraker/Media-Organizer) 
