package main

import (
	"fmt"
	"io/fs"
	"path/filepath"
	"time"
)

func creator(sourcePath string, queue chan<- FileInfo) {
	filepath.WalkDir(sourcePath, func(path string, d fs.DirEntry, err error) error {
		if err != nil {
			fmt.Println(err)
			return err
		}

		if !d.Type().IsRegular() {
			return nil // skip directories and other non-regular files
		}

		fileType := getFileType(path)
		if fileType == Unknown {
			queue <- FileInfo{Path: path, FileType: Unknown}
			return nil
		}

		created, err := getCreatedTime(path)
		if err != nil {
			queue <- FileInfo{Path: path, FileType: Unknown}
			return nil
		}

		queue <- FileInfo{Path: path, FileType: fileType, Created: created}
		return nil
	})
	close(queue)
}

func getFileType(path string) FileType {
	// implement logic to determine file type based on extension or other criteria
	return Unknown
}

func getCreatedTime(path string) (time.Time, error) {
	// implement logic to get the creation time of a file
	return time.Now(), nil
}
