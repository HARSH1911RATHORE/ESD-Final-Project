#include <stdio.h>
#include <stdlib.h>
#include<at89c51ed2.h>          ///include library functions needed FOR input
#include <mcs51/8051.h>
#include <stdint.h>
#include "remote_key.h"
#include "LCD.h"
#include "GLCD.h"
#include "Dc_motor_pwm.h"
#include "Keypad.h"
#include "Remote_functions.h"
#include "Sevensegment.h"
volatile uint32_t bitPattern=0,newKey=0;            ///bitpattern, newkey is set t zero as initialized as extern
volatile uint8_t motor_direction_pin1=1;
volatile uint8_t motor_direction_pin2=0;

unsigned char seven_seg[]= {0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90};    ///hex values for displaying 0 to 9
unsigned char seven_seg_alp[]= {0x88,0x80,0xC6};
#define Bulb P1_2
#define ir P1_7


volatile uint32_t keyCode;                   ///keypad key
volatile char mode;                          ///mode for re-programmable function
volatile char input1;
extern volatile int8_t power_key;
extern volatile int8_t back_key;            ///back key, power key and back key on remote
extern volatile int8_t home_key;
volatile uint8_t motor;
volatile uint8_t remote_flag=0;

volatile uint8_t keypad=0;
volatile uint16_t OFF_Period=0, ON_Period=0,Speed=0;

#define M1_Pin1		 P1_0	                  /// Motor Pin 1 set pin
#define M1_Pin2		 P2_1	                  /// Motor Pin 2  set pin



void msdelay(unsigned int time)              /// Function for creating delay in milliseconds.
{
    unsigned i,j ;
    for(i=0; i<time; i++)
        for(j=0; j<1275; j++);
}

/// Function to provide delay of 1ms at 11.0592 MHz
void delay2(unsigned int count)
{
    int i,j;
    for(i=0; i<count; i++)
        for(j=0; j<112; j++);
}

void delay1(unsigned int count)                        ///delay for glcd
{
    int i,j;
    for(i=0; i<count; i++)
        for(j=0; j<112; j++);
}

void switchs(char keys)
{
    printf("\n\r mode=%c\n\r",mode);
    switch(keys)
    {
    case('A'):
    {
        P0=seven_seg_alp[0];
        setCursor(0,0);

        stringDisp(" POWER BUTTON     SELECTED");                ///Print string to GLCD
        if (mode=='1')
            power_key=1;
        else if (mode=='2')                                     ///to find the particular key THE OPERATION needs to be mapped to
            power_key=2;                                        ///MODE1 = power, MODE2 = BACK KEY, MODE3 = HOME KEY
        else if(mode=='3')
            power_key=3;
        break;
    }
    case('B'):
    {
        P0=seven_seg_alp[1];
        setCursor(0,0);
        ///Print string to LCD
        stringDisp("  BACK BUTTON      SELECTED");                ///Print string to GLCD
        if (mode=='1')
            back_key=1;
        else if (mode=='2')                                     ///to find the particular key THE OPERATION needs to be mapped to
            back_key=2;
        else if(mode=='3')                                      ///MODE1 = power, MODE2 = BACK KEY, MODE3 = HOME KEY
            back_key=3;
        break;
    }
    case('C'):
    {
        P0=seven_seg_alp[2];
        setCursor(0,0);
        ///Print string to LCD
        stringDisp("  HOME BUTTON     SELECTED");                ///Print string to GLCD
        if (mode=='1')
            home_key=1;
        else if (mode=='2')                                    ///to find the particular key THE OPERATION needs to be mapped to
            home_key=2;
        else if(mode=='3')                                     ///MODE1 = power, MODE2 = BACK KEY, MODE3 = HOME KEY
            home_key=3;
        break;
    }
    default:
    {
        printf_tiny("\n\rINVALID INPUT\n\r");
    }

    }


}

