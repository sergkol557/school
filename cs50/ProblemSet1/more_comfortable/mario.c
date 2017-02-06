#include <stdio.h>
#include <cs50.h>

int main(void){
    int piramide_height;
    do{
       printf("Height:");    
       piramide_height=get_int();    
    }while(piramide_height<0||piramide_height>23);
    int piramide_width=piramide_height+1;
    int row_spaces, row_hashes;
    for(int row=0;row<piramide_height;row++){
        row_hashes=row+1;
        row_spaces=piramide_width-row_hashes-1;
        for(int count_spaces=0;count_spaces<row_spaces;count_spaces++)printf(" ");
        for(int count_hashes=0;count_hashes<row_hashes;count_hashes++)printf("#");
        printf("  ");
        for(int count_hashes=0;count_hashes<row_hashes;count_hashes++)printf("#");
        printf("\n");
    }
}