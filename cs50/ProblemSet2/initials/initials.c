#include <cs50.h>
#include <stdio.h>
#include <ctype.h>

/**
 * More comfortable version
 */


//====================================================================================================================
int checkPosition(string user_string,int count){
    int answer=0;
    if(count==0){
       answer=1;
    }
    else if(isblank(user_string[count-1])){
       answer=1;  
    }
    return answer;
}
//====================================================================================================================
int checkInitials(string user_string,int count){
       int check_letter=0;
       if(isalpha(user_string[count])){
          if(checkPosition(user_string,count)){ 
             check_letter=1;
          }
       }
       return check_letter;
}
//====================================================================================================================
void printString(string user_string){
       int i=0;
       while(user_string[i]!=0){
             if(checkInitials(user_string,i)){
                 printf("%c",toupper(user_string[i]));
             }
             i++;
       }
       printf("\n");
}
//====================================================================================================================
int main(void){
    printString(get_string());
    return 0;
}
//====================================================================================================================