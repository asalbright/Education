//Andrew Albright
//ECE 306
//timers.c

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
extern unsigned int test_value;
extern char pwm_state;
extern char chosen_direction;
extern char change;
//------------------------------------------------------------------------------
//timers.c Globals
volatile unsigned int Time_Sequence = RESET;
volatile char one_time;

void Init_Timers(void){
  Init_Timer_A0();
  Init_Timer_B0();
}

// Timer A0 initialization sets up both A0_0, A0_1-A0_2 and overflow
void Init_Timer_A0(void){
    TA0CTL = TASSEL__SMCLK; // SMCLK source
    TA0CTL |= TACLR; // Resets TA0R, clock divider, count direction
    TA0CTL |= MC__CONTINOUS; // Continuous up
    TA0CTL |= ID__2; // Divide clock by 2
    TA0EX0 = TAIDEX__8; // Divide clock by an additional 8
    
    TA0CCR0 = TA0CCR0_INTERVAL; // CCR0
    TA0CCTL0 |= CCIE; // CCR0 enable interrupt
    TA0CCR1 = TA0CCR1_INTERVAL; // CCR1
    TA0CCTL1 &= ~CCIE; // CCR1 enable interrupt
    TA0CCR2 = TA0CCR2_INTERVAL; // CCR2
    TA0CCTL2 &= ~CCIE; // CCR2 enable interrupt
   
    TA0CTL &= ~TAIE; // Disable Overflow Interrupt
    TA0CTL &= ~TAIFG; // Clear Overflow Interrupt flag
  }

void Init_Timer_B0(void) {
  //------------------------------------------------------------------------------
  // SMCLK source, up count mode, PWM Right Side
  // TB0.3 P3.4 L_REVERSE TB0.1 P3.6 R_REVERSE
  // TB0.4 P3.5 L_FORWARD TB0.2 P3.7 R_FORWARD
  //------------------------------------------------------------------------------
  TB0CTL = TBSSEL__SMCLK; // SMCLK
  TB0CTL |= MC__UP; // Up Mode
  TB0CTL |= TBCLR; // Clear TAR
  TB0CCR0 = WHEEL_PERIOD; // PWM Period
  TB0CCTL3 = OUTMOD_7; // CCR1 reset/set
  LEFT_REVERSE_SPEED = WHEEL_OFF; // P3.4 Left Reverse PWM duty cycle
  TB0CCTL4 = OUTMOD_7; // CCR2 reset/set
  LEFT_FORWARD_SPEED = WHEEL_OFF; // P3.5 Left Forward PWM duty cycle
  TB0CCTL5 = OUTMOD_7; // CCR1 reset/set
  RIGHT_REVERSE_SPEED = WHEEL_OFF; // P3.6 Right Reverse PWM duty cycle
  TB0CCTL6 = OUTMOD_7; // CCR2 reset/set
  RIGHT_FORWARD_SPEED = WHEEL_OFF; // P3.7 Right Forward PWM duty cycle
  //------------------------------------------------------------------------------
}