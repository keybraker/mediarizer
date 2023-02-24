package main

import (
	"fmt"
	"os"
	"path/filepath"
)

// func consumer(destinationPath string, queue <-chan FileInfo, done chan<- struct{}) {
// 	for fileInfo := range queue {
// 		var newPath string
// 		switch fileInfo.FileType {
// 		case Unknown:
// 			newPath = filepath.Join(destinationPath, "unknown", filepath.Base(fileInfo.Path))
// 		case Image, Video:
// 			year := fileInfo.Created.Year()
// 			month := fileInfo.Created.Month()
// 			newPath = filepath.Join(destinationPath, fmt.Sprintf("%d", year), fmt.Sprintf("%02d", month), filepath.Base(fileInfo.Path))
// 		}

// 		err := os.Rename(fileInfo.Path, newPath)
// 		if err != nil {
// 			fmt.Println(err)
// 		}
// 	}
// 	done <- struct{}{}
// }

func consumer(destinationPath string, queue <-chan FileInfo, done chan<- struct{}) {
	for fileInfo := range queue {
		var destPath string

		// Determine the destination path based on the file type and created time.
		switch fileInfo.FileType {
		case FileTypeImage, FileTypeVideo:
			destPath = fmt.Sprintf("%s/%04d/%s/%s", destinationPath, fileInfo.Created.Year(), fileInfo.Created.Month().String(), filepath.Base(fileInfo.Path))
		case FileTypeUnknown:
			destPath = fmt.Sprintf("%s/unknown/%s", destinationPath, filepath.Base(fileInfo.Path))
		}

		// Move the file to the destination path.
		if err := moveFile(fileInfo.Path, destPath); err != nil {
			fmt.Printf("failed to move %s to %s: %v\n", fileInfo.Path, destPath, err)
		}
	}

	done <- struct{}{}
}

// func moveFile(sourcePath, destPath string) error {
// 	// Open the source file.
// 	sourceFile, err := os.Open(sourcePath)
// 	if err != nil {
// 		return fmt.Errorf("failed to open source file %s: %v", sourcePath, err)
// 	}
// 	defer sourceFile.Close()

// 	// Create the destination file's directory if it doesn't exist.
// 	if err := os.MkdirAll(filepath.Dir(destPath), os.ModePerm); err != nil {
// 		return fmt.Errorf("failed to create destination directory %s: %v", filepath.Dir(destPath), err)
// 	}

// 	// Create the destination file.
// 	destFile, err := os.Create(destPath)
// 	if err != nil {
// 		return fmt.Errorf("failed to create destination file %s: %v", destPath, err)
// 	}
// 	defer destFile.Close()

// 	// Copy the contents of the source file to the destination file.
// 	if _, err := io.Copy(destFile, sourceFile); err != nil {
// 		return fmt.Errorf("failed to copy contents of %s to %s: %v", sourcePath, destPath, err)
// 	}

// 	// Delete the source file.
// 	if err := os.Remove(sourcePath); err != nil {
// 		return fmt.Errorf("failed to delete source file %s: %v", sourcePath, err)
// 	}

// 	return nil
// }

func moveFile(sourcePath, destPath string) error {
	// Create the destination file's directory if it doesn't exist.
	if err := os.MkdirAll(filepath.Dir(destPath), os.ModePerm); err != nil {
		return fmt.Errorf("failed to create destination directory %s: %v", filepath.Dir(destPath), err)
	}

	// Rename the source file to the destination file.
	if err := os.Rename(sourcePath, destPath); err != nil {
		return fmt.Errorf("failed to move file from %s to %s: %v", sourcePath, destPath, err)
	}

	return nil
}
