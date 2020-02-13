#include "Dc_motor_pwm.h"
#include <stdio.h>
#include <stdlib.h>
#include<at89c51ed2.h>          ///include library functions needed for dc motor control
#include <mcs51/8051.h>
#include <stdint.h>
#define PWM_Out_Pin  P1_3	    /// PWM Out Pin for speed control

#define PWM_Period 0xA5FD       ///PWM period of 25 ms set at the start

#define M1_Pin1		 P1_0	   /// Motor Pin 1
#define M1_Pin2		 P2_1	   /// Motor Pin 2
extern volatile uint16_t OFF_Period, ON_Period,Speed;  ///Variables defined for pwm speed control at ever
                                                        ///key pressed on the remote by changing the timer count for pwm in th2 and tl2 register
volatile uint8_t duty_cycle=0;  ///duty cycle of pwm
int period = 65535 - PWM_Period;  ///100 percent period of pwm set as period


/*****************************Timer 2 INIT***********************************
THIS FINCTION CONTAINS ALL INIT REQUIREMENTS FOR PWM speed and direction specification of the dc motor
TIMER 2 IS USED FOR GENERATING capture compare mode of timer 2 interrupt where value is loaded as 81 hex in T2CON
****************************************************************************/
void Timer_init()
{
    M1_Pin1=1;                   ///m1 and m2 pin are used to set direction of motor pin as clockwise initially
    M1_Pin2=0;
    T2CON = 0x81;                ///to set the timer in capture compare mode
    PWM_Out_Pin=0;               ///initially set the output pin as 0


    TH2 = (0xA5);               /// 25ms timer value
    TL2 = 0xFD;


    ET2 = 1;                      /// Enable Timer 2 Interrupts
    TR2 = 1;                      /// Start Timer 2 Running
    EA = 1;                      ///enable global interrupt


}

/****************************************Timer 2 interrupt*****************************************
This function is used for changing the speed of dc motor on particular key presses on the remote
It changes the on and off time period by loading different values in the th2 and tl2 register
*****************************************************************************************************/
void Timer0_ISR() __interrupt 5
{
    M1_Pin1=motor_direction_pin1;      ///initially set the motor pin as 1 and 0 for clockwise rotation
    M1_Pin2=motor_direction_pin2;
    TF2=0;                             ///Timer overflow flag is reset on visit to the interrupt
    PWM_Out_Pin =!PWM_Out_Pin;         ///toggle outpin pin of motor

    if(PWM_Out_Pin)                    ///if pwm out pin is high we will load the value of th2 and tl2 as defined by on period
    {

        TH2 = ((ON_Period)>>8);
        TL2 = ON_Period;
    }
    else                              ///if pwm out pin is low we will load the value of th2 and tl2 as defined by off period
    {
        TH2 = (OFF_Period>>8);
        TL2 = OFF_Period;
    }

}


/// Calculate period & duty cycle for pwm by changing the on and off period
void Set_DutyCycle_To(float duty_cycle)
{
    float period = 65535 - PWM_Period;           ///period of 100 percent duty cycle is set as period at start
    ON_Period = ((period/100.0) * duty_cycle);   ///on period is period divided by 100 into duty cycle,changed which every key pressed which corresponds to the specific function
    OFF_Period = (period - ON_Period);           ///off period is period found by subtracting on period from period
    ON_Period = 65535 - ON_Period;               ///the value to be loaded in the register is 0xffff minus the on period
    OFF_Period = 65535 - OFF_Period;             ///the value to be loaded in the register is 0xffff minus the off period
}

/// Initially Speed & Duty cycle  of the motor is set to zero and is in clockwise direction
void Motor_Init()
{
    Speed = 0;           ///speed zero
    M1_Pin1 = 1;         ///clockwise direction
    M1_Pin2 = 0;
    Set_DutyCycle_To(Speed);
}
