#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>

const long long MAX_CREDIT_CARD_NUMBER=9999999999999999;
const int KABAL_SUM[]={0,2,4,6,8,1,3,5,7,9};
const int ASCII_TO_DIGIT=48;

int main(void)
{
  int number_digits_credit=0;
  long long number_credit_card, number_credit_card2;
  int sum_chet=0;
  int sum_nechet=0;
  char valid[4][12]={"INVALID\n","VISA\n","MASTERCARD\n","AMEX\n"};
  int validator=0;
  do{
     printf("Number:"); 
     number_credit_card=get_long_long();  
  }while(number_credit_card<1 || number_credit_card>=MAX_CREDIT_CARD_NUMBER);
  //считаем количество цифр
  number_credit_card2=number_credit_card;
  do{
     number_digits_credit++;
  }while(number_credit_card2/=10);
  //печатаем число в массив типа чар
  char *number;
  number=(char*)malloc(number_digits_credit*sizeof(char));
  sprintf(number, "%llu", number_credit_card);
  //проводим операции с четными и нечетными числами
  for(int count=0,i=0;count<number_digits_credit;count++){
        i=number_digits_credit-count-1;
        if((count+1)%2!=0)sum_nechet+=((int)number[i]-ASCII_TO_DIGIT);  
        else sum_chet+=KABAL_SUM[((int)number[i]-ASCII_TO_DIGIT)];
  }
  //проверяем компании
  if((sum_chet+sum_nechet)%10==0){
     int first_digit=(int)number[0]-ASCII_TO_DIGIT;
     int second_digit=(int)number[1]-ASCII_TO_DIGIT;
     if(first_digit==4){
          if(number_digits_credit==13||number_digits_credit==16)validator=1;
     }
     else if(first_digit*10+second_digit>50&&first_digit*10+second_digit<56){
          if(number_digits_credit==16)validator=2;
     }
     else if(first_digit*10+second_digit==34||first_digit*10+second_digit==37){
          if(number_digits_credit==15)validator=3;
     }
  }
  printf("%s",valid[validator]);
  free(number);
  return 0;
}