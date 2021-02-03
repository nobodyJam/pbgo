package base

/*
#include "pbrt.h"
*/
import "C"
import (
	"unsafe"
	//"fmt"
	"github.com/axgle/mahonia"
)
func GS(chart_porint *C.char,coding... string) string {
	str := C.GoString(chart_porint)
	code := "gb18030"

	if (len(coding) == 1) {
		code = coding[0]
	}
	goStr:= mahonia.NewDecoder(code).ConvertString(str)
	defer C.free(unsafe.Pointer(chart_porint))
	return goStr
}

func CallC() string {
    return GS(C.test())
}