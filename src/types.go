package main

import "time"

type FileType int

const (
	Unknown FileType = iota
	Image
	Video
)

type FileInfo struct {
	Path     string
	FileType FileType
	Created  time.Time
}
