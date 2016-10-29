package main

import (
	"fmt"
	"io"
	"log"
	"net/http"
	"net/url"
)

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
	//fmt.Fprintf(w, "Hello, %q", html.EscapeString(req.URL.Path))
	//serverValue := req.Header().Get("Server")
	//  fmt.Println(serverValue)
}

func main() {
	http.HandleFunc("/", HelloServer)
	fmt.Println("Listening localhost:12345")
	log.Fatal(http.ListenAndServe(":12345", nil))
}
