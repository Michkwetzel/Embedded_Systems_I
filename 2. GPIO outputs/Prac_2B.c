//******************************************************************** //* EEE2046F C example * //*==================================================================* 
//* WRITTEN BY: Michael Wetzel
//* DATE CREATED: 21 April 2018
//*==================================================================*
//* PROGRAMMED IN: Eclipse Neon 3 Service Release 1 (4.4.1)
//* DEV. BOARD: UCT STM32 Development Board
//* TARGET: STMicroelectronics STM32F051C6 
//*==================================================================* 
//* DESCRIPTION: * 
// Work with GPIO outputs of STM32F
//==================================================================== // INCLUDE FILES //==================================================================== 
#include "lcd_stm32f0.h"
#include "stm32f0xx.h"
//==================================================================== // SYMBOLIC CONSTANTS //==================================================================== 
#define Delay1 650
#define Delay2 5000 
//==================================================================== // GLOBAL VARIABLES //====================================================================
//==================================================================== // FUNCTION DECLARATIONS //==================================================================== 
void init_GPIOB(void);
void Delay(); 
//==================================================================== // MAIN FUNCTION //==================================================================== 
void main (void)
{
    init_GPIOB();
    init_LCD(); // Initialise lcd
    lcd_putstring("Michael Wetzel"); // Display string on line 1
    lcd_command(LINE_TWO);
    lcd_putstring("WTZMIC001");
    int bitpattern1 = 0b0;
    int bitpattern2 = 0b11111111;
    int bitpattern3 = 0b10101010;
    int counter = 0;  //counter that keeps treck of which pattern was displayed last
  
    for(;;) {  // Loop forever
        switch(counter){            //statement which checks which pattern must be displayed
            case 0 :
                GPIOB->ODR = bitpattern1;
                counter ++;
                break;
            case 1 : 
                GPIOB->ODR = bitpattern2;
                counter ++;
                break;
            case 2 :
                GPIOB->ODR = bitpattern3; 
                counter = 0;
                break;
        }
        for (int i = 0 ;i<=650;i++) {        //Delay of aprox 1 second
            for(int j = 0;j<=5000;j++);
        }
        
        char value[8] = {0,0,0,0,0,0,0,0};  //Create default Value
        int counter;
        //initialise all variables
        int newnum;
        int remainder = 0;


        for (int i=0;i<256;i++){       //loop must run 255times (there are 255 decimal number representations with 8 bits) 
              counter = 7;
              //modifying value from back to front so start with last index     
              newnum = i;
              //number to be converted to binary   
               while(newnum != 0){ // Run until number is fully converted
                  remainder = newnum%2;
                  newnum = newnum/2;
                  value[counter] = remainder; //add remainder to value
                  counter --;     //Move backward another place
                }
          
                char str[9];  //Change value into format that can be output to LCD
                int i=0;
                int index = 0;
                for (i=0; i<8; i++){
                  index += sprintf(&str[index], "%d", value[i]);
                  }
                init_LCD();  //// Initialise lcd eachtime to clear lcd of previous value
                lcd_putstring(str);
                for (int i = 0 ;i<=500;i++){ //generate approx 1 sec delay
                    for(int j = 0;j<=5000;j++);  
                } 
                int bitpattern = 0b1; // Loop start at 1st LED lighting up
        }

          for(;;){
            if (bitpattern == 0b1000000000){ //if the pattern is at its end restart again
            int bitpattern = 0b1; start at 1st LED lighting up
            }

            GPIOB->ODR = bitpattern;  
            bitpattern = bitpattern<<1;

            for (int i = 0 ;i<=500;i++) { //generate approx 1 sec delay
                for(int j = 0;j<=5000;j++);
            }
         }


//==================================================================== // FUNCTION DEFINITIONS //==================================================================== 
void init_GPIOB(void)
{
    RCC  ->AHBENR |= 1<<18;
    GPIOB->MODER  |= 0x00505555;
    GPIOB->ODR     = 0b0000010000001111;
}
void Delay(){
    for(int i=0;i<Delay1;i++){
        for(int j=0;j<Delay2;j++){ 
        }
    } 
}
//******************************************************************** // END OF PROGRAM //********************************************************************