void main()
{
    M1_Pin1=1;
    M1_Pin2=0;
    lcdinit();                     ///LCD INITIALIZATION
    lcdbusywait();
    lcd_instruction_write(0x40);   ///setting cgram address
    lcdbusywait();
    lcdputch(0x00);                ///the custom  characters first row
    lcdbusywait();
    lcd_instruction_write(0x41);   ///first custom character row 1
    lcdbusywait();
    lcdputch(0x1B);               ///the custom  characters second row
    lcdbusywait();
    lcd_instruction_write(0x42); ///first custom character row 2
    lcdbusywait();
    lcdputch(0x00);              ///the custom  characters third row
    lcdbusywait();
    lcd_instruction_write(0x43); ///first custom character row 3
    lcdbusywait();
    lcdputch(0x04);             ///the custom  characters fourth row
    lcdbusywait();
    lcd_instruction_write(0x44); ///first custom character row 4
    lcdbusywait();
    lcdputch(0x04);            ///the custom  characters fifth row
    lcdbusywait();
    lcd_instruction_write(0x45); ///first custom character row 5
    lcdbusywait();
    lcdputch(0x11);           ///the custom  characters sixth row
    lcdbusywait();
    lcd_instruction_write(0x46); ///first custom character row 6
    lcdbusywait();
    lcdputch(0x0E);          ///the custom  characters seventh row
    lcdbusywait();
    lcd_instruction_write(0x47);
    lcdbusywait();
    lcdputch(0x00);
    lcdbusywait();
    lcdgotoxy(0,7);         ///print the custom character at various locations
    lcdbusywait();
    lcdputch(0);            ///print the 0th custom character
    lcdgotoxy(1,7);
    lcdbusywait();
    lcdputch(0);
    lcdgotoxy(2,7);
    lcdbusywait();
    lcdputch(0);
    lcdgotoxy(3,7);
    lcdbusywait();
    lcdputch(0);

    lcdgotoxy(0,0);
    lcdbusywait();
    lcdputstr("1.MOTOR A.POWER");   ///display the re-programmable functions for the different keys on lcd for ease of input
    lcdgotoxy(1,0);
    lcdbusywait();
    lcdputstr("2.LIGHT B.BACK");
    lcdgotoxy(2,0);
    lcdbusywait();
    lcdputstr("3.GLCD  C.HOME");
    lcdbusywait();
    lcdgotoxy(3,1);            ///print the custom character at different location
    lcdbusywait();
    lcdputch(0);
    lcdgotoxy(3,3);
    lcdbusywait();
    lcdputch(0);
    lcdgotoxy(3,5);
    lcdbusywait();
    lcdputch(0);
    lcdgotoxy(3,7);
    lcdbusywait();
    lcdputch(0);
    lcdgotoxy(3,9);
    lcdbusywait();
    lcdputch(0);
    lcdgotoxy(3,11);
    lcdbusywait();
    lcdputch(0);
    lcdgotoxy(3,13);
    lcdbusywait();
    lcdputch(0);
    lcdgotoxy(3,15);
    lcdbusywait();
    lcdputch(0);
    delay(1000);
    Initialize_LCD();

    Bulb = 0;	      /// Turn OFF the relay during Init
    IR_RemoteInit();  /// Initialize the INTO and Timer0 for decoding the IR pulses

    Timer_init();     ///timer init for pwm motor
    Motor_Init();
    msdelay(100);
    setPixel(0,0);

    while(1)
    {

        printf_tiny("Enter the operation which needs to mapped to a specific button\n\r");
        printf_tiny("\n\r1=MOTOR\n\r");
        printf_tiny("\n\r2=LIGHT\n\r");
        printf_tiny("\n\r3=GLCD\n\r");
        printf_tiny("\n\rM=MENU\n\r");
        mode=getchar();                          ///TAKE INPUT IN FORM A CHARACTER FORM USER
        putchar(mode);
        if(mode!=0)
        {

            if(mode=='1' || keypad==1)          ///if  mode is 1 or keypad pressed is 1 display on 7 segment display
            {
                P0=seven_seg[1];
                allClear();
                setCursor(0,0);
                ///Print string to LCD
                stringDisp("MOTOR SELECTED");
                printf_tiny("\n\r~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\r");
                printf_tiny("\n\rKEY to which the operation needs to be mapped to\n\r");
                printf_tiny("\n\rA=POWER\n\r");
                printf_tiny("\n\rB=BACK\n\r");
                printf_tiny("\n\rC=HOME\n\r");
                printf_tiny("\n\r~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\r");
                input1=getchar();                          ///TAKE INPUT IN FORM A CHARACTER FORM USER
                putchar(input1);
                switchs(input1);                    ///when motor is selected go to switchs, to find the particular key it needs to be mapped to

            }
            else if(mode=='2' || keypad==2)
            {
                P0=seven_seg[2];
                allClear();
                setCursor(0,0);
                ///Print string to LCD
                stringDisp("LIGHT SELECTED");
                printf_tiny("\n\r~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\r");
                printf_tiny("\n\rKEY to which the operation needs to be mapped to\n\r");
                printf_tiny("\n\rA=POWER\n\r");
                printf_tiny("\n\rB=BACK\n\r");
                printf_tiny("\n\rC=HOME\n\r");
                printf_tiny("\n\r~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\r");
                input1=getchar();                          ///TAKE INPUT IN FORM A CHARACTER FORM USER
                putchar(input1);
                switchs(input1);                  ///when light is selected go to switchs, to find the particular key it needs to be mapped to

            }
            else if(mode=='3' || keypad==3)
            {
                P0=seven_seg[3];
                allClear();
                setCursor(0,0);
                ///Print string to LCD
                stringDisp(" GLCD SELECTED");
                printf_tiny("\n\r~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\r");
                printf_tiny("\n\rKEY to which the operation needs to be mapped to\n\r");
                printf_tiny("\n\rA=POWER\n\r");
                printf_tiny("\n\rB=BACK\n\r");
                printf_tiny("\n\rC=HOME\n\r");
                printf_tiny("\n\r~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\r");
                input1=getchar();                          ///TAKE INPUT IN FORM A CHARACTER FORM USER
                putchar(input1);
                switchs(input1);                ///when glcd is selected go to switchs, to find the particular key it needs to be mapped to

            }
            else if(mode=='M')                   ///to print the menu again
            {
                printf_tiny("\n\r1=MOTOR\n\r");
                printf_tiny("\n\r2=LIGHT\n\r");
                printf_tiny("\n\r3=\n\r");
            }
            else
            {
                printf_tiny("\n\rINVALID INPUT\n\r");
            }
        }
    }
}

