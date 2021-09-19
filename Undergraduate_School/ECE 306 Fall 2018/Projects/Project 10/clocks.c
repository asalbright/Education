//------------------------------------------------------------------------------
//
//  Description: This file contains the Clock Initialization
//
//  Jim Carlson
//  Jan 2016
//  Built with IAR Embedded Workbench Version: V7.3.1.3987 (6.40.1)

#include  "msp430.h"
#include  "macros.h"
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
//------------------------------------------------------------------------------

//MACROS========================================================================
#define FLLN_BITS          (0x03ffu)
#define FLLN_255           (0x00ffu)
#define CSLOCK             (0x01) // Any incorrect password locks registers

// Port J Pins
#define XINR                 (0x10) // XINR
#define XOUTR                (0x20) // XOUTR
#define CLEAR_REGISTER     (0X0000)

void Init_Clocks(void);

void Init_Clocks(void){
//------------------------------------------------------------------------------
// Clock Configurtaions
// This is the clock initialization for the program.
//
// Initial clock configuration, runs immediately after boot.
// Disables 1ms watchdog timer,
//      configure MCLK to 8MHz
//      configure SMCLK to 8MHz.
// Since the X1 oscillator is not currently connected,
// X1CLK is an unknown speed (probably ~10kHz).
//------------------------------------------------------------------------------
  WDTCTL = WDTPW | WDTHOLD;  // Disable watchdog
//  PJSEL0 |= XINR;
//  PJSEL0 |= XOUTR;

// Clocks:
// Clock System Control 0 Register
  CSCTL0 = CSKEY;            // Unlock register

// Clock System Control 1 Register
  CSCTL1 = CLEAR_REGISTER;   // Clear register
  CSCTL1 = DCOFSEL_6;        // Set DCO setting for 8MHz
//  CSCTL1 &= ~DCORSEL;        // DCO range select. For high-speed devices,
                             // this bit can be written by the user.
                             // For low-speed devices, it is always reset.

// Clock System Control 2 Register
  CSCTL2 = CLEAR_REGISTER;   // Clear register
  CSCTL2 |= SELA__LFXTCLK;
  CSCTL2 |= SELS__DCOCLK;
  CSCTL2 |= SELM__DCOCLK;

// Clock System Control 3 Register
  CSCTL3 = CLEAR_REGISTER;   // Clear register
  CSCTL3 |= DIVA__1;         // set ACLK clock divider /1
  CSCTL3 |= DIVS__1;         // set SMCLK clock divider /1
  CSCTL3 |= DIVM__1;         // set MCLK clock divider /1

// Clock System Control 4 Register
//  CSCTL4 = CLEAR_REGISTER;   // Clear register
  CSCTL4 &= ~LFXTOFF;        // Enable LFXT1

  do
  {
    CSCTL5 &= ~LFXTOFFG;     // Clear XT1 fault flag
    SFRIFG1 &= ~OFIFG;
  } while (SFRIFG1 & OFIFG); // Test oscillator fault flag

//  CSCTL0 = CSLOCK;           // Lock registers
  CSCTL0_H = RESET;              // Lock CS registers



//------------------------------------------------------------------------------
}


