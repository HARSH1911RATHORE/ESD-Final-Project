#include "Remote_functions.h"
#include "remote_key.h"
#include "Dc_motor_pwm.h"
#include "GLCD.h"
#include <stdio.h>
#include <stdlib.h>
#include<at89c51ed2.h>          ///include library functions needed for remote functions
#include <mcs51/8051.h>
#include <stdint.h>
volatile uint8_t timer_mili=0;  ///used for storing the count value of timer interrupt for pulse width
volatile uint8_t mili_count=0;    ///used for calculating 1ms timer interrupt
volatile int pulseCount=0;    ///calculating number of pulses
extern volatile uint32_t bitPattern;  ///forming the binary bit pattern
extern volatile uint32_t newKey;     ///storing value of bit pattern into variable
extern volatile uint8_t remote_flag;
volatile int8_t power_key=0;         ///used for reprogrammable remote functionality
volatile int8_t back_key=0;
volatile int8_t home_key=0;

#define Bulb P1_2             ///defining port at which led is placed


/****************************************Timer T0 interrupt*****************************************
This function is used for detecting the pulse width by incrementing the count of a variable that passes through the interrupt every 1 ms and
hence we find the pulse width by measuring this variable count with the time the external edge of arrives, which gives us the pulse width
*****************************************************************************************************/
void timer0_isr() __interrupt 1
{
    if(mili_count<50)
        mili_count++;

    TH0 = 0xFC;   // Reload the timer value for 1ms Delay
    TL0 = 0x67;
}

/****************************************External INT0 interrupt*****************************************
This function is used for detecting the number of pulses through the external hardware pin
The interrupt triggers on every falling edge of the pulse
*****************************************************************************************************/

void externalIntr0_ISR()  __interrupt 0
{

    timer_mili = mili_count;
    mili_count = 0;

    TH0 = 0xFC;  /// Reload the timer value for 1ms Delay
    TL0 = 0x67;

    pulseCount++;

    if((timer_mili>=50)) /// If the pulse width is greater than 50ms, the new pulse start of frame is present
    {
        pulseCount = -2; ///the value of first 2 counts is not included as part of the 32 bit address and command bits,therefore pulse count is -2
        bitPattern = 0;  ///and therefore bit pattern is 0
    }
    else if((pulseCount>0) && (pulseCount<=32)) ///Accumulate  0-31 bit values
    {
        if(timer_mili>=2)                      ///pulse width greater than 2ms is considered as LOGIC1
        {
            bitPattern |=(uint32_t)1<<(31-pulseCount);
        }
        else
        {

        }
    }
    else if(pulseCount>=32)                  ///32 pulses are received, hence we store it into the bit pattern
    {
        newKey = (bitPattern>>4);                /// Copy the newKey(patter) and set the pulse count to 0;

        pulseCount = 0;
        remote_flag=1;

        printf("newKey=%lu\n\r",newKey);       ///display the pattern on uart
        if (newKey!=0)
        {

            if (newKey==power || newKey==power1 ||(newKey==power && newKey==32763231 && newKey==66580479))
            {

                if(power_key==1)                           ///if power key is programmed as motor, motor will turn on
                {
                    motor_direction_pin1=0;
                    motor_direction_pin1=1;
                    printf_tiny("\n\rmotor\n\r");
                }
                else if(power_key==2)                    ///if power key is programmed as light, light will turn on
                {
                    Bulb=Bulb^1;
                    printf_tiny("\n\rlight\n\r");
                    CR=0;
                }
                else if (power_key==3)                  ///if power key is programmed as to display a message on glcd, glcd will turn on
                {
                    allClear();
                    setCursor(1,0);
                    stringDisp(" POWER BUTTON");

                }
            }
            if(newKey==back || newKey==back1)
            {

                if(back_key==1)               ///if back key is programmed as motor, motor will turn on
                {
                    motor_direction_pin1=0;
                    motor_direction_pin1=1;
                    printf_tiny("\n\rmotor\n\r");

                }
                else if(back_key==2)        ///if back key is programmed as light, light will turn on
                {
                    Bulb=Bulb^1;

                    CR = 0;

                }
                else if (back_key==3)    ///if back key is programmed as to display a message on glcd, glcd will turn on
                {
                    allClear();
                    setCursor(1,0);
                    stringDisp(" BACK KEY");
                    CR = 0;
                }
            }
            if(newKey==home || newKey==home1)   ///if home key is programmed as motor, motor will turn on
            {
                if(home_key==1)
                {
                    motor_direction_pin1=0;
                    motor_direction_pin1=1;
                    printf_tiny("\n\rmotor\n\r");

                }
                else if(home_key==2)        ///if home key is programmed as light, light will turn on
                {
                    Bulb=Bulb^1;
                    CR = 0;

                }
                else if (home_key==3)      ///if home key is programmed as to display a message on glcd, glcd will turn on
                {
                    setCursor(1,0);
                    stringDisp("  HOME BUTTON");

                }

            }
            if(newKey==up_arrow || newKey==up_arrow1) ///set to increase speed of dc motor
            {
                allClear();
                setCursor(0,0);
                stringDisp("INCREASE SPEED ");
            }
            if(newKey==right_arrow || newKey==right_arrow1)  ///set to stop dc motor
            {
                printf_tiny("\n\rright\n\r");
                motor_direction_pin1=1;
                motor_direction_pin1=0;

                P1_2=P1_2^1;

            }
            if(newKey==down_arrow || newKey==down_arrow1)   ///set to decrease speed of dc motor
            {
                allClear();
                setCursor(0,0);
                stringDisp("REDUCE SPEED");


            }
            if(newKey==left_arrow || newKey==left_arrow1)  ///set to start dc motor
            {
                printf_tiny("\n\rleft\n\r");
                motor_direction_pin1=0;
                motor_direction_pin1=1;

            }
            if(newKey==ok_key || newKey==ok_key1)         ///set to turn light on
            {
                P1_2=P1_2^1;
            }

            if(newKey==night_mode_key || newKey==night_mode_key1) ///set to turn light on
            {

                P1_2=P1_2^1;

            }
            if(newKey==brightness_key || newKey==brightness_key1) ///set to turn light on
            {

                P1_2=P1_2^1;

            }
            if(newKey==rewind_key || newKey==rewind_key1)  ///set to switch direction of dc motor
            {

                P1_2=P1_2^1;

            }
            if(newKey==fast_forward_key || newKey==fast_forward_key1) ///set to turn light on
            {
                P1_2=P1_2^1;

            }
            if(newKey==advance_key || newKey==advance_key1) ///set to turn light on
            {

                P1_2=P1_2^1;

            }
        }

    }
}


/*****************************IR REMOTE INIT***********************************
THIS FINCTION CONTAINS ALL INIT REQUIREMENTS FOR DETECTION OF NEC PROTOCOL
TIMER 0 IS USED FOR GENERATING 1 ms interrupt
INT0 is used for triggering an interrupt every falling edge of the pulse
****************************************************************************/
void IR_RemoteInit(void)
{
    TMOD |= 0x01;  /// Timer0 MODE1(16-bit timer)
    TH0 = 0xFC;    /// Timer value for 1ms at 11.0592Mhz clock
    TL0 = 0x67;
    TR0 = 1;       /// Start the Timer
    ET0 = 1;       /// Enable the Timer0 Interrupt

    IT0 = 1;       /// Configure external INT0 falling edge interrupt
    EX0 = 1;       /// Enable the INT0 External Interrupt

    EA  = 1;       /// Enable the Global Interrupt bit
}



