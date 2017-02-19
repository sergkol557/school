#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

const int UPPER_A_POSITION=65;
const int LOWER_A_POSITION=97;
const int NUMBER_LETTERS=26;

//==================================================================================================================================
int checkKeyInput(string input,int arg_number){
    int answer=0;
    int i=0;
    if (arg_number!=2){
        answer=1;
    }else{
        while(input[i]!=0){
              if(!isalpha(input[i])){
                 answer=1;
              }
              i++;
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
int applyVigenereCipher(char letter, string key, int count){
    int key_index=count%strlen(key);
    return((letter-checkModification(letter)+key[key_index]-checkModification(key[key_index]))%NUMBER_LETTERS+checkModification(letter));
}
//==================================================================================================================================
void printCipherText(string plain_text, string cipher_key){
     int i=0,j=0;
     printf("ciphertext:");
     while(plain_text[i]!=0){
           if(isalpha(plain_text[i])){
               printf("%c",applyVigenereCipher(plain_text[i],cipher_key,j++));
           }else{
               printf("%c",plain_text[i]);  
           }
           i++;
     }
     printf("\n");
}
//==================================================================================================================================

int main(int argc, string argv[])
{
  if(checkKeyInput(argv[1],argc)){
     printf("Usage: ./vigenere k\n"); 
     return 1;
  }
  printCipherText(getPlainText(),argv[1]);
  
  return 0;
}
//==================================================================================================================================