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

  if (param1 == "on") {
    param1 = "1"
  } else {
    param1 = "0"
  }

  if (param2 == "on") {
    param2 = "1"
  } else {
    param2 = "0"
  }

  var dato string = "a=" + param1 + "&b=" + param2
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
	param1 := q["param1"][0]
	param2 := q["param2"][0]
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
