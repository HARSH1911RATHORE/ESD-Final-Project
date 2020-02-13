#ifndef _REMOTE_FUNCTIONS_H_
#define _REMOTE_FUNCTIONS_H_

/*****************************************************************************​​*​​
​​*HARSH RATHORE​​
*UNIVERSITY OF COLORADO BOULDER
*FALL 2019
*EMBEDDED SYSTEMS DESIGN
​​******************************************************************************/
/// **​​*​​@file​ ​name Remote_functions.h
/// *​​@Ir remmote control
/// **this header file contains all the intructions,variables and commands of nec based ir remote
​​/// *​​*​​@author​​ Harsh Rathore
​​/// @references-https://exploreembedded.com/wiki/NEC_IR_Remote_Control_Interface_with_8051
​​/// https://www.snrelectronicsblog.com/8051/8051-based-remote-for-home-appliance/
​​​/// *​​@ date 1st Dec 2019
​​​​/// *​​@version​​1.0​
​​/// */


/**​​
*​​@brief​​ the external interrupt handler function which triggers depending on the external hardware interrupt
.​​
*​​*​​@param​​ptr​​ none

*​​*​​@return​​ void.​​
*/
void externalIntr0_ISR()  __interrupt 0;
/**​​
*​​@brief​​ the remote init function initializing remote timer interrupt values

*​​*​​@param​​ptr​​ void

*​​*​​@return​​ void.​​
*/
void IR_RemoteInit(void);                        ///prototype declaration of remote functions
/**​​
*​​@brief​​ the time r0 interrupt for ms count which runs according to timer value loaded

*​​*​​@param​​ none

*​​*​​@return​​ void.​​
*/

void timer0_isr() __interrupt 1;

#endif
