package main

import (
	"fmt"
	"io/fs"
	"log"
	"os"
	"path/filepath"
	"runtime"
	"sort"
	"strings"
	"syscall"
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

// getFileType returns the type of the file at the given path.
func getFileType(path string) FileType {
	file, err := os.Open(path)
	if err != nil {
		log.Println(err)
		return FileTypeUnknown
	}
	defer file.Close()

	fileInfo, err := file.Stat()
	if err != nil {
		log.Println(err)
		return FileTypeUnknown
	}

	if fileInfo.IsDir() {
		return FileTypeFolder
	}

	fileType := FileTypeUnknown
	extension := strings.ToLower(filepath.Ext(path))
	switch extension {
	case ".jpg", ".jpeg", ".png":
		fileType = FileTypeImage
	case ".mp4":
		fileType = FileTypeVideo
	}

	return fileType
}

// getCreatedTime returns the creation time of the file at the given path.
func getCreatedTime(path string) (time.Time, error) {
	file, err := os.Open(path)
	if err != nil {
		return time.Time{}, err
	}
	defer file.Close()

	fileInfo, err := file.Stat()
	if err != nil {
		return time.Time{}, err
	}

	// For Windows, try to get the creation time from the file info.
	// If the creation time is not available, fall back to the modification time.
	if runtime.GOOS == "windows" {
		creationTime := fileInfo.Sys().(*syscall.Win32FileAttributeData).CreationTime
		lastAccessTime := fileInfo.Sys().(*syscall.Win32FileAttributeData).LastAccessTime
		lastWriteTime := fileInfo.Sys().(*syscall.Win32FileAttributeData).LastWriteTime

		// Create a slice of the three times and sort it.
		times := []syscall.Filetime{creationTime, lastAccessTime, lastWriteTime}
		sort.Slice(times, func(i, j int) bool {
			return times[i].Nanoseconds() < times[j].Nanoseconds()
		})

		// the first element in the sorted slice will be the oldest time
		oldestTime := times[0]

		if oldestTime.Nanoseconds() != 0 {
			return time.Unix(0, oldestTime.Nanoseconds()), nil
		}
	}

	// For other platforms, try to get the creation time from the file info.
	// If the creation time is not available, fall back to the modification time.
	createdTime := fileInfo.ModTime()
	return createdTime, nil
}
