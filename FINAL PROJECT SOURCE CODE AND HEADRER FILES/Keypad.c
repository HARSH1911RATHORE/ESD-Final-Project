#include "Keypad.h"
#include "GLCD.h"            ///libraries required for keypad
#include "Sevensegment.h"

#include <stdint.h>
#define  C2  P1_0            /// Connecting keypad to Port 1
#define  R1  P1_1
#define  C1  P3_5
#define  R4  P3_4
#define  C3  P1_4
#define  R3  P1_5
#define  R2  P1_6


extern volatile uint8_t keypad;

void row_finder1()            ///Function used for finding the row for column 1
{
    R1=R2=R3=R4=1;
    C1=C2=C3=0;

    if(R1==0)                ///if c1 are zero and r1 is zero then 1 is pressed
    {
        if(R1==0);
        keypad=1;
        P0=seven_seg[1];
        charDisp('1');
    }
    if(R2==0)              ///if c1 are zero and r2 is zero then 4 is pressed
    {
        if(R2==0);
        P0=seven_seg[4];
        charDisp('4');
    }

    if(R3==0)          ///if c1 are zero and r3 is zero then 7 is pressed
    {
        if(R3==0);
        P0=seven_seg[7];
        charDisp('7');
    }

    if(R4==0)         ///if c1 are zero and r4 is zero then * is pressed
    {
        if(R4==0);
        P0=seven_seg[0];
    }

}

void row_finder2() ///Function used for finding the row for column 2
{
    R1=R2=R3=R4=1;
    C1=C2=C3=0;

    if(R1==0)     ///if c2 is zero and r1 is zero then 2 is pressed
    {
        if(R1==0);
        keypad=2;
        P0=seven_seg[2];
    }
    if(R2==0)    ///if c2 is zero and r2 is zero then 5 is pressed
    {
        if(R2==0);
        P0=seven_seg[5];
    }
    if(R3==0)   ///if c2 is zero and r2 is zero then 8 is pressed
    {
        if(R3==0);
        P0=seven_seg[8];
    }

    if(R4==0)   ///if c2 is zero and r2 is zero then 0 is pressed
    {
        if(R4==0);
        P0=seven_seg[0];
    }
}

void row_finder3() ///Function used for finding the row for column 3
{
    R1=R2=R3=R4=1;
    C1=C2=C3=0;

    if(R1==0)  ///if c3 is zero and r1 is zero then 3 is pressed
    {
        if(R1==0);
        keypad=3;
        P0=seven_seg[3];
    }

    if(R2==0) ///if c3 is zero and r2 is zero then 6 is pressed
    {
        if(R2==0);
        P0=seven_seg[6];
    }

    if(R3==0) ///if c3 is zero and r3 is zero then 9 is pressed
    {
        if(R3==0);
        P0=seven_seg[9];
    }

    if(R4==0) ///if c3 is zero and r4 is zero then # is pressed
    {
        if(R4==0);
    }

}
