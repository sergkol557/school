#include <stdio.h>
#include <cs50.h>
#include <math.h>

#define TYPE_COINS int

 const TYPE_COINS CENTS_COIN[]={25, 10, 5, 1};
 const int CENTS_PER_DOLLAR=100;
 const int MAX_SAFE_INT=21474836;
 
 
int main (void){
    float change;
    int number_coins=0;
    int coin_count=sizeof(CENTS_COIN)/sizeof(TYPE_COINS);
    printf("O hai! ");
    do{
       printf("How much change in dollars is owed?\n");
       change=get_float();
    }while(change<0 || change>MAX_SAFE_INT);
    
    TYPE_COINS cents_change=round(change*CENTS_PER_DOLLAR);
    
    for(int i=0;i<coin_count;i++){
        while(cents_change>=CENTS_COIN[i]){
              cents_change-=CENTS_COIN[i];
              number_coins++;
        }
    }
    //output result
    printf("%d\n",number_coins);
}