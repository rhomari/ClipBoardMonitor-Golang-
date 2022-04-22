package main

import (
	"clipboardmonitor/clipboardmonitor"
	"fmt"
)

func main() {

	clipboardmonitor.OnClipboardDataChanged = func(data string) { // function to handle clipboard data changes (text data only)
		fmt.Printf("new clipboard data :\n %s\n", data)
	}
	go clipboardmonitor.EnableClipboardMonitor() // running on goroutine to prevent blocking main thread
	fmt.Printf("doing stuff.\n")                 // do other stuff
	select {}                                    //force to run forever

}
