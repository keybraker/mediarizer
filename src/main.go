package main

import (
	"log"
	"os"
	"path/filepath"
)

func main() {
	if len(os.Args) != 3 {
		log.Fatal("usage: mediarizer [source] [destination]")
	}

	sourcePath := os.Args[1]
	destinationPath := os.Args[2]

	// create unknown directory in destination path
	if err := os.MkdirAll(filepath.Join(destinationPath, "unknown"), 0755); err != nil {
		log.Fatalf("error creating unknown directory: %v", err)
	}

	queue := make(chan FileInfo)
	done := make(chan struct{})

	go creator(sourcePath, queue)
	go consumer(destinationPath, queue, done)

	<-done
}
