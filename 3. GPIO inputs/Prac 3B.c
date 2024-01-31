#include <stdio.h> 
#include <stdlib.h> 
#include "diag/Trace.h" 
#include "stm32f0xx.h"

char CountUp(char value); 
char CountDown(char value);

void main(void){ 
    char info;
    InitPorts();
    /*for(;;){
      info = GPIOA -> IDR;
      if ((info & 0b1) == 0){ 
        GPIOB -> ODR = 0b1;
      } 
    }
    */
    char nextValue = 0; 
    char upDown = 1; 
      for(;;) {
        while(upDown == 1){ 
          Delay();
          nextValue = CountUp(nextValue);
          info = GPIOA -> IDR;           //gett current state of IDR
          if((info & 0b10) == 0){        //if button 2 gets pressed
            upDown = 0;                  //set upDown to 0 which will exit curent
            nextValue--;
          }
          if(nextValue == 256){       //if max value is reached reset to 0
            nextValue = 0;
          }
    }
    }
}

void InitPorts(void){
    RCC ->AHBENR |= 11<<17; //activate B and A clock 
    GPIOB->MODER |= 0x00505555; //set LED's to output mode 
    GPIOA->MODER |= 0b00000000; // set push buttons to input mode
    GPIOB->ODR |= 0b00000000; //turns off led's
    GPIOA->PUPDR |= 0b01010101; // sets push bottons to pull up resistors on
}          

char CountUp(char value){ 
    GPIOB-> ODR |= value;
    char newvalue = value++; 
    return newvalue;
}

char CountDown(char value){ 
    GPIOB -> ODR |= value;
    char newvalue = value--; 
    return newvalue;
}

void Delay(void){
    for(int i = 0;i<=650;i++)
 }




