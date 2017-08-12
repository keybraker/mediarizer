# Picture Organizer 
Organises a folder of images in a chronological order ( Only jpeg )

## How does it work 
```text
make  |---------------| ./jpegOrganizer /picture.jpg /desPath  |------------------| 
----> | jpegOrganizer |--------------------------------------> | organised photos | 
      |---------------| ./jpegOrganizer /folderPath /desPath   | in year/month    | 
                                                               |------------------| 
```

## Why use Picture Organiser
* Organises photos super fast, the only limit is your hardware
* Cleans your photos from duplicates
* Lightweight and runs everywhere

## Installation Guide
Clone this repository with ( or download zip ):
```
git clone https://github.com/keybraker/jpeg-Organizer.git
```

## Usage Guide


##### 1. Open a terminal window and cd to cloned project
```
cd .../jpeg-Organizer
```

##### 2. To compile the program just type:
```
make 
```

##### 3. You can run the program in two ways, a single picture mode and a folder mode. The single picture only organises this one picture and to do that just type:
```
./jpegOrganizer /path/picture.jpg /destinationPath
```
If you want to organise all the picture in a folder, and the folders in them, just type :
```
./jpegOrganizer /path/folder /destinationPath
```

## Coping Files
Photos are only copied once, so cleaning is done as-well !

## Corrupted files
All corrupted jpeg files are not being copied. If even one file is copputed, a txt file is
created called ``` corruptedFiles ``` in which every corrupted files is listed wby its full
path, so that you can handle it manually.

## Cleaning
* To clean the program type ``` make clean ``` in ``` /jpeg-Organizer ```
* To clean the organized folders type ``` make clean ``` in ``` /photosOrganized ```
  ( but be careful to delete the folders when pictures are stored there )

## Photo file support list 
* jpeg ✔︎
* png ( to be added )
* tiff ( to be added )

## Video file support list 
* avi ( to be added )
* mp4 ( to be added )
* wmv ( to be added )
* mov ( to be added )

## Release History

* v1.0.0: 12 August 2017: Full jpeg release !
* v0.1.0: 9 August 2017: Creation.

## Authors
* **Ioannis Tsiakkas** - *(Keybraker)* - [Keybraker](https://github.com/keybraker)

## Acknowledgments
* mayanklahiri with the exeptional project:  [easyexif](https://github.com/mayanklahiri/easyexif)
