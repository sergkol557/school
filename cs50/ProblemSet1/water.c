#include <stdio.h>
#include <cs50.h>

const int BOTTLES_PER_MINUTE=12;

//=================================================================================================================
int getMinutes(){
    int minutes;
    do{
      printf("Minutes:");    
      minutes=get_int();
    }while(minutes<0);  
    return minutes;
}
//=================================================================================================================
int setBottles(int minute){
    return (minute*BOTTLES_PER_MINUTE); 
}
//=================================================================================================================
int main(void){
    printf("Bottles:%i\n",setBottles(getMinutes()));
    return 0;
}
//=================================================================================================================