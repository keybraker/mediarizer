# Picture Organizer 
Organises a folder of images in a chronological order ( Only jpeg )

## Why use Picture Organiser
#### 1. Organises photos super fast, the only limit is your hardware
#### 2. Cleans your photos from duplicates
#### 3. Lightweight and runs everywhere

## How does it work ( simple representation )
```text
make  |---------------| ./jpegOrganizer /picture.jpg /desPath  |------------------| 
----> | jpegOrganizer |--------------------------------------> | organised photos | 
      |---------------| ./jpegOrganizer /folderPath /desPath   | in year/month    | 
                                                               |------------------| 
```

## Installation Guide
Clone this repository with ( or download zip ):
```
git clone https://github.com/keybraker/jpeg-Organizer.git
```

## Usage Guide
Open a terminal window and cd to cloned project

##### 1. 
```
cd .../jpeg-Organizer
```

##### 2.
To compile the program just type:
```
make 
```

##### 3.
You can run the program in two ways, a single picture mode and a folder mode.
The single picture only organises this one picture and to do that just type:
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

## Authors
* **Ioannis Tsiakkas** - *(Keybraker)* - [Keybraker](https://github.com/keybraker)

## Acknowledgments
* mayanklahiri with the exeptional project:  [easyexif](https://github.com/mayanklahiri/easyexif)
