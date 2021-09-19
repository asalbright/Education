//Andrew Albright
//ECE 306
//switches.c

#include  "msp430.h"
#include  "functions.h"
#include  "macros.h"
#include <string.h>
//------------------------------------------------------------------------------
// Global Variables
extern volatile char slow_input_down;
extern char display_line[disp_line_4][disp_line_11];
extern char *display[disp_4];
extern unsigned char display_mode;
extern volatile unsigned char display_changed;
extern volatile unsigned char update_display;
extern volatile unsigned int update_display_count;
extern volatile unsigned int Time_Sequence;
extern volatile char one_time;
extern unsigned int test_value;
extern char pwm_state;
extern char chosen_direction;
extern char change;
//ADDED
extern unsigned char Button_Pressed;
extern volatile unsigned int ADC_Thumb;
extern volatile unsigned int ADC_Right_Detector;
extern volatile unsigned int ADC_Left_Detector;
extern volatile unsigned int Timer_A2_Interrupted;
extern unsigned int Display_Timer;
extern unsigned char Display;

extern unsigned char Transmit_Active;
extern unsigned int Timer_A2_Time;
extern unsigned char Timer_A2_Running;
extern unsigned int Black_Line;
extern unsigned int White_Line;
extern unsigned char Operation;
extern unsigned int Run_Time;
extern unsigned int Scroll;
extern unsigned int Right_Speed;
extern unsigned int Left_Speed;

unsigned char Calibrate_IRs = RESET;
unsigned char Set_Baud = SLOW_BAUD;
unsigned char Baud_Rate = SLOW_BAUD;
unsigned char Baud_Operation = WAITING;
unsigned char Surface = FIND_WHITE;

//------------------------------------------------------------------------------
//Switches_Process() takes in nothing and returns nothing. It purpose is to 
//control what happends after a button is debounced as well as control the 
//operations of the cars follow the line movements
//------------------------------------------------------------------------------

void Switches_Process(void){
//BUTTON 1 PRESS
  if(Button_Pressed == BUTTON_1){
    Display = MAIN_MENU;
    Button_Pressed = RESET;
  }
//BUTTON 2 PRESS
  else if(Button_Pressed == BUTTON_2){
//Setting the IR Line values
    switch(Display){
    case MAIN_MENU:
      switch(Scroll){
      case CONST_TWO:
      case CONST_ONE:
        Display = IOT_MENU;
        break; 
      case CONST_ZERO:
        Display = IR_MENU;
        break;
      default: break;
      }
      break;
    case IR_MENU:
      switch(Calibrate_IRs){
      case CONST_ZERO:
        Black_Line = (ADC_Right_Detector + ADC_Left_Detector) / CONST_TWO;
        Calibrate_IRs++;
        P8OUT &= ~IR_LED;
        break;
      case CONST_ONE:
        White_Line = (ADC_Right_Detector + ADC_Left_Detector) / CONST_TWO;
        P8OUT &= ~IR_LED;
        Calibrate_IRs = RESET;
        break;
        
      default: break;
      }
      break;
    default: break;
    }
    Button_Pressed = RESET;
  }
  switch(Operation){
    case AUTO_MODE:
      switch(Timer_A2_Running){
      case OFF:
        P8OUT |= IR_LED;
        Timer_A2_OFF(A2_1_SECOND);
        break;
      case STOP:
        Operation = FIND_THE_LINE;
        Timer_A2_Running = OFF;
        break;
      default: break;
      }
      break;
    case FIND_THE_LINE://10
      Find_Line();
      break;
      
    case ALIGN_TO_LINE://15
      Align_Line();
      break;
      
    case FOLLOW_THE_LINE://20
      Follow_Line(A2_2_MIN);
      break;
    default: break;
  }
}

