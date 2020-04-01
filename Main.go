package main

import (
	"fmt"
	"io/ioutil"
	"os"
)

func main() {

	fmt.Println(os.Args[1:])
	for i, val := range os.Args[1:] {
	data, err := ioutil.ReadFile(val)

	if err != nil {
		fmt.Println("[Error]: Cannot read the file:", err, i)
		return
	}

		fmt.Println(string(data))
	}

}
