package main

import (
	"io/ioutil"

	"bytes"
	"fmt"
	"net/http"
	"sort"
	"todo_server"
)

//=============================================================================================
func gatherPost() string {

	var key_array []string
	site_posts = todo_server.GetAllPosts()
	response_posts := ""
	html_post, err := ioutil.ReadFile(programm_directory + "/templates/post.html")
	todo_server.CheckError(err)

	for key, _ := range site_posts {

		key_array = append(key_array, key)
	}
	sort.Strings(key_array)

	for _, values := range key_array {

		response_posts += fmt.Sprintf(string(html_post), site_posts[values], values)
	}

	return response_posts
}

//======================================================================================================================
func buildPage(name string) string {

	index_page, err := ioutil.ReadFile(programm_directory + "/templates/index.html")

	if err != nil {

		return http.StatusText(todo_server.InternalServerError) + err.Error()
	}
	text, err := ioutil.ReadFile(programm_directory + "/templates/header_text.html")

	if err != nil {

		return http.StatusText(todo_server.InternalServerError) + err.Error()
	}

	index_page = bytes.Replace(index_page,
				   text,
				   []byte("Hello "+name+","+todo_server.LogOutButton),
				   todo_server.NumberOfReplace)
	all_posts := gatherPost()
	index_page = bytes.Replace(index_page,
				   []byte("<article>"),
				   []byte("<article>"+all_posts),
				   todo_server.NumberOfReplace)

	return string(index_page)
}

//============================================================================================
