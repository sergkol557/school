package main

import (
	"fmt"
	"github.com/gorilla/context"
	"io/ioutil"
	"net/http"
	"todo_server"
)

//======================================================================================================================
func indexHandler(w http.ResponseWriter, r *http.Request) {

	if Debug {
		fmt.Println("index page handler")
		fmt.Println(context.Get(r, todo_server.CheckLogged))
	}

	if context.Get(r, todo_server.CheckLogged) == "logged" {

		login, _ := r.Cookie("login")
		fmt.Fprintf(w, buildPage(login.Value))

	} else {

		index_page, err := ioutil.ReadFile(programm_directory + "/templates/index.html")
		if err != nil {
			fmt.Fprint(w, err.Error())
		}
		fmt.Fprint(w, string(index_page))

	}
}

//======================================================================================================================
func registerHandler(w http.ResponseWriter, r *http.Request) {

	if Debug {
		fmt.Println("register user handler")
	}

	if !todo_server.CheckUser(r.FormValue("login")) {

		if todo_server.AddUser(r.FormValue("login"), r.FormValue("pas")) {

			fmt.Fprint(w, "register succesfully")
		} else {

			fmt.Fprint(w, "cant add user,user exists ")
		}

	} else {

		fmt.Fprint(w, "user exists")
	}
}

//======================================================================================================================
func signHandler(w http.ResponseWriter, r *http.Request) {

	if Debug {

		fmt.Println("sign user handler")
	}

	if todo_server.AuthenticationUser(r.FormValue("login"), r.FormValue("pas")) {

		fmt.Fprintf(w, "Hello %s, %s", r.FormValue("login"), todo_server.LogOutButton)

	} else {

		html, err := ioutil.ReadFile(programm_directory + "/templates/head.html")
		todo_server.CheckError(err)
		fmt.Fprint(w, string(html))
	}
}

//======================================================================================================================
func addPostHandler(w http.ResponseWriter, r *http.Request) {

	if Debug {
		fmt.Println("add post handler")
	}

	if context.Get(r, todo_server.CheckLogged) == "logged" &&
		todo_server.AddPost(r.FormValue("date"), r.FormValue("text")) {

		fmt.Fprint(w, "post added succefully")

	} else {

		fmt.Fprint(w, "post cant be added")
	}
}

//======================================================================================================================
func deletePostHandler(w http.ResponseWriter, r *http.Request) {

	if Debug {

		fmt.Println("delete post handler")
	}

	if context.Get(r, todo_server.CheckLogged) == "logged" &&
		todo_server.DeletePost(r.FormValue("date")) {

		fmt.Fprint(w, "post deleted succefully")
	} else {

		fmt.Fprint(w, "post cant be deleted")
	}
}

//======================================================================================================================
func updatePostHandler(w http.ResponseWriter, r *http.Request) {

	if Debug {

		fmt.Println("update post handler")
	}
	if context.Get(r, todo_server.CheckLogged) == "logged" {

		fmt.Fprint(w, gatherPost())
	} else {

		fmt.Println(w, "cant update posts")
	}

}

//======================================================================================================================
func logoutHandler(w http.ResponseWriter, r *http.Request) {

	if Debug {

		fmt.Println("logout handler")
	}

	text, err := ioutil.ReadFile(programm_directory + "/templates/header_text.html")

	if err != nil {
		http.Error(w, http.StatusText(todo_server.InternalServerError), todo_server.InternalServerError)
	}
	fmt.Fprint(w, string(text))
}
//======================================================================================================================