#ifndef _LCD_H_
#define _LCD_H_

/*****************************************************************************​​*​​
​​*HARSH RATHORE​​
*UNIVERSITY OF COLORADO BOULDER
*FALL 2019
*EMBEDDED SYSTEMS DESIGN
​​******************************************************************************/
/// **​​*​​@file​ ​name LCD.h
​​/// *​​@LCD commands
​​/// **this header file contains all the lcd command and display instructions
​​​​/// *​​*​​@author​​ Harsh Rathore
​​​/// *​​@ date 21st nov 2019
​​​​/// *​​@version​​1.0​

​

#include <stdlib.h>
#include<at89c51ed2.h>          ///include library functions needed for lcd display and 8051
#include <mcs51/8051.h>
#include <stdint.h>
#define unlock (0x30)
#define Function_set (0x38)      ///macro defined for different sets of lcd commands
#define display_off (0x08)
#define display_on (0x0E)
#define entrymode_set (0x06)
#define clearscreen (0x01)

__xdata __at (0xF000) volatile unsigned char instruction_reg_write;  ///Instruction Register Write address

__xdata __at (0xF100) volatile unsigned char data_register_write;   ///Data register write address

__xdata __at (0xF200) volatile unsigned char busy_flag_read;        ///  Busy Flag Read address

__xdata __at (0xF300) volatile unsigned char data_register_read;   ///Data register read address

/**​​
*​​@brief​​ the lcd put string function to print the string
*​​*​​Given​​ a ​​pointer​​ string

*​​*​​@param​​ptr​​ string value to be displayed

*​​*​​@return​​ void.​​
*/
void lcdputstr(char *string);
/**​​
*​​@brief​​ the character to be displayed
*​​*​​Given​​ a char variable
​

*​​@param​​ value​​ to​​ write ​​to ​​the lcd
*​​*​​@return​​ void.​​
*/
void lcdputch(char cc);
/**​​
*​​@brief​​ the rows and columns the cursor needs to be set to
*​​*​​Given​​ a ​​uint8_t value of row
​​**​​*​​Given​​ a ​​uint8_t value of col
*​​*​​@param sets row
*​​@param​​ sets column
*​​*​​@return​​ void.​​
*/
void lcdgotoxy(uint8_t rows, uint8_t columns);
/**​​
*​​@brief​​ the address of ddram
*​​*​​Given​​ a ​​uint8_t value of address

*​​@param ​​value​​ of the address the character should be displayed at
*​​*​​@return​​ void.​​
*/
void lcdgotoaddr(uint8_t addr);                            ///prototype declaration of lcd functions
/**​​
*​​@brief​​ to clear the screen
*​​*​​Given​​ none

*​​*​​@param​​ none

*​​*​​@return​​ void.​​
*/

void lcd_clear_screen();
/**​​
*​​@brief​​ the lcd init function to initialize the lcd correctly
*​​*​​Given​​ a ​​void

*​​@param​​ void
*​​*​​@return​​ void.​​
*/

void lcdinit(void);

/**​​
*​​@brief​​ the lcd busy wait function to wait for command to process

*​​*​​Given​​ none

*​​@param​​ void
*​​*​​@return​​ void.​​
*/

void lcdbusywait();

/**​​
*​​@brief​​ the delay of 1 ms
*​​*​​Given​​ a uint32_t value

*​​*​​@param​​ provide delay in multiple of 1ms

*​​*​​@return​​ void.​​
*/

void delay(uint32_t n);

/**​​
*​​@brief​​ the instruction commands for lcd
*​​*​​Given​​ a ​​uint16_t write

*​​*​​@param​​ write instruction commands

*​​*​​@return​​ void.​​
*/

void lcd_instruction_write(uint16_t write);

#endif
