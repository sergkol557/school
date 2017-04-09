package main

import (
	"fmt"
	"os"
	"unicode"
	"bufio"
)
const NUMBER_OF_LETTERS = 26
const LOWER_A_POSITION  = 97
var (
	input_text string
)
//======================================================================================================================
func applyCipherCaesar(letter, caesar_key rune)rune{
	upper :=unicode.IsUpper(letter)
	letter=unicode.ToLower(letter)
	//(((a - 'A') + (b - 'A')) % 26) + 'A'
	letter=((letter-LOWER_A_POSITION)+(caesar_key-LOWER_A_POSITION))%NUMBER_OF_LETTERS+LOWER_A_POSITION
	if upper{
		letter=unicode.ToUpper(letter)
	}
	return letter
}
//======================================================================================================================
func printCipherText(cipher_key , plain_text string){
	fmt.Println("ciphertext")

	for counter, one_char:=range plain_text{
		if unicode.IsLetter(one_char){
			key_index:=counter%len(cipher_key)
			fmt.Printf("%c",applyCipherCaesar(one_char,rune(cipher_key[key_index])))
		}else {
			fmt.Printf("%c",one_char)
		}
	}
	fmt.Print("\n")
}
//======================================================================================================================
func checkArguments()string {
	if  len(os.Args[1:])==0{
		fmt.Println("Usage: ./caesar key")
		os.Exit(1)
	}
	cipher_key:=os.Args[1]
	for _,one_char:=range cipher_key{
		if !unicode.IsLetter(one_char){
			fmt.Println("Key must be from letters")
			os.Exit(2)
		}
	}
	return cipher_key
}
//======================================================================================================================
func main(){
	printCipherText(checkArguments(),
	func ()string{
	fmt.Println("plaintext:")
	reader := bufio.NewReader(os.Stdin)
	input_text, err := reader.ReadString('\n')
	if err!=nil{
	panic("you must enter text")
	}
	return input_text
	}())
}
//======================================================================================================================