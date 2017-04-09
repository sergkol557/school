package main

import (
	"fmt"
	"bufio"
	"os"
	"unicode"
)
//======================================================================================================================
func checkPosition(user_text string, counter int)bool{
	var answer bool
	if counter==0{
		answer=true
	}else if unicode.IsSpace(rune(user_text[counter-1])){
		answer=true
	}
	return answer;
}
//======================================================================================================================
func checkInitials (user_text string, counter int)bool{
 	var result bool
	if unicode.IsLetter(rune(user_text[counter])){
		if checkPosition(user_text,counter) {
			result=true
		}
	}
	return result
}
//======================================================================================================================
func printString(text string){
	for counter,one_letter:=range text{
		if checkInitials(text,counter){
			fmt.Printf("%c",unicode.ToUpper(one_letter))
		}
	}
	fmt.Printf("\n")
}

func main(){
	printString(func ()string{
		reader := bufio.NewReader(os.Stdin)
		input_text, err := reader.ReadString('\n')
		if err!=nil{
			panic("you must enter text")
		}
		return input_text
	}())
}
