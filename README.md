# Media Organizer 
Organises all your media in a chronological order.

## How does it work 
```text
make  |----------------| ./mediaOrganizer /picture.jpg /desPath  |------------------| 
----> | mediaOrganizer |---------------------------------------> | organised photos | 
      |----------------| ./mediaOrganizer /folderPath /desPath   | in year/month    | 
                                                                 |------------------| 
```
![alt text](https://raw.githubusercontent.com/keybraker/Media-Organizer/master/MediaOrgaanizerDisplay.jpg)

## Why use Picture Organiser
* Organises photos extremply fast, the only limitation is your hardware
* Cleans your photos from duplicates
* Lightweight and runs everywhere

## Installation Guide
Clone this repository with ( or download zip ):
```
git clone https://github.com/keybraker/Media-Organizer.git
```

## Usage Guide

##### 1. Install ExifTool by Phil Harvey
Download and install from here [ExifTool](http://owl.phy.queensu.ca/~phil/exiftool/).
This program may very well be the best exif parser in the world (nj)
This is the heart of the program and the essential tool that helped create this project.

##### 2. Open a terminal window and cd to cloned project
```
cd .../Media-Organizer 
```

##### 3. To compile the program just type:
```
make 
```

##### 4. You can run the program in two ways, a single picture mode and a folder mode. The single picture only organises this one picture and to do that just type:
```
./mediaOrganizer /path/picture.jpg /destinationPath
```
If you want to organise all the picture in a folder, and the folders in them, just type :
```
./mediaOrganizer /path/folder /destinationPath
```

## Coping Files
Photos are only copied once, so cleaning is done as-well !

## Corrupted files
All corrupted jpeg files are not being copied. If even one file is copputed, a txt file is
created called ``` corruptedFiles ``` in which every corrupted files is listed wby its full
path, so that you can handle it manually.

## Cleaning
* To clean the program type ``` make clean ``` in ``` /Media-Organizer ```

## Photo file support list 
* jpeg
* png

## Video file support list 
* avi
* mov
* wmv
* mp4

## Release History

* v1.1.1: 17 August 2017: Now photos and videos are separated in to diffrent folders for maximum organisation.
* v1.1.0: 17 August 2017: Huge improvement using [ExifTool](http://owl.phy.queensu.ca/~phil/exiftool/) as processing tool.
						  Basically everyfile is supported, implementations,
						  are on the way !
* v1.0.0: 12 August 2017: Full jpeg release with the help of [easyexif](http://owl.phy.queensu.ca/~phil/exiftool/)
* v0.1.0: 9  August 2017: Creation.

## Authors
* **Ioannis Tsiakkas** - *(Keybraker)* - [Keybraker](https://github.com/keybraker)

## Acknowledgments
* Phil Harvey with the exeptional [ExifTool](http://owl.phy.queensu.ca/~phil/exiftool/)

## License
* [Free Software](http://www.gnu.org/philosophy/free-sw.html)
