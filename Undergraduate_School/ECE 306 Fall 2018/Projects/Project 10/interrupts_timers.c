//Andrew Albright
//ECE 306
//interrupts_timers.c

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

extern unsigned char Button_Debouncing;
extern unsigned int Timer_A2_Time;
extern unsigned char Operation;
extern unsigned char Timer_A2_Running;
extern unsigned int Run_Time;
extern unsigned char Baud_Operation;
extern unsigned char Command_Recieved;


//------------------------------------------------------------------------------
unsigned char Button_Pressed = RESET;
char Timer_A0_Interupted = RESET;
volatile unsigned int Timer_A1_Interrupted = RESET;
volatile unsigned int Timer_A2_Interrupted = RESET;
unsigned int Display_Timer = RESET;
unsigned char Transmit_Active = OFF;
unsigned char Activate_IOT = OFF;

#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer0_A0_ISR(void){
  //----------------------------------------------------------------------------
  // TimerA0 0 Interrupt handler
  //----------------------------------------------------------------------------
//to blink the leds
  if(Time_Sequence >= RESET_TIME_SEQUENCE) Time_Sequence = RESET;
  else{
    Time_Sequence++;                    
    one_time = ALWAYS;
  }
//to keep the display updating
  if(!(Timer_A0_Interupted % A0_2TENTH_SECOND)){ 
    update_display = ALWAYS;
    display_changed = ALWAYS;
  }
//for the display timer Project 07 (half Second)
  if(!(Timer_A0_Interupted % TENTH_SECOND)){ 
    if(Operation != FINISHED) Display_Timer++;
  }
//for IOT Init reset and power save
  if(Timer_A0_Interupted >= A0_1_SECOND){
    switch(Activate_IOT){
    case OFF:
      P1OUT &= ~RED_LED;           
      P1OUT &= ~GRN_LED;
      P5OUT &= ~LCD_BACKLITE;     //change backlite
      P3OUT |= IOT_RESET;
      P8OUT &= ~IR_LED;
      Activate_IOT = ON;
      break;
    case ON:
      break;
    default: break;
    }
    Run_Time ++;
    Timer_A0_Interupted = RESET;
  }  
//increment 20ms time count
  Timer_A0_Interupted++;        
  
  TA0CCR0 += TA0CCR0_INTERVAL; // Add Offset to TACCR0
  //----------------------------------------------------------------------------
}

#pragma vector = TIMER0_A1_VECTOR
__interrupt void TIMER0_A1_ISR(void){
  //----------------------------------------------------------------------------
  // TimerA0 1-2, Overflow Interrupt Vector (TAIV) handler
  //----------------------------------------------------------------------------
  switch(__even_in_range(TA0IV,CONST_FOURTEEN)){
  case NONE: break; // No interrupt

  case CCR1_INTERRUPT: // CCR1 not used
//Based on Button_Debouncing
    switch(Button_Debouncing){
    case BUTTON_1:
        P5IE &= ~BUTTON1;       //disable button1 interrupted
        P5IE &= ~BUTTON2;       //diable button2 interrupted       
//bounce time passed? Re-enable button1 interrupt
      if(Timer_A1_Interrupted >= CONST_FIVE){
        P5IFG &= ~BUTTON1;      //clear button1 flags
        P5IE |= BUTTON1;        //re-enable button1 interrupts
        P5IFG &= ~BUTTON2;      //clear button2 flags (clears the button que)
        P5IE |= BUTTON2;        //re-enable button2 interrupts
        TA0CCTL0 |= CCIE;       //re-enable A1 CCR0

        Button_Debouncing = RESET;      //clear debouncing time (not necessary)
        Button_Pressed = BUTTON_1;      //for MAIN
        
        TA0CCTL1 &= ~CCIE;      //disable A1 CCR1
      }
      Timer_A1_Interrupted++;   //increment 100ms time count
      break;
      
    case BUTTON_2:
      P5IE &= ~BUTTON2;         //disable button2 interrupt
      P5IE &= ~BUTTON1;
//bounce time passed? Re-enable button1 interrupt
      if(Timer_A1_Interrupted >= CONST_FIVE){
        P5IFG &= ~BUTTON2;
        P5IE |= BUTTON2;
        P5IFG &= ~BUTTON1;
        P5IE |= BUTTON1;
        TA0CCTL0 |= CCIE;

        Button_Debouncing = RESET;
        Button_Pressed = BUTTON_2; //for MAIN
        
        TA0CCTL1 &= ~CCIE;
      }
      Timer_A1_Interrupted++;
      break;
      
    default:
      break;
    }
    
    TA0CCR1 += TA0CCR1_INTERVAL; // Add Offset to TACCR1
  break;

  case CCR2_INTERRUPT: // CCR2 not used
//Based on Button_Pressed
    switch(Command_Recieved){
    case RESET:
      TA0CCTL2 &= ~CCIE;
      break;
    case RUN_COMMAND:
      switch(Timer_A2_Running){
      case ON:
      case RUNNING:
        if(Timer_A2_Interrupted >= Timer_A2_Time){
          Timer_A2_Running = STOP;
          Timer_A2_Interrupted = RESET;
          Timer_A2_Time = RESET;
          TA0CCTL2 &= ~CCIE;
        }
        else Timer_A2_Interrupted++;
        break;
      case OFF:
      default: break;
      }
      break;
    default:
      break;
    }
    
    TA0CCR2 += TA0CCR2_INTERVAL; // Add Offset to TACCR2
    break;

  case OVERFLOW_INTERRUPT: // overflow
  //...... Add What you need happen in the interrupt ......
  break;

  default: break;
  }
  //----------------------------------------------------------------------------
}