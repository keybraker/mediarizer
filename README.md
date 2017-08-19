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
```./mediaOrganizer /path/picture.jpg /destinationPath -mp4 -jpg```
will only copy jpg and mp4 files.

```./mediaOrganizer /path/picture.jpg /destinationPath -photo```
will only copy photos not videos.

```./mediaOrganizer -dup /Path```
will only copy photos not videos.

~~```./mediaOrganizer /path/picture.jpg /destinationPath -photo -jpg```~~ **! this is _NOT_ valid.**

##### Category:
 * -photo : _for photo organization only_
 * -video : _for video organization only_
   **( Attention: These modes can only be used solely )**

##### File type:**( You can use multiple flags, in order to transfer only the selected file types )**
 * -jpg : _for jpg organization only_
 * -png : _for png organization only_
 * -avi : _for avi organization only_
 * -mov : _for mov organization only_
 * -wmv : _for wmv organization only_
 * -mp4 : _for mp4 organization only_
 * -mts : _for mts organization only_

##### Information:**( You can use multiple flags, in order to transfer only the selected file types )**
 * -det : for a detailed list of executions in a txt format ( detailedTransfer.txt )

##### Mode:
 * -dup : duplicate mode deletes duplicate with diffrent names **( duplication cleaning is still in _BETA_ please _back up your files_ before attempting use with _caution_ and _on your own risk_ )**

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

* v1.5.0: 18 August 2017: Added duplication deletion.
* v1.1.2: 18 August 2017: Added -flags for a more controlled organisation.
* v1.1.1: 17 August 2017: Now photos and videos are separated in to diffrent folders for maximum organisation.
* v1.1.0: 17 August 2017: Huge improvement using [ExifTool](http://owl.phy.queensu.ca/~phil/exiftool/) as processing tool.
						  Basically everyfile is supported, implementations,
						  are on the way !
* v1.0.0: 12 August 2017: Full jpeg release with the help of [easyexif](http://owl.phy.queensu.ca/~phil/exiftool/)
* v0.1.0: 9  August 2017: Creation.

## Future Improvements and features 
1. Threads
2. support for more files
3. gps location organization

## Authors
* **Ioannis Tsiakkas** - *(Keybraker)* - [Keybraker](https://github.com/keybraker)

## Acknowledgments
* Phil Harvey with the exeptional [ExifTool](http://owl.phy.queensu.ca/~phil/exiftool/)

## License
* [Free Software](http://www.gnu.org/philosophy/free-sw.html)
