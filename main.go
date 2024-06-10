package main

import (
	"fmt"
	"hex_test/hextest"
	"os"
)

func main() {
	fmt.Print(hextest.Process_Bytes(os.Args[1]))
}
