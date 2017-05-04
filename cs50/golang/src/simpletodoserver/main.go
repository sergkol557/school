package main

import (
	"fmt"
	"log"
	"net/http"
	"os"
	"path/filepath"
	"time"
	"github.com/heroku/simpletodoserver/todo_server"
	"github.com/boltdb/bolt"
	"github.com/gorilla/context"
	"github.com/gorilla/mux"
	"github.com/justinas/alice"
)

const (
	Debug           = false
)

var (
	programm_directory string
	err                error
	site_posts         map[string]string
)

//======================================================================================================================
func main() {

	server_router := mux.NewRouter()
	site_posts = make(map[string]string)
	programm_directory = filepath.Dir(os.Args[0])
	common_handles := alice.New(todo_server.LoggingHandler,
		todo_server.RecoverHandler,
		todo_server.CookieHandler,
		todo_server.AuthentificateHandler)

	todo_server.Data_base, err = bolt.Open(programm_directory+"/bolt.db", todo_server.DataBaseMode, nil)
	todo_server.CheckError(err)
	todo_server.AddUser("admin", "admin")
	todo_server.AddPost(time.Now().Format(todo_server.DateFormat), "server is running")
	defer todo_server.Data_base.Close()

	server_router.Methods("GET").
		Queries("act", "sign").
		Handler(common_handles.ThenFunc(signHandler))

	server_router.Methods("GET").
		Queries("act", "reg").
		Handler(common_handles.ThenFunc(registerHandler))

	server_router.Methods("GET").
		Queries("act", "add").
		Handler(common_handles.ThenFunc(addPostHandler))

	server_router.Methods("GET").
		Queries("act", "delete").
		Handler(common_handles.ThenFunc(deletePostHandler))

	server_router.Methods("GET").
		Queries("act", "update").
		Handler(common_handles.ThenFunc(updatePostHandler))

	server_router.Methods("GET").
		Queries("act", "logout").
		Handler(common_handles.ThenFunc(logoutHandler))

	server_router.Handle("/", common_handles.ThenFunc(indexHandler))

	server_router.PathPrefix("/templates/").
		Handler(http.StripPrefix("/templates/",
			http.FileServer(http.Dir(programm_directory+"/templates/"))))



	server := &http.Server{
		Addr:           todo_server.ServerPort,
		Handler:        context.ClearHandler(server_router),
		ReadTimeout:    todo_server.ServerReadTimeout * time.Second,
		WriteTimeout:   todo_server.ServerWriteTimeout * time.Second,
		MaxHeaderBytes: todo_server.ServerMaxHeaderByte,
	}

	fmt.Println("server is started at:", time.Now().Format(todo_server.DateFormat))
	log.Fatal(server.ListenAndServeTLS(programm_directory+"/server.crt",programm_directory+"/serverkey.key"))


}

//======================================================================================================================