/*
LEFT_REVERSE_SPEED = WHEEL_OFF; // P3.4 Left Reverse PWM OFF
LEFT_REVERSE_SPEED = [DESIRED ON AMOUNT]; // P3.4 Left Reverse PWM on amount
LEFT_FORWARD_SPEED = WHEEL_OFF; // P3.5 Left Forward PWM OFF
LEFT_FORWARD_SPEED = [DESIRED ON AMOUNT]; // P3.5 Left Forward PWM on amount
RIGHT_REVERSE_SPEED = WHEEL_OFF; // P3.6 Right Reverse PWM OFF
RIGHT_REVERSE_SPEED = [DESIRED ON AMOUNT]; // P3.6 Right Reverse PWM on amount
RIGHT_FORWARD_SPEED = WHEEL_OFF; // P3.7 Right Forward PWM OFF
RIGHT_FORWARD_SPEED = [DESIRED ON AMOUNT]; // P3.7 Right Forward PWM on amount
*/

//------------------------------------------------------------------------------
//Find_Line functions purpose is to allow the car to find a determined color 
//depending on the set colors to look for. Function takes in nothing and returns
//nothing.
//------------------------------------------------------------------------------
void Find_Line(void){
  switch(Surface){
  case FIND_WHITE:
    if(ADC_Right_Detector < WHITE_LINE || ADC_Left_Detector < WHITE_LINE){
    Hault_Movement();
    Surface = FIND_BLACK;
  }
  else{
    RIGHT_FORWARD_SPEED = Right_Speed;
    LEFT_FORWARD_SPEED = Left_Speed;
  }
    break;
  case FIND_BLACK:
    if(ADC_Right_Detector > Line_Found || ADC_Left_Detector > Line_Found){
      Hault_Movement();
      Surface = FIND_WHITE;
      Operation = ALIGN_TO_LINE;
    }
    else{
      RIGHT_FORWARD_SPEED = Right_Speed;
      LEFT_FORWARD_SPEED = Left_Speed;
    }
    break;
  default: break;
  }
  
}

//------------------------------------------------------------------------------
//Follow_Line functions purpose is to allow the car to align to a determined 
//color //depending on the set colors to look for. Function takes in nothing and
//returns nothing.
//------------------------------------------------------------------------------
void Align_Line(void){
  switch(Surface){
  case FIND_WHITE:
    if(ADC_Right_Detector < WHITE_LINE && ADC_Left_Detector < WHITE_LINE){
    Hault_Movement();
    Surface = FIND_BLACK;
  }
    else{ 
      RIGHT_FORWARD_SPEED = Right_Speed;
      LEFT_FORWARD_SPEED = Left_Speed;
    }
    break;
  case FIND_BLACK:
    if(ADC_Right_Detector > Line_Found && ADC_Left_Detector < Line_Found){
      Hault_Movement();
      Operation = FOLLOW_THE_LINE;
    }
    else{ 
      RIGHT_REVERSE_SPEED = Right_Speed;
      LEFT_FORWARD_SPEED = Left_Speed;  
    }
    break;
  default: break;
  }
}

//------------------------------------------------------------------------------
//Find_Line functions purpose is to allow the car to follow a determined color 
//depending on the set colors to look for. Function takes in amount of time to 
//folllow the line and returns nothing.
//------------------------------------------------------------------------------
void Follow_Line(int Time){
  switch(Timer_A2_Running){
  case OFF:
    Timer_A2_OFF(Time);
  case RUNNING:
  case ON:
    if(ADC_Right_Detector < Line_Found){
      RIGHT_FORWARD_SPEED = Right_Speed;
      LEFT_FORWARD_SPEED = WHEEL_OFF;  
    }
    else if(ADC_Left_Detector > Line_Found){
      RIGHT_FORWARD_SPEED = WHEEL_OFF;
      LEFT_FORWARD_SPEED = Left_Speed;
    }
    else{
      RIGHT_FORWARD_SPEED = Right_Speed;
      LEFT_FORWARD_SPEED = Left_Speed;
    }
    break;
  case STOP:
     Hault_Movement();
     Timer_A2_Running = OFF;
     Operation = ALIGN_PERPED_LINE;
  default: break;
  }
}