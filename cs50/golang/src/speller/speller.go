package main

import (
	"fmt"
	"os"
	"runtime"
	"sync"
	"time"
)

const (
	Dictionary_File_Name = "dictionaries/large"
	//Text_File_Name       = "texts/alice.txt"  //text filename example
	Max_Word_Lenght      = 45
)

var (
	number_words_in_text	    int
	dictionary                  DictionaryForSpellcheck
	mispelled_words             []string
	mutex                       = &sync.Mutex{}
	number_CPU                  = runtime.NumCPU()
)

//======================================================================================================================
func testTime(someFunction func(string),filename string) time.Duration {

	start_time := time.Now()
	someFunction(filename)
	finish_time := time.Now()
	return finish_time.Sub(start_time)
}

//======================================================================================================================
func getTextFileName() string {
	if len(os.Args) == 1 || len(os.Args) > 3 {

		panic("Usage: speller [dictionary] text")

	} else if len(os.Args) == 3 {

		return os.Args[2]

	} else {

		return os.Args[1]
	}
}
//======================================================================================================================
func getDictionaryName()string{

	if len(os.Args) == 3 {

		return os.Args[1]
	}else{
		return  Dictionary_File_Name
	}
}
//======================================================================================================================
func main() {

	fmt.Println("TIME OF DICTIONARY LOAD", testTime(dictionary.appendFromFile,getDictionaryName()))
	fmt.Println("WORDS IN  DICTIONARY", len(dictionary))
	fmt.Println("TIME OF SPELLCHECCKING", testTime(checkOrphographyInFile,getTextFileName()))
	fmt.Println("WORDS IN TEXT", number_words_in_text)
	fmt.Println("MISPELLINGS", len(mispelled_words))
	fmt.Println("MISPELLED WORDS", mispelled_words)
}

//======================================================================================================================
