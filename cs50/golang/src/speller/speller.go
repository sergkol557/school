package main

import (
	"time"
	"fmt"
	"os"
	"sync"
)

const(
	Dictionary_Name = "dictionaries/large"
 	Text_File_Name = "texts/alice.txt"
	Max_Word_Lenght=45
)

var(
	number_words_in_text, words int
	dictionary MyDictionary
	mispelled_words []string
	dictionary_file,text_file string
	mutex = &sync.Mutex{}
)
//======================================================================================================================
func testTime(someFunction func()) time.Duration {
	start_time:=time.Now()
	someFunction()
	finish_time:=time.Now()
	return finish_time.Sub(start_time)
}
//======================================================================================================================
func checkArguments()(string,string) {
	if  len(os.Args)==1||len(os.Args)>3{
		panic("Usage: speller [dictionary] text")
	}else if len(os.Args)==3{
		return os.Args[1],os.Args[2]
	}else{
		return Dictionary_Name,os.Args[1]
	}
}
//======================================================================================================================
func main(){
	dictionary_file,text_file=checkArguments()
	fmt.Println("TIME OF DICTIONARY LOAD",testTime(dictionary.appendFromFile))
	fmt.Println("WORDS IN  DICTIONARY",len(dictionary))
	fmt.Println("TIME OF SPELLCHECCKING",testTime(checkWordFromFile))
	fmt.Println("WORDS IN TEXT",number_words_in_text)
	fmt.Println("MISPELLINGS",len(mispelled_words))
	fmt.Println("MISPELLED WORDS", mispelled_words)
}
//======================================================================================================================