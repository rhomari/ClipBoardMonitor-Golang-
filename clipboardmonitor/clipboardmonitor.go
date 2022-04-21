package clipboardmonitor

// #include "winClipboardmonitor.h"
import (
	"C"
)

var OnClipboardDataChanged func(string)

func EnableClipboardMonitor() C.HWND {
	return C.StartClipBoardMonitor()

}

//export GoClipboardDataChangedEvent
func GoClipboardDataChangedEvent(cbData *C.char) {

	OnClipboardDataChanged(C.GoString(cbData))
}