int putchar (int c)
{
    while (!TI);
                                            /// wait for TX ready, spin on TI
    SBUF = c;  	                            /// load serial port with transmit value
    TI = 0;  	                           /// clear TI flag
    return 0;
}

int getchar ()
{
    while (!RI)
    {   /// Increment Duty cycle i.e. speed by 10% for Speed_Inc Switch
        if( newKey== up_arrow || newKey==up_arrow1)  ///if the button pressed on remote is up
        {
            if(Speed < 100)                 ///if pwm speed is less than 100
                Speed += 10;                ///increase the pwm speed by 10 percent
            Set_DutyCycle_To(Speed);        ///set the new value of speed for the dc motor
            while(newKey==up_arrow);        ///wait till up arrow is being pressed
            delay(200);
        }

        /// Decrement Duty cycle i.e. speed by 10% for Speed_Dec Switch
        if(newKey == down_arrow || newKey==down_arrow1) ///if the button pressed on remote is up
        {
            if(Speed > 0)                   ///if pwm speed is greater than 0
                Speed -= 10;                ///decrease speed by 10 percent
            Set_DutyCycle_To(Speed);        ///set the new value of speed for the dc motor
            while(newKey == down_arrow);    ///wait till down arrow is being pressed
            delay(200);
        }
        /// Change rotation direction for Change_Dir Switch
        if(newKey == replay|| newKey == replay1 || newKey==ok_key || newKey==ok_key1) ///if the button pressed on remote is ok or replay
        {
            M1_Pin1 = !motor_direction_pin1;  ///toggle the pins which set the direction of pwm dc motor
            M1_Pin2 = !motor_direction_pin2;
            while(newKey == replay);        ///wait till replay is being pressed
            delay(200);
        };


    }                                      /// wait for RI ready, spin on RI
    /// wait for character to be received, spin on RI
    RI = 0;			                        /// clear RI flag
    return SBUF;  	                        /// return character from SBUF
}
