
#ifndef _KEYPAD_H_
#define _KEYPAD_H_

/*****************************************************************************​​*​​
​​*HARSH RATHORE​​
*UNIVERSITY OF COLORADO BOULDER
*FALL 2019
*EMBEDDED SYSTEMS DESIGN
​​******************************************************************************/
/// **​​*​​@file​ ​name Keypad.h
/// *​​@KEYPAD 4*3
​​/// **this header file contains all the intructions,variables and commands of 4*3 keypad
​​​​/// *​​*​​@author​​ Harsh Rathore
​​/// @reference-https://circuitdigest.com/microcontroller-projects/keypad-interfacing-with-8051-microcontroller
​​​/// *​​@ date 1st Dec 2019
​​​​/// *​​@version​​1.0​
​​/// */


/**​​
*​​@brief​​ the row finder function for a given column
*​​*​​Given​​ none

*​​*​​@param​​ none

*​​*​​@return​​ void.​​
*/
void row_finder1();            ///prototype declaration of keypad functions
/**​​
*​​@brief​​ the row finder function for a given column
*​​*​​Given​​ none

*​​*​​@param​​p none

*​​*​​@return​​ void.​​
*/
void row_finder2();
/**​​
*​​@brief​​ the row finder function for a given column
*​​*​​Given​​ none

*​​*​​@param​​p noneem​​

*​​*​​@return​​ void.​​
*/
void row_finder3();

extern unsigned char seven_seg[];    ///hex values for displaying 0 to 9
extern unsigned char seven_seg_alp[];

#endif
