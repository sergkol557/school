package main

import (
	"io/ioutil"
	"unicode"
	"strings"
	"runtime"
)
//======================================================================================================================
func  checkWordFromFile() {
	channel:=make(chan string)
	file_text, err := ioutil.ReadFile(text_file)
	if err != nil {
		panic(err)
	}
	divideString := func(letter rune) bool {
		return !unicode.IsLetter(letter) && letter!='\''
	}
	words_in_file :=strings.FieldsFunc(string(file_text),divideString)
	number_words_in_text=len(words_in_file)
	for k:=0;k<number_words_in_text;k++{
		for i:=0;i<runtime.NumCPU();i++{
			go checkDictionary(channel,words_in_file[k])
			if k<number_words_in_text{
				k++
			}else{
				break
			}
		}
		for j:=0;j<runtime.NumGoroutine();j++{
			<-channel
		}
	}
}
//======================================================================================================================
func checkDictionary(word_channel chan string,input_word string){
	input_word=strings.Trim(input_word,"'")
	if !dictionary.contains(input_word)||len(input_word)>Max_Word_Lenght{
		mispelled_words=append(mispelled_words,input_word)
	}
	word_channel<-""

}
//======================================================================================================================