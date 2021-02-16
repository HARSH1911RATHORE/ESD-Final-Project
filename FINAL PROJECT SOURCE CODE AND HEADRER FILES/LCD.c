#include "LCD.h"

#include <stdint.h>


/*****************************************************************************​​*​​
​​*HARSH RATHORE​​
*UNIVERSITY OF COLORADO BOULDER
*FALL 2019
*EMBEDDED SYSTEMS DESIGN
​​******************************************************************************/
///**​​*​​@file​ ​name LCD.c
///*​​@LCD commands usage
///**this header file contains all the timer calculations usage
​​///*​​*​​@author​​ Harsh Rathore
​///*​​@ date 21st nov 2019
​​///*​​@version​​1.0​



volatile char ch=0;

volatile int8_t row2=0;                         ///rows and column value defined as global so that value of the teh string gets printed even when timer is running
/// hence defined its values inside the timer function
volatile int8_t column2=0;
volatile char *string=0;                     ///input string which will be taken from the user is defined as global and defined inside timer function so that
///it gets printed

volatile int8_t address1=0;                                 ///defining the address for input from the user to write a particular character

volatile char input=0;                         ///input of ui made to make the user take charge of lcd display
volatile uint8_t count=0;
volatile uint8_t row=0;
volatile uint8_t column=0;

void delay(uint32_t n)
{
    int i,j;                                    ///delay function called between different lcd instruction commands

    for(i=0; i<n; i++)
    {
        for(j=0; j<1275; j++)
        {
            ;
        }
    }
}
void lcd_instruction_write(uint16_t write)
{
    instruction_reg_write=write;
    lcdbusywait();
}
void lcdbusywait()
{
    while(busy_flag_read&0x80);                               ///checking for the busy flag, if it is 1
}

void lcdinit(void)
{
    delay(15);                                    ///15ms delay
    instruction_reg_write = unlock;

    delay(4);                                    ///4.1ms delay
    instruction_reg_write = unlock;

    delay(1);                                   ///100uS delay
    instruction_reg_write = unlock;

    lcdbusywait();                                  /// wait for busy flag to clear

    instruction_reg_write = Function_set;

    lcdbusywait();                                  /// wait for busy flag to clear

    instruction_reg_write = display_off;

    lcdbusywait();                                    /// wait for busy flag to clear

    instruction_reg_write = display_on;

    lcdbusywait();                                  /// wait for busy flag to clear

    instruction_reg_write = entrymode_set;

    lcdbusywait();                                  /// wait for busy flag to clear

    instruction_reg_write = clearscreen;
}

void lcd_clear_screen()
{
    instruction_reg_write = clearscreen;         ///function to clear the lcd screen
}
void lcdgotoaddr(uint8_t addr)
{
    instruction_reg_write = addr;               ///function to write to the lcd ddram address

}
void lcdgotoxy(uint8_t rows, uint8_t columns)
{
    row=rows;
    column=columns;
    int address=0;                           ///function to specify the required location to go to specified by the row and column
    int a=0x80;
    int b=0xC0;
    int c=0x90;
    int d=0xD0;

    if (rows==0)
        address=a+columns;                  ///increment the value of the address of each row and column address as specified as row and column values
    if (rows==1)                            ///for the address
        address=b+columns;
    if (rows==2)
        address=c+columns;
    if (rows==3)
        address=d+columns;
    lcdgotoaddr(address);                ///using lcd go to address to go to a required location
}

void lcdputch(char cc)
{
    data_register_write=cc;            ///putting character on the lcd display at the desired location
    lcdbusywait();
    delay(10);

}
void lcdputstr(char *string)
{
    count=column;
    while(*string!='\0' && (*string!='\n' && *string!='\r'))             ///till string ends keep putting characters on lcd
    {
        lcdputch(*string++);            ///send characters one by one

        count++;
        if (count==16)                ///check the count of the characters
        {
            row=row+1;
            count=0;
            if(row==4)                ///if column value is 16 goto the next line and to the next row
            {
                lcdgotoxy(0,0);
                row=0;
            }

            else
            {
                lcdgotoxy(row,0);    ///if reached the last column and last row, jump to the first location
            }
        }
    }
}

