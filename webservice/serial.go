package main

import (
	"fmt"
	"github.com/tarm/goserial"
)

//http://stackoverflow.com/questions/17599232/reading-from-serial-port-with-while-loop/17601050
func main() {
	c := &serial.Config{Name: "/dev/pts/2", Baud: 9600}
	s, err := serial.OpenPort(c)

	if err != nil {
		fmt.Println(err)
	}

	_, err = s.Write([]byte("mensaje"))

	if err != nil {
		fmt.Println(err)
	}
	s.Close()
}
