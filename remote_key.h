
#ifndef _REMOTE_KEY_H
#define _REMOTE_KEY_H
/*****************************************************************************​​*​​
​​*HARSH RATHORE​​
*UNIVERSITY OF COLORADO BOULDER
*FALL 2019
*EMBEDDED SYSTEMS DESIGN
​​******************************************************************************/
/// **​​*​​@file​ ​name Remote_key.h
​​/// *​​@Remote_key
​​///​​ **this header file contains all the intructions,variables and commands of Remote_key
​​​​/// *​​*​​@author​​ Harsh Rathore
​​/// @reference-https://exploreembedded.com/wiki/NEC_IR_Remote_Control_Interface_with_8051
​​​/// *​​@ date 1st Dec 2019
​​​​/// *​​@version​​1.0​
​​/// */

#define  power 0x1E3E817
#define power1 0x3E3E817
#define power_long_press
#define back  0x1E36699‬
#define back1  0x3E36699
#define home  0x3E3C03F
#define home1  0x1E3C03F
#define up_arrow  0x3E39867
#define up_arrow1  0x1E39867
#define right_arrow  0x3E3B44B
#define right_arrow1  0x1E3B44B
#define down_arrow   0x3E3CC33
#define down_arrow1   0x1E3CC33                 ///values of bitpatterns for the different keys pressed
#define  left_arrow 0x3E37887
#define  left_arrow1 0x1E37887
#define  ok_key  0x3E354AB
#define  ok_key1  0x1E354AB
#define  replay  0x3E31EE1
#define  replay1  0x1E31EE1
#define   night_mode_key  0x3E346B9‬
#define   night_mode_key1  0x1E346B9‬
#define  brightness_key   0x3E38679
#define  brightness_key1   0x1E38679
#define  rewind_key  0x3E32CD3
#define  rewind_key1  0x1E32CD3
#define  fast_forward_key   0x3E332CD
#define  fast_forward_key1   0x3E332CD
#define  advance_key  0x3E3AA55
#define  advance_key1  0x1E3AA55
#define  netflix_key 0x3E34AB5
#define  netflix_key1 0x1E34AB5
#define  espn_key 0x3E34EB1
#define  espn_key1 0x1E34EB1
#define  hulu_key 0x3E3B24D
#define  hulu_key1 0x1E3B24D
#define  roku_tv 0x3E37689‬
#define  roku_tv1 0x1E37689‬
#define pow 0xE817

#endif
