package main

import (
	"bufio"
	"io"
	"os"
	"strings"
)

type DictionaryForSpellcheck  []string

//======================================================================================================================
func (md *DictionaryForSpellcheck ) appendFromFile(dictionary_file string) {

	dict_channel := make(chan string)
	var read_line string
	file_descriptor, err := os.Open(dictionary_file)

	if err != nil {
		panic(err)
	}

	file_reader := bufio.NewReader(file_descriptor)
	defer file_descriptor.Close()
	
	for {
		for i := 0; i < number_CPU; i++ {
			go readStringFromFile(file_reader, dict_channel)
		}
		for j := 0; j < number_CPU; j++ {
			read_line = <-dict_channel
			*md = append(*md, read_line)
		}
		if len(read_line) == 0 {
			break
		}
	}
}

//======================================================================================================================
func (md DictionaryForSpellcheck ) contains(word string) bool {

	answer := false
	for _, dictionary_words := range md {

		if strings.Contains(dictionary_words, strings.ToLower(word)) {
			answer = true
			break
		}
	}
	return answer
}

//======================================================================================================================
func readStringFromFile(reader *bufio.Reader, dict_channel chan string) {

	mutex.Lock()
	string_line, err2 := reader.ReadString('\n')
	mutex.Unlock()

	if err2 != io.EOF && err2 != nil {
		panic(err2)
	}

	dict_channel <- string_line
}

//======================================================================================================================
