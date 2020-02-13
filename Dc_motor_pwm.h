
#ifndef _DC_MOTOR_PWM_H_
#define _DC_MOTOR_PWM_H_
/*****************************************************************************​​*​​
​​*HARSH RATHORE​​
*UNIVERSITY OF COLORADO BOULDER
*FALL 2019
*EMBEDDED SYSTEMS DESIGN
​​******************************************************************************/
/// **​​*​​@file​ ​name DC_motor_pwm.h
/// *​​@pwm commands and variables
​​/// **this header file contains all the dc motor functions,its prototypes and variables
​​​​/// *​​*​​@author​​ Harsh Rathore
​​///@reference-https://www.electronicwings.com/8051/dc-motor-interfacing-with-8051
​​​/// *​​@ date 1st Dec 2019
​​​​/// *​​@version​​1.0​
​​/// */

#include <stdint.h>
extern volatile uint8_t motor_direction_pin1;
extern volatile uint8_t motor_direction_pin2;

/**​​
*​​@brief​​ sets the initial values of the timer2 low and high register and starts the timer
*​​*​​Given​​ none

*​​@param​​ none
*​​*​​@return​​ void.​​
*/

void Timer_init();

/**​​
*​​@brief​​ sets the initial values of the timer2 low and high register and starts the timer
*​​*​​Given​​ none

*​​@param​​ none
*​​*​​@return​​ void.​​
*/
void Motor_Init();                               ///prototype declaration of dc motor functions
/**​​
*​​@brief​​ sets the values of the duty cycle for speed control and pins for direction control
*​​*​​Given​​ afloat duty cycle
​​

*​​@param​​  ​​duty cycle value to be set for pwm dc motor
*​​*​​@return​​ void.​​
*/
void Set_DutyCycle_To(float duty_cycle);
/**​​
*​​@brief​​ the interrupt handler function which triggers depending on the timer load value
*​​*​​Given​​ none

*​​@param​​ none
*​​*​​@return​​ void.​​
*/
void Timer0_ISR() __interrupt 5;

#endif
