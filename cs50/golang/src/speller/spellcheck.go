package main

import (
	"io/ioutil"
	"strings"
	"unicode"
)

//======================================================================================================================
func checkOrphographyInFile(text_file string) {

	text_channel := make(chan string)
	file_text, err := ioutil.ReadFile(text_file)

	if err != nil {
		panic(err)
	}

	words_in_file := strings.FieldsFunc(string(file_text),
					    func(letter rune) bool {
				  	    	return !unicode.IsLetter(letter) && letter != '\''
					    })

	number_words_in_text = len(words_in_file)

	for k := 0; k < number_words_in_text; k++ {

		for i := 0; i < number_CPU; i++ {

			go checkDictionary(text_channel, words_in_file[k])

			if k < number_words_in_text {

				k++

			} else {

				break
			}
		}
		for j := 0; j < number_CPU; j++ {

			<-text_channel
		}
	}
}

//======================================================================================================================
func checkDictionary(word_channel chan string, input_word string) {

	input_word = strings.Trim(input_word, "'")

	if !dictionary.contains(input_word) || len(input_word) > Max_Word_Lenght {

		mispelled_words = append(mispelled_words, input_word)
	}
	word_channel <- ""

}

//======================================================================================================================
