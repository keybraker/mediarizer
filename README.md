# Media Organizer 
Organises all your media in a chronological order.
```
`7MMM.     ,MMF'             `7MM    db           
  MMMb    dPMM                 MM                 
  M YM   ,M MM  .gP"Ya    ,M""bMM  `7MM   ,6"Yb.  
  M  Mb  M' MM ,M'   Yb ,AP    MM    MM  8)   MM  
  M  YM.P'  MM 8M"""""" 8MI    MM    MM   ,pm9MM  
  M  `YM'   MM YM.    , `Mb    MM    MM  8M   MM  
.JML. `'  .JMML.`Mbmmd'  `Wbmd"MML..JMML.`Moo9^Yo.
                                                      ,,                          
   .g8""8q.                                           db                          
 .dP'    `YM.                                                                     
 dM'      `MM `7Mb,od8 .P"Ybmmm ,6"Yb.  `7MMpMMMb.  `7MM  M"""MMV .gP"Ya `7Mb,od8 
 MM        MM   MM' "':MI  I8  8)   MM    MM    MM    MM  '  AMV ,M'   Yb  MM' "' 
 MM.      ,MP   MM     WmmmP"   ,pm9MM    MM    MM    MM    AMV  8M""""""  MM     
 `Mb.    ,dP'   MM    8M       8M   MM    MM    MM    MM   AMV  ,YM.    ,  MM     
   `"bmmd"'   .JMML.   YMMMMMb `Moo9^Yo..JMML  JMML..JMML.AMMmmmM `Mbmmd'.JMML.   
                      6'     dP                                                   
                      Ybmmmd'                                                     
```

## How does it work 
```text
make       |----------------| ./mediaOrganizer /media.file /path/to/store       |------------------| 
---------> | mediaOrganizer |-------------------------------------------------> | organised photos | 
      	   |----------------| ./mediaOrganizer /path/folder /path/to/store      | in year/month    | 
                    |                                        	                |------------------| 
                    |
                    |         ./mediaOrganizer -dup /path/to/store              |------------------| 
                    \---------------------------------------------------------> | duplicate free   | 
      	                                                                        | folders          | 
                                                            	                |------------------| 
```
![alt text](https://raw.githubusercontent.com/keybraker/Media-Organizer/master/img/MediaOrganizerDisplay.jpg)
<br />**_( These is achieved in one run of the program )_**

## Why use Media Organizer
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
./mediaOrganizer /path/media.file /path/to/store/folder
```
##### b. Folder mode: Organises all the pictures and videos in a folder, and the folders in it.
```
./mediaOrganizer /path/folder /path/to/store/folder
```
###### Photos are copied to the new path if date information is available. <br />Same photos with same names, from diffrent folders are not being copied.
###### To clean the program type ``` make clean ``` in ``` /Media-Organizer ```

##### c. Duplicate mode: Deletes all duplicate pictures and videos in a folder, and the folders in it.
```
./mediaOrganizer -dup /path/folder
```
###### Better run duplicate mode after organizing. It may be more cpu and time consuming but you can guarantee a fully, free of duplicates library due to the siple fact that duplicate files are only searched in current folder.

_Output:_
```
> > It is a file and is not hidden
> > > The names are equal except for a slight variation
> > > > The sizes are the same
> > > > > The dates of creation are the same
> > > > > > The resolutions are the same
> > > > > > > rm -rf "/videos/videowemv copy.wmv" ( DELETED )
```
![alt text](https://raw.githubusercontent.com/keybraker/Media-Organizer/master/img/MediaOrganizerDisplayDuplicate.jpg)
<br />**_( These is achieved in one run of the program )_**

## Flags
##### Category:
 * -photo : _for photo organization only_
 * -video : _for video organization only_

##### File type:
 * -jpg : _for jpg organization only_
 * -png : _for png organization only_
 * -avi : _for avi organization only_
 * -mov : _for mov organization only_
 * -wmv : _for wmv organization only_
 * -mp4 : _for mp4 organization only_
 * -mts : _for mts organization only_
<br />**( You can use multiple flags, in order to transfer only the selected file types )**

##### Informative:
 * -hlp : _Media Organizer User Guide_ 
 * -vrs:  _Version_
 * -det : _for a detailed list of executions in a txt format_ ( detailedTransfer.txt )

##### Mode:
 * -dup : _duplicate mode deletes duplicate with diffrent names_
 <br />**( Duplication cleaning is fully funcitonal, but please _back up your files_ before attempting to use it. _Run at your own risk_ )**

#### Flag Use Examples:
##### Flags can be put in any order you wish even in the middle of the directories, like this:
```./mediaOrganizer -mp4 /path/source/folder -jpg /path/to/store/folder -png```
<br />is the same as,<br />
```./mediaOrganizer /path/source/folder /path/to/store/folder -mp4 -jpg -png```

##### will only copy jpg and mp4 files.
```./mediaOrganizer -mp4 -jpg /path/source/folder /path/to/store/folder```
<br />is the same as,<br />
```./mediaOrganizer -mp4 /path/source/folder -jpg /path/to/store/folder```

##### will only copy photos not videos.
```./mediaOrganizer /path/source/folder /path/to/store/folder -photo```

##### duplicates will be deleted.
```./mediaOrganizer -dup /path/source/folder```

##### **! only _videos_ will be copied.**
```./mediaOrganizer -video /path/media.file /path/to/store/folder -jpg```

##### **! this is _NOT_ valid because -dup can only be used alone.**
~~```./mediaOrganizer -dup /path/media.file /path/to/store/folder -jpg```~~

## Corrupted files or Unsupported files
All corrupted or unsupported files are not being copied. If even one file is copputed or unsupported, a txt file is created called ``` corruptedFiles ```, in which every corrupted or unsupported file is listed by its full path, so that you can handle it manually.

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
