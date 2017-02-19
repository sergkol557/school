#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

const int LETTERS_MAX=26;

//==================================================================================================================================
string getString(){
       printf("input string:");
       return get_string();
}
//==================================================================================================================================
string toUpperString(string user_string){
       int i=0;
       while(user_string[i]!=0){
          if(islower(user_string[i])){
             user_string[i]=toupper(user_string[i]);
          }
          i++;
      }
      return user_string;
}
//==================================================================================================================================
void sortNumberLetters(int array_for_sort[LETTERS_MAX][2]){
      int tmp=0,tmp2=0;
      for(int i = 0; i < LETTERS_MAX; i++){
        for(int j = LETTERS_MAX - 2; j >= 0; j--){
            if(array_for_sort[j][1]<array_for_sort[j+1][1]){
                tmp = array_for_sort[j][0];
                tmp2 = array_for_sort[j][1];
                array_for_sort[j][0] = array_for_sort[j+1][0];
                array_for_sort[j][1] = array_for_sort[j+1][1];
                array_for_sort[j+1][0] = tmp;
                array_for_sort[j+1][1] = tmp2;
            }
        }
      }
}      //return array_for_sort;
//==================================================================================================================================
int checkLetter(int array_for_check[LETTERS_MAX][2],char letter){
     for(int i=0;i<LETTERS_MAX;i++){
         if(array_for_check[i][0]==letter){
             return i;
         }
     }
     return -1;
}
//==================================================================================================================================
void checkNumberOfLetter(string upper_string,int output[LETTERS_MAX][2]){
    int i=0,j=0;
    int position=0;

    while(upper_string[i]!=0){
          if(isalpha(upper_string[i])){
             position=checkLetter(output, upper_string[i]);
             if(position!=-1){
                output[position][1]++;
             }
             else{
                output[j][0]=upper_string[i];
                output[j++][1]=1;
             }
          }
          i++;
    }
    sortNumberLetters(output);
}
//==================================================================================================================================
void printLettersAndNumbers(int sorted_array[LETTERS_MAX][2]){
     for(int i=0;i<LETTERS_MAX;i++){
         if(sorted_array[i][1]!=0){
            printf("%c - %i \n",sorted_array[i][0],sorted_array[i][1]);
         }else{
            break;
         }
     }
}
//==================================================================================================================================
int main(void){
    int output[LETTERS_MAX][2];               //first dimension for letters and second dimension for number of the letter in string
    memset(output,0,LETTERS_MAX*2*sizeof(int));
    string user_input=toUpperString(getString());
    checkNumberOfLetter(user_input,output);
    printLettersAndNumbers(output);
    return 0;
}
//==================================================================================================================================