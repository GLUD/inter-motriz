package main

import (
	"fmt"
	"io"
	"log"
	"net/http"
	"net/url"
	"strconv"

	"github.com/tarm/goserial"
)

func conSerial(numero int, param1 string, param2 string) int {
	result := strconv.Itoa(numero)
	c := &serial.Config{Name: "/dev/ttyACM" + result, Baud: 9600}
	s, err := serial.OpenPort(c)

	if err != nil {
		fmt.Println(err)
		return 1
	}

	var dato string = ""
	if (param1 == "on") {
		dato = "0"
	} else if (param1 == "off") {
		dato = "1"
	} else if (param2 == "on") {
		dato = "2"
	} else { //if (param2 == "off") {
		dato = "3"
	}

	fmt.Println(dato)

	_, err = s.Write([]byte(dato))

	if err != nil {
		fmt.Println(err)
		return 2
	}

	s.Close()
	return 0
}

// hello world, the web server
func HelloServer(w http.ResponseWriter, req *http.Request) {
	io.WriteString(w, "")
	//fmt.Println(req.RequestURI)
	u, err := url.Parse(req.RequestURI)
	if err != nil {
		log.Fatal(err)
	}
	q := u.Query()
	fmt.Println(q)
	var param1 string = "";
	var param2 string = "";
	if (q["param1"] != nil) {
		param1 = q["param1"][0]
	}
	if (q["param2"] != nil) {
		param2 = q["param2"][0]
	}
	fmt.Println(param1, param2)
	var dev int = 0
	var error int = -1
	for error != 0 {
		error = conSerial(dev, param1, param2)
		dev += 1
		if dev > 10 {
			return
		}
	}
}

func main() {
	http.HandleFunc("/", HelloServer)
	fmt.Println("Listening curl \"localhost:12345/?param1=on&param2=off\"")
	log.Fatal(http.ListenAndServe(":12345", nil))
}
