package main

import (
	"bufio"
	"os"
	"io"
	"strings"
	"runtime"
)

type MyDictionary []string
//======================================================================================================================
func (md *MyDictionary) appendFromFile() {
	channel2:=make(chan string)
	var read_line string
	file_descriptor, err := os.Open(dictionary_file)
	if err != nil {
		panic(err)
	}
	file_reader := bufio.NewReader(file_descriptor)
	defer file_descriptor.Close()
	for {
		for i:=0;i<runtime.NumCPU();i++ {
			go readStringFromFile(file_reader, channel2)
		}
		for j:=0;j<runtime.NumCPU();j++ {
			read_line=<-channel2
			*md = append(*md, read_line)
		}
		if len(read_line)==0{
			break
		}
	}
}
//======================================================================================================================
func (md MyDictionary)contains(word string) bool{
	answer:=false
	for _,dictionary_words:=range md{
		if strings.Contains(dictionary_words,strings.ToLower(word)){
			answer=true
			break
		}
	}
	return answer
}
//======================================================================================================================
func readStringFromFile(reader *bufio.Reader, input_channel chan string){
	mutex.Lock()
	string_line, err2 := reader.ReadString('\n')
	mutex.Unlock()
	if err2 != io.EOF && err2 != nil{
		panic(err2)
	}
	input_channel<-string_line
}
//======================================================================================================================