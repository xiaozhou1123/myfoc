#include <stdio.h>
#include "svpwm.h"
int main(void){
    RotationAxis temp = {1.0,0.0};
    float angle = 0;
    while (1)
    {
        
        Svpwm(&temp,angle);
        angle++;
        if(angle == 720){
            break;
        }
    }
    
    
    return 0;
}