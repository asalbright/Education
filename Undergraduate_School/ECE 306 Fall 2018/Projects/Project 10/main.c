//------------------------------------------------------------------------------
//
//  Description: This file contains the Main Routine - "While" Operating System
//
//
//  Jim Carlson
//  Jan 2018
//  Built with IAR Embedded Workbench Version: V4.10A/W32 (7.11.2)

#include  "msp430.h"
#include  "functions.h"
#include  "macros.h"
#include <string.h>
//------------------------------------------------------------------------------
// Global Variables
volatile char slow_input_down;
extern char display_line[disp_line_4][disp_line_11];
extern char *display[disp_4];
unsigned char display_mode;
extern volatile unsigned char display_changed;
extern volatile unsigned char update_display;
extern volatile unsigned int update_display_count;
extern volatile unsigned int Time_Sequence;
extern volatile char one_time;
unsigned int test_value;
char pwm_state;
char chosen_direction;
char change;

//ADDED
extern unsigned char Button_Pressed;
extern volatile unsigned int ADC_Thumb;
extern volatile unsigned int ADC_Right_Detector;
extern volatile unsigned int ADC_Left_Detector;
extern unsigned char Baud_Rate;
extern unsigned char Transmit_Active;
extern unsigned char Operation;



//function declarations
void display_ADC_Values(volatile unsigned int, volatile unsigned int, volatile unsigned int);
void translate_commands(void);
//------------------------------------------------------------------------------
void main(void){
//------------------------------------------------------------------------------
// Main Program
// This is the main routine for the program. Execution of code starts here.
// The operating system is Back Ground Fore Ground.
//
//------------------------------------------------------------------------------
// Disable the GPIO power-on default high-impedance mode to activate
// previously configured port settings
  PM5CTL0 &= ~LOCKLPM5;
  Init_Ports();                        // Initialize Ports
  Init_Clocks();                       // Initialize Clock System
  Init_Conditions();                   // Initialize Variables and Initial Conditions
  Init_ADC();
  Init_Serial_UCA3(Baud_Rate);
  Init_Serial_UCA0();
  Init_Timers();                       // Initialize Timers
  Init_LCD();                          // Initialize LCD
// Place the contents of what you want on the display, in between the quotes
// Limited to 10 characters per line
//

  strcpy(display_line[disp_line_0], "   NCSU   ");
  update_string(display_line[disp_line_0], disp_0);
  strcpy(display_line[disp_line_1], " WOLFPACK ");
  update_string(display_line[disp_line_1], disp_1);
  strcpy(display_line[disp_line_2], "  ECE306  ");
  update_string(display_line[disp_line_3], disp_3);
  enable_display_update();
  Display_Update(CONST_ZERO,CONST_ZERO,CONST_ZERO,CONST_ZERO);
  TA0CCTL2 &= ~CCIE;    //disable Timer
//------------------------------------------------------------------------------
// Begining of the "While" Operating System
//------------------------------------------------------------------------------
  while(ALWAYS) {                      // Can the Operating system run
 
    Display_Process();
    
    display_ADC_Values(ADC_Thumb, ADC_Right_Detector, ADC_Left_Detector);
    
    switch(Operation){
    case AUTO_MODE:
    case FIND_THE_LINE:
    case ALIGN_TO_LINE:
    case FOLLOW_THE_LINE:
    case ALIGN_PERPED_LINE:
    case DRIVE_FORWARD:
      Switches_Process();
      break;
    case IOT_MODE:
      switch(Button_Pressed){
      case BUTTON_1:
      case BUTTON_2:
        Switches_Process();
      default:
        break;
      }
      translate_commands();
      break;
    default:
      break;
    }
  }
}
//------------------------------------------------------------------------------