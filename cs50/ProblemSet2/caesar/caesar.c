#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

const int UPPER_A_POSITION=65;
const int LOWER_A_POSITION=97;
const int CHECK_ARGUMENT=2;
const int NUMBER_LETTERS=26;

//==================================================================================================================================
int checkKeyInput(string input,int arg_number){
    int answer=0;
    int i=0;
    if (arg_number!=CHECK_ARGUMENT){
        answer=1;
    }
    else{
        while(input[i]!=0){
              if(!isdigit(input[i++])){
                 answer=1;
              }
        }
    }
    return answer;
}
//==================================================================================================================================
string getPlainText(){
       printf("plaintext:");
       return get_string();
}
//==================================================================================================================================
int checkModification(char letter){
    int mod=0;
    if(isupper(letter)){
        mod=UPPER_A_POSITION;
    }else{
        mod=LOWER_A_POSITION;
    }
    return mod;
}
//==================================================================================================================================
int applyCaesarCipher(char letter, int key){
    return((letter-checkModification(letter)+key)%NUMBER_LETTERS+checkModification(letter));
}
//==================================================================================================================================
void printCipherText(string plain_text, int cipher_key){
     int i=0;
     printf("ciphertext:");
     while(plain_text[i]!=0){
           if(isalpha(plain_text[i])){
               printf("%c",applyCaesarCipher(plain_text[i],cipher_key));
           }else{
               printf("%c",plain_text[i]);  
           }
           i++;
     }
     printf("\n");
}
//==================================================================================================================================
int main(int argc, string argv[]){
  if(checkKeyInput(argv[1],argc)){
     printf("Usage: ./caesar k\n"); 
     return 1;
  }
  printCipherText(getPlainText(),atoi(argv[1]));
  
  return 0;
}
//==================================================================================================================================