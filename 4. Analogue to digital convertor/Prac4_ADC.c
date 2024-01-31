
#include <stdio.h>
#include "lcd_stm32f0.h"
#include "stm32f0xx.h"

void main (void) {
    init_GPIOB();
    init_LCD();                                //Initialize LCD
    
    lcd_putstring("EEE2046F Prac 2B");         // Display string on line 1
    lcd_command(LINE_TWO);                     // Move cursor to line 2
    lcd_putstring("****************");         // Display string on line 2

    for(;;) {                                  // Loop forever
        GPIOB->ODR = ~GPIOB->ODR; 
        for (int i = 0 ;i<=100;i++)
            for(int j = 0;j<=5000;j++);
    }
}                                               //End of Main

void init_GPIOB(void) {
    RCC -> AHBENR |= 11<<17;
    GPIOA -> MODER |= 0b111111110011; 
    GPIOA -> PUPDR |= 0b01010101;
    GPIOB -> MODER |= 0b0101010101010101;
}

void init_ADC(void){
    GPIOA -> MODER |= GPIO_MODER_MODER5; 
    RCC -> APB2ENR |= RCC_APB2ENR_ADCEN;
    ADC1 -> CR &= ~ADC_CR_ADSTART;
    ADC1 -> CFGR1 |= ADC_CFGR1_RES_1;
    ADC1 -> CFGR1 &= ~ADC_CFGR1_RES_0;
    ADC1 -> CFGR1 &= ~ADC_CFGR1_ALIGN;
    ADC1 -> CFGR1 |= ADC_CFGR1_CONT;
    ADC1 -> CHSELR |= ADC_CHSELR_CHSEL5; 
    ADC1 -> CR |= ADC_CR_ADEN;
    ADC1 -> CFGR1 |= ADC_CFGR1_SCANDIR; 
    while((ADC1->ISR & ADC_ISR_ADRDY) == 0); 
    ADC1 -> CR |= ADC_CR_ADSTART;
    while((ADC1->ISR & ADC_ISR_EOC) == 0);
}

void check_battery(void){ ADC1 -> CR |= 0b10000;
    char value = ADC1->DR;                        //get value from adc float 
    batVoltage = value*(0.09411);
    lcd_putstring("Battery V:"); 
    lcd_command(LINE_TWO);                        //code to display info on lcs 
    lcd_putstring(value);
    if (batVoltage > 149){
        GPIOB -> ODR |= 0b1000000000;
    } 
    else {            //checks if batery voltage is low or high 
        GPIOB -> ODR &= ~0b1000000000;
    }
}


void display(){
    if ((GPIOA ->IDR & 0b1) !=1){                //if button 0 is pressed
        lcd_command(CLEAR); 
        lcd_putstring("EEE2046F Prac4B"); 
        lcd_command(LINE_TWO); 
        lcd_putstring("Michael");
    }
    else if((GPIOA ->IDR & 0b10) != 1){         //if button 1 is pressed 
        lcd_command(CLEAR);
        lcd_putstring("EEE2046F Prac4B"); 
        lcd_command(LINE_TWO); 
        lcd_putstring("Press SW2");
    }
    else if((GPIOA ->IDR & 0b100) != 1){        //if button 2 is pressd 
        lcd_command(CLEAR);
        check_battery();                        //display batery voltage
    }
}

//******************************************************************** // END OF PROGRAM //********************************************************************
