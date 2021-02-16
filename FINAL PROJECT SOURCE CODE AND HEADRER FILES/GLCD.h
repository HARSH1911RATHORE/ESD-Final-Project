#ifndef _GLCD_H_
#define _GLCD_H_

/*****************************************************************************​​*​​
​​*HARSH RATHORE​​
*UNIVERSITY OF COLORADO BOULDER
*FALL 2019
*EMBEDDED SYSTEMS DESIGN
​​******************************************************************************/
/// **​​*​​@file​ ​name GLCD.h
/// *​​@Graphical lcd
​​/// **this header file contains all the intructions,variables and commands of nokia 5110 graphical lcd
​​​​/// *​​*​​@author​​ Harsh Rathore
​​/// @reference-http://www.circuitstoday.com/nokia-graphic-lcd-display-8051
​​​/// *​​@ date 1st Dec 2019
​​​​/// *​​@version​​1.0​
​​/// */

#include<at89c51ed2.h>          ///include library functions needed for lcd display and 8051
#include <mcs51/8051.h>
#include <stdint.h>
#define CLK P2_1
#define data_in P2_2
#define Data_command P2_3
#define chip_enable P2_4
#define RST P2_5


extern const unsigned char LookUpTable [][5];            ///lookup table to print characters

/**​​
*​​@brief​​ the write to pixel through spi protocol
*​​*​​Given​​ an ​​unsigned int write to write the pixel value

*​​*​​@param​​ write

*​​*​​@return​​ void.​​
*/

void Write(unsigned int write);
/**​​
*​​@brief​​ the data value to be written
*​​*​​Given​​ an unsigned char value which is send to the ddram address

*​​*​​@param​​p char x

*​​*​​@return​​ void.​​
*/

void Data(unsigned char x);
/**​​
*​​@brief​​ the command instruction to be sent
*​​*​​Given​​ a ​n unsigned char
​
*​​*​​@param​​ x set the command in hex, mostly used at start to initialise the lcd

*​​*​​@return​​ void.​​
*/

void Command(unsigned char x);
/**​​
*​​@brief​​ the function to set the pixel address
*​​*​​Given​​ a ​n unsigned char x
​​*​​Given​​ a ​n unsigned char y
*​​*​​@param​​ x to set x axis
*​​@param​​ y to set y axis
*​​*​​@return​​ void.​​
*/

void setPixel(unsigned char x, unsigned char y);         ///prototype declaration of glcd functions
/**​​
*​​@brief​​ the lcd clear function
*​​*​​Given​​ none


*​​@param​​ void
*​​*​​@return​​ void.​​
*/

void allClear(void);
/**​​
*​​@brief​​ the function is used to initialize the lcd
*​​*​​Given​​ a void value

*​​@param​​ value
*​​*​​@return​​ void.​​
*/

void Initialize_LCD(void);

/**​​
*​​@brief​​ the set the pixel position
*​​*​​Given​​ a ​​char row which is the x axis
​​*​​given a char value col which is y axis
*​​*​​@param​​p char row value
*​​@param​​ ​​ char col value
*​​*​​@return​​ void.​​
*/

void setCursor(unsigned char row, unsigned char col);

/**​​
*​​@ brief​​ the function to print character on glcd
*​​*​​Given​​ a ​​unsigned char to variable
*​​*​​@param​​ value of data item to be displayed
*​​*​​@return​​ void.​​
*/

void charDisp(unsigned char a);

/**​​
*​​@brief​​ the function to print strings on glcd
*​​*​​Given​​ a ​​char pointer to a variable p​​
*​​*​​@param​​ pointer to a data iterm
*​​*​​@return​​ void.​​
*/
void stringDisp(unsigned char *p);

#endif
