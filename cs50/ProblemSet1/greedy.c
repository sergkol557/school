#include <stdio.h>
#include <cs50.h>
#include <math.h>

 const int CENTS_COIN[]={25, 10, 5, 1};
 const int CENTS_PER_DOLLAR=100;
 const float MAX_SAFE_INT=21474830;
 const int START_ARRAY_POSITION=0;
 const int START_COINS_COUNT=1;
//=================================================================================================================
float getChange(){
      float change=0.0;
      do{
         printf("How much change in dollars is owed?\n");
         change=get_float();
      }while(change<0 || change>MAX_SAFE_INT);
      return change;
}
//=================================================================================================================
//with recursion
int recursiveCheckNumberCoins(int change,int count, int position){
    while(change<CENTS_COIN[position]){
          position++;
          if (position>(sizeof(CENTS_COIN)/sizeof(int)-1)){ 
              return 0;
          }
    }
    count+=recursiveCheckNumberCoins(change-CENTS_COIN[position],1,position);
    
    return count;
}

//=================================================================================================================
//without recursion
int checkNumberCoins(int cents_change){
        int coins=0;
        for(int i=0;i<sizeof(CENTS_COIN)/sizeof(int);i++){
            while(cents_change>=CENTS_COIN[i]){
                    cents_change-=CENTS_COIN[i];
                    coins++;
            } 
        }
        return coins;
}
//=================================================================================================================
int main (void){
    printf("O hai! ");
    printf("%d\n",recursiveCheckNumberCoins(round(getChange()*CENTS_PER_DOLLAR),START_COINS_COUNT,START_ARRAY_POSITION));
    return 0;
}
//=================================================================================================================