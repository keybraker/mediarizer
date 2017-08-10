# jpeg Organizer
Organises a folder of images in a chronological order

## How does it work ( simple representation )
```text
cd photosOrganized:
make                                                    |----------|
------------------------------------------------------> | folder   |
                                                        | creation |
                                                        |----------|
                                                             |
cd .. :                                                      |
make     |---------------| ./jpegOrganizer picture.jpg       |
-------> | jpegOrganizer |-----------------------------------/
         |               | ./jpegOrganizer path
         |---------------|
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
```
cd .../photosOrganized
```

##### 3.
To create all the folders in which your photos will be organised to type:
( Folder will be created from 2000 - 2017 if your pictures range in other years please add the folders )
```
make 
```
( Folder will be created from 2000 - 2017 if your pictures range in other years please add the folders )

##### 4.
```
cd ..
```

##### 5.
To compile the program just type:
```
make 
```

##### 6.
You can run the program in two ways, a single picture mode and a folder mode.
The single picture only organises this one picture and to do that just type:
```
./jpegOrganizer /filePath/picture.jpg
```
If you want to organise all the picture in a folder, and the folders in them, just type :
```
./jpegOrganizer /filePath/folder
```

## Cleaning
* To clean the program type ``` make clean ``` in ``` /jpeg-Organizer ```
* To clean the organized folders type ``` make clean ``` in ``` /photosOrganized ```
  ( but be careful to delete the folders when pictures are stored there )

## Authors
* **Ioannis Tsiakkas** - *(Keybraker)* - [Keybraker](https://github.com/keybraker)

## Acknowledgments
* mayanklahiri with the exeptional project:  [easyexif](https://github.com/mayanklahiri/easyexif)
