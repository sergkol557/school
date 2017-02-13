#include <stdio.h>
#include <cs50.h>

const int PIRAMIDE_MAX_HEIGHT=23;

//=================================================================================================================
int getPiramideHeight(){
    int height;
    do{
       printf("Height:");    
       height=get_int();    
    }while(height<0||height>PIRAMIDE_MAX_HEIGHT);
    return height;
}
//=================================================================================================================
void drawPiramideRaw(int row, int height){
     int row_hashes=row+1;
     int row_spaces=height-row_hashes;
     for(int count_spaces=0;count_spaces<row_spaces;count_spaces++){
         printf(" ");
     }
     for(int count_hashes=0;count_hashes<row_hashes;count_hashes++){
         printf("#");
     }
     printf("  ");
     for(int count_hashes=0;count_hashes<row_hashes;count_hashes++){
         printf("#");
     }
     printf("\n");
}
//=================================================================================================================
int main(void){
    int piramide_height=getPiramideHeight();
    for(int count_row=0;count_row<piramide_height;count_row++){
        drawPiramideRaw(count_row,piramide_height);
    }
    return 0;
}
//=================================================================================================================