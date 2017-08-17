# Media Organizer 
Organises all your media in a chronological order.

## How does it work 
```text
make  |----------------| ./mediaOrganizer /picture.jpg /desPath  |------------------| 
----> | mediaOrganizer |---------------------------------------> | organised photos | 
      |----------------| ./mediaOrganizer /folderPath /desPath   | in year/month    | 
                                                                 |------------------| 
```
![alt text](https://raw.githubusercontent.com/keybraker/Media-Organizer/master/MediaOrganizerDisplay.jpg)

## Why use Media Organiser
* Organises photos / videos extremly fast, the only limitation is your hardware
* Cleans your library from duplicates
* Lightweight and runs everywhere

## Installation Guide
Clone this repository with ( or download zip ):
```
git clone https://github.com/keybraker/Media-Organizer.git
```
##### Install ExifTool by Phil Harvey
Download and install from here [ExifTool](http://owl.phy.queensu.ca/~phil/exiftool/).
This program may very well be the best exif parser in the world (nj)
This is the heart of the program and the essential tool that helped create this project.

## Usage Guide
##### 1. Open a terminal window and cd to cloned project
```
cd .../Media-Organizer 
```

##### 2. To compile the program just type:
```
make 
```

##### 3. You can run the program in two ways, a single picture mode and a folder mode. The single picture only organises this one picture and to do that just type:
```
./mediaOrganizer /path/picture.jpg /destinationPath
```
If you want to organise all the picture in a folder, and the folders in them, just type :
```
./mediaOrganizer /path/folder /destinationPath
```

## Flags
Flags can only be used in the end of the command in whatever order you wish.
```
./mediaOrganizer /path/picture.jpg /destinationPath -mp4 -jpg
```
will only copy jpg and mp4 files.
```
./mediaOrganizer /path/picture.jpg /destinationPath -photo
```
will only copy photos not videos.

~~```./mediaOrganizer /path/picture.jpg /destinationPath -photo -jpg```~~ **! this is _NOT_ valid.**

##### Category:
 * -photo : for photo organization only
 * -video : for video organization only
   ( Attention: These modes can only be used solely )

##### File type:
 * -jpg : for jpg organization only
 * -png : for png organization only
 * -avi : for avi organization only
 * -mov : for mov organization only
 * -wmv : for wmv organization only
 * -mp4 : for mp4 organization only
 * -mts : for mts organization only

( You can use multiple flags, in order to transfer only the selected file types )

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
* m2ts

## Release History

* v1.1.2: 18 August 2017: Added -flags for a more controlled organisation.
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
