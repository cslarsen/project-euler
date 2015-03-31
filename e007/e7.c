#include <stdio.h> 
#include <math.h> 

#define ulong unsigned long

int main(void) 
{ 
    ulong x;
    ulong y; 
    ulong z; 
    ulong cnt = 1; 
  
    printf("Prime %5d = %6d \n", 1, 2); 
  
    for (x = 3 ; cnt <= 10001 ; x++) 
    { 
        z = 0; 
    
        for (y = 2 ; y <= sqrt(x) ; y++) 
        { 
            if ((x % y) == 0) 
            { 
                z++; 
                break; 
            } 
        } 
  
        if (z == 0) 
        { 
            cnt++; 
            if(cnt == 10001)
            {
                printf("Prime %5d = %6d \n", cnt, x); 
            }
        } 
    }
    return 0; 
}
