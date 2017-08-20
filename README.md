# Media Organizer 
Organises all your media in a chronological order.

## How does it work 
```text
make       |----------------| ./mediaOrganizer /picture.jpg /desPath            |------------------| 
---------> | mediaOrganizer |-------------------------------------------------> | organised photos | 
      	   |----------------| ./mediaOrganizer /folderPath /desPath             | in year/month    | 
                                                            	                |------------------| 
```
![alt text](https://raw.githubusercontent.com/keybraker/Media-Organizer/master/MediaOrganizerDisplay.jpg)
<br />**_( These is achieved in one run of the program )_**

## Why use Media Organiser
* Organises photos / videos extremly fast, the only limitation is your hardware
* Cleans your library from duplicates
* Lightweight and runs everywhere

## Installation Guide
#### 1. Clone this repository with ( or download zip ):
```
git clone https://github.com/keybraker/Media-Organizer.git
```
#### 2. Install ExifTool by Phil Harvey
Download and install from here [ExifTool](http://owl.phy.queensu.ca/~phil/exiftool/).
 <br />This program may very well be the best exif parser in the world (nj).
 <br />This is the heart of the program and the essential tool that helped create this project.

## Usage Guide
#### 1. Open a terminal window and cd to cloned project
```
cd .../Media-Organizer 
```

#### 2. To compile the program just type:
```
make 
```

#### 3. Run the program:
##### a. Single image mode: Organises the one picture or video given to it.
```
./mediaOrganizer /path/picture.jpg /destinationPath
```
##### b. Folder mode: Organises all the pictures and videos in a folder, and the folders in it.
```
./mediaOrganizer /path/folder /destinationPath
```
###### Photos are copied to the new path if date information is available. <br />Same photos with same names, from diffrent folders are not being copied.
###### To clean the program type ``` make clean ``` in ``` /Media-Organizer ```

##### c. Duplicate mode: Deletes all duplicate pictures and videos in a folder, and the folders in it.
```
./mediaOrganizer -dup /path/folder
```
_Output:_
```
> > It is a file and is not hidden
> > > The names are equal except for a slight variation
> > > > The sizes are the same
> > > > > The dates of creation are the same
> > > > > > The resolutions are the same
> > > > > > > rm -rf "/videos/videowemv copy.wmv" ( DELETED )
```
![alt text](https://raw.githubusercontent.com/keybraker/Media-Organizer/master/MediaOrganizerDisplayDuplicate.jpg)
<br />**_( These is achieved in one run of the program )_**

## Flags
Flags can only be used in the end of the command in whatever order you wish.
<br />Except for ```-dup```, that works only in the beginning.
<br />
<br />```./mediaOrganizer /path/picture.jpg /path/to/store/folder -mp4 -jpg```
<br />will only copy jpg and mp4 files.

<br />```./mediaOrganizer /path/picture.jpg /path/to/store/folder -photo```
<br />will only copy photos not videos.

<br />```./mediaOrganizer -dup /Path```
<br />duplicates will be deleted.

<br />~~```./mediaOrganizer /path/picture.jpg /path/to/store/folder -photo -jpg```
<br />~~ **! this is _NOT_ valid.**

##### Category:
 * -photo : _for photo organization only_
 * -video : _for video organization only_
 <br />**( Attention: These modes can only be used solely )**

##### File type:
 * -jpg : _for jpg organization only_
 * -png : _for png organization only_
 * -avi : _for avi organization only_
 * -mov : _for mov organization only_
 * -wmv : _for wmv organization only_
 * -mp4 : _for mp4 organization only_
 * -mts : _for mts organization only_
<br />**( You can use multiple flags, in order to transfer only the selected file types )**

##### Information:
 * -det : for a detailed list of executions in a txt format ( detailedTransfer.txt )
<br />**( You can use multiple flags, in order to transfer only the selected file types )**

##### Mode:
 * -dup : duplicate mode deletes duplicate with diffrent names
 <br />**( Duplication cleaning is fully funcitonal, but please _back up your files_ before attempting to use it. _Run at your own risk_ )**

## Corrupted files
All corrupted jpeg files are not being copied. If even one file is copputed, a txt file is
 <br />created called ``` corruptedFiles ``` in which every corrupted files is listed wby its full
 <br />path, so that you can handle it manually.

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

* v1.6.0: 20 August 2017: Fully functional duplication deletion.
* v1.5.0: 19 August 2017: Added duplication deletion.
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
