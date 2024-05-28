#include <stdio.h>
#include <math.h>

// Constants
#define TWO_PI 6.28318530718
#define SAMPLE_TIME 0.01 // Sampling time in seconds (example: 0.01s)

typedef struct {
    float angle;      
    float frequency;  
    float error;     
    float integral;  
    float Kp;  
    float Ki;        
} PLL;
void initPLL(PLL *pll, double Kp, double Ki) {
    pll->angle = 0.0;
    pll->frequency = 0.0;
    pll->error = 0.0;
    pll->integral = 0.0;
    pll->Kp = Kp;
    pll->Ki = Ki;
}

void updatePLL(PLL *pll, double measured_sin, double measured_cos) {
    // Current estimated sine and cosine values based on the estimated angle
    double estimated_sin = sin(pll->angle);
    double estimated_cos = cos(pll->angle);
    
    // Calculate the error
    pll->error = measured_sin * estimated_cos - measured_cos * estimated_sin;
    
    // Proportional-Integral control
    pll->integral += pll->error;
    double control_signal = pll->Kp * pll->error + pll->Ki * pll->integral;
    
    // Update the estimated frequency
    pll->frequency = control_signal;
    
    // Update the estimated angle
    pll->angle += pll->frequency;
    
    // Wrap the estimated angle between 0 and TWO_PI
    if (pll->angle >= TWO_PI) {
        pll->angle -= TWO_PI;
    } else if (pll->angle < 0.0) {
        pll->angle += TWO_PI;
    }
}

 float angle = 0;
int main() {
    PLL pll;
    initPLL(&pll, 1.0, 0.1); // Example gains for Kp and Ki
    while (1)
    {
        updatePLL(&pll, sin(angle),cos(angle));
        angle+= 0.01;
        printf("%f,%f,%f\n",pll.frequency,angle,pll.angle);
        if(angle >= 5){
            break;
        }
    }
    


    return 0;
}
