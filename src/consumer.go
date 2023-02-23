package main

import (
	"fmt"
	"os"
	"path/filepath"
)

func consumer(destinationPath string, queue <-chan FileInfo, done chan<- struct{}) {
	for fileInfo := range queue {
		var newPath string
		switch fileInfo.FileType {
		case Unknown:
			newPath = filepath.Join(destinationPath, "unknown", filepath.Base(fileInfo.Path))
		case Image, Video:
			year := fileInfo.Created.Year()
			month := fileInfo.Created.Month()
			newPath = filepath.Join(destinationPath, fmt.Sprintf("%d", year), fmt.Sprintf("%02d", month), filepath.Base(fileInfo.Path))
		}

		err := os.Rename(fileInfo.Path, newPath)
		if err != nil {
			fmt.Println(err)
		}
	}
	done <- struct{}{}
}
