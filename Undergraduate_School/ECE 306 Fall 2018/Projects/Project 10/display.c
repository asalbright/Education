//Andrew Albright
//ECE 306
//display.c

#include  "msp430.h"
#include  "functions.h"
#include  "macros.h"
#include <string.h>
extern volatile unsigned char update_display;
extern volatile unsigned char display_changed;
extern char display_line[disp_line_4][disp_column_11];
extern unsigned int Display_Timer;
extern unsigned char Operation;
extern unsigned int Black_Line;
extern unsigned int White_Line;
extern unsigned char Baud_Rate;
extern volatile char USB_Char_Rx[];
extern volatile char USB_Char_Tx[];
extern char Controlled_Message[];
extern char IOT_Transmit[CONST_TWO][SMALL_RING_SIZE];
extern char IP_Address[];
char* IP_Index = IP_Address;
extern unsigned char Baud_Operation;
extern unsigned int Run_Time;
extern unsigned char Transmit_Active;



unsigned char Display = IOT_MENU;
unsigned int Scroll = RESET;
char adc_char[disp_column_11] = {RESET};

//------------------------------------------------------------------------------
//display_ADC_Values functions purpose is to set the display of the lcd on the 
//car. Function takes values from the thumb wheel and IR detectors and returns 
//nothing.
//------------------------------------------------------------------------------
void display_ADC_Values(volatile unsigned int Thumb, volatile unsigned int Right_Detector, volatile unsigned int Left_Detector){ 
  switch(Display){
//MAIN MENU
  case MAIN_MENU:
    Scroll = Thumb / TWO_PAGE_MENU;
      strcpy(display_line[disp_line_0], "MAIN MENU:");
      strcpy(display_line[disp_line_1], "IOT_Menu  ");
      strcpy(display_line[disp_line_2], "IR_Menu   ");
      strcpy(display_line[disp_line_3], "PROJECT 10");
             switch(Scroll){
               case CONST_TWO:
               case CONST_ONE:
                 display_line[disp_line_1][disp_column_9] = ARROW;
                 break;
               case CONST_ZERO:
                 display_line[disp_line_2][disp_column_9] = ARROW;
                 break;
               default: break;
             }
    break;
//IR MENU
    case IR_MENU:         
      strcpy(display_line[disp_line_0], "IR Calibr8");

      HEXtoBCD(Black_Line);
      strcpy(display_line[disp_line_1], "BLK:  ");
      strncat(display_line[disp_line_1], adc_char, CONST_FOUR);
      
      HEXtoBCD(White_Line);
      strcpy(display_line[disp_line_2], "WHT:  ");
      strncat(display_line[disp_line_2], adc_char, CONST_FOUR);
      
      HEXtoBCD(Line_Found);
      strcpy(display_line[disp_line_3], "Avg:  ");
      strncat(display_line[disp_line_3], adc_char, CONST_FOUR);
      
      break;
//IOT MENU
    case IOT_MENU:
      switch(Baud_Operation){
       case WAITING:
        strcpy(display_line[disp_line_0], "   IOT    ");
        strcpy(display_line[disp_line_1], "Connecting");
        break;
      case IOT_CONNECTED:
        strcpy(display_line[disp_line_0], "IP Address");
        switch(Run_Time){
        case CONST_ZERO:
          strncpy(display_line[disp_line_1], IP_Index, CONST_TEN);
          break;
        case CONST_ONE:
          if(*(IP_Index + CONST_TEN) == CHAR_NULL) IP_Index = IP_Address;
          else IP_Index++;
        default:
          Run_Time = RESET;
          break;
        }
        break;
        
      default: break;
      }
      
      switch(Operation){
      case IOT_MODE:
        strcpy(display_line[disp_line_2], "BAUD Rate:");
        switch(Baud_Rate){
        case FAST_BAUD:
          strcpy(display_line[disp_line_3], " 460,800  ");
          break;
        case SLOW_BAUD:
          strcpy(display_line[disp_line_3], " 115,200  ");
          break;
        default: 
          break;
        }
        break;
      case AUTO_MODE:
        strcpy(display_line[disp_line_2], "Operation:");
        strcpy(display_line[disp_line_3], "IRs Active");
        break;
      case FIND_THE_LINE:
        strcpy(display_line[disp_line_2], "Operation:");
        strcpy(display_line[disp_line_3], "Find Line ");
        break;
      case ALIGN_TO_LINE:
        strcpy(display_line[disp_line_2], "Operation:");
        strcpy(display_line[disp_line_3], "Align Line");
        break;
      case FOLLOW_THE_LINE:
        strcpy(display_line[disp_line_2], "Operation:");
        strcpy(display_line[disp_line_3], "Folow Line");
        break;
      case ALIGN_PERPED_LINE:
        strcpy(display_line[disp_line_2], "Operation:");
        strcpy(display_line[disp_line_3], "Align2Cent");
        break;
      case DRIVE_FORWARD:
        strcpy(display_line[disp_line_2], "Operation:");
        strcpy(display_line[disp_line_3], "Drive2Cent");
        break;
        
      default: break;
      }
      
      break;
    default: break;
  }
}

// Hex to BCD Conversion
// HextoBCD function converts a Hex number to a BCD for display on an LCD or 
//monitor. Function Takes in a hex_value and returns nothing.
void HEXtoBCD(int hex_value){
  int value = RESET;
  adc_char[disp_column_0] = CHAR_ZERO;
  while (hex_value > Less_Than_Thousand){
    hex_value = hex_value - CONST_THOUSAND;
    value = value + CONST_ONE;
    adc_char[disp_column_0] = Char_Hex_Offset + value;
  }
  value = RESET;
  adc_char[disp_column_1] = CHAR_ZERO;
  while (hex_value > Less_Than_Hundred){
    hex_value = hex_value - CONST_HUNDRED;
    value = value + CONST_ONE;
    adc_char[disp_column_1] = Char_Hex_Offset + value;
  }
  value = RESET;
  adc_char[disp_column_2] = CHAR_ZERO;
  while (hex_value > Less_Than_Ten){
    hex_value = hex_value - CONST_TEN;
    value = value + CONST_ONE;
    adc_char[disp_column_2] = Char_Hex_Offset + value;
  }
  adc_char[disp_column_3] = Char_Hex_Offset + hex_value;
}