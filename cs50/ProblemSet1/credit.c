#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <math.h>


const long long MAX_CREDIT_CARD_NUMBER=9999999999999999;
const int KABAL_SUM[]={0,2,4,6,8,1,3,5,7,9};
const int ASCII_TO_DIGIT=48;
const char valid[4][11]={"INVALID","VISA","MASTERCARD","AMEX"};
//=================================================================================================================
long long getCardNumber(){
          long long CardNumber=0;
          do{
          printf("Number:"); 
          CardNumber=get_long_long();  
          }while(CardNumber<1 || CardNumber>=MAX_CREDIT_CARD_NUMBER);
          return CardNumber;
}
//=================================================================================================================
int countDigits(long long number){
    int number_digits=0;
    do{
    number_digits++;
    }while(number/=10);
    return number_digits;
}
//=================================================================================================================
int CharToInt(int simbol){
    return simbol-ASCII_TO_DIGIT;
}
//=================================================================================================================
int checkSumm(long long number,int lenght){
    int sum_chet=0;
    int sum_nechet=0;
    //char *simvol_number;
    //simvol_number=(char*)malloc((lenght+1)*sizeof(char));
    char simvol_number[lenght+1];
    sprintf(simvol_number, "%llu", number);
    for(int count=0,i=0;count<lenght;count++){
        i=lenght-count-1;
        if((count+1)%2!=0)sum_nechet+=CharToInt(simvol_number[i]);  
        else sum_chet+=KABAL_SUM[CharToInt(simvol_number[i])];
    }
    //free(simvol_number);
    if((sum_chet+sum_nechet)%10==0) return (int)(number/pow(10,lenght-2));
    else return -1;
}
//=================================================================================================================
int checkCreditCompany(int first_digits,int lenght){
    if(first_digits/10==4 && (lenght==13 || lenght==16)) return 1; 
    else if(first_digits>50 && first_digits<56 && lenght==16) return 2;
    else if((first_digits==34 || first_digits==37) && lenght==15) return 3;
    
    return 0;
}
//=================================================================================================================
int main(void)
{
  long long number_credit_card=getCardNumber();
  int number_digits_credit=countDigits(number_credit_card);
  printf("%s\n",valid[checkCreditCompany(checkSumm(number_credit_card,number_digits_credit),number_digits_credit)]);
  return 0;
}
//=================================================================================================================