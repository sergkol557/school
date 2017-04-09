package main

import (
	"fmt"
	"os"
	"unicode"
	"strconv"
	"bufio"
)

const NUMBER_OF_LETTERS =26
const LOWER_A_POSITION  = 97
var (
	input_text string
)
//======================================================================================================================
func applyCipherCaesar(letter rune, caesar_key int)rune{
	upper :=unicode.IsUpper(letter)
	letter=unicode.ToLower(letter)
	caesar_key%=NUMBER_OF_LETTERS
	letter=(letter-LOWER_A_POSITION+rune(caesar_key))%NUMBER_OF_LETTERS+LOWER_A_POSITION
	if upper{
		letter=unicode.ToUpper(letter)
	}
	return letter
}
//======================================================================================================================
func printCipherText(cipher_key int, plain_text string){
	fmt.Println("ciphertext")
	for _, one_char:=range plain_text{
		if unicode.IsLetter(one_char){
			fmt.Printf("%c",applyCipherCaesar(one_char,cipher_key))
		}else {
			fmt.Printf("%c",one_char)
		}
	}
	fmt.Print("\n")
}
//======================================================================================================================
func checkArguments()int {
	if  len(os.Args[1:])==0{
		fmt.Println("Usage: ./caesar key")
		os.Exit(1)
	}
	argv:=os.Args[1]
	for _,one_char:=range argv{
		if !unicode.IsDigit(one_char){
			fmt.Println("Key must be integer")
			os.Exit(2)
		}
	}
	cipher_key,err:=strconv.Atoi(argv)
	if err!=nil{
		fmt.Println("Error key converting")
		os.Exit(3)
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