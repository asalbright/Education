//Andrew Albright
//ECE 306
//ports.c

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
//------------------------------------------------------------------------------
  
void Init_Ports(void){
  Init_Port1();
  Init_Port2();
  Init_Port3(USE_L_REVERSE);        //USE_SMCLK , USE_L_REVERSE
  Init_Port4();
  Init_Port5();
  Init_Port6();
  Init_Port7();
  Init_Port8();
  Init_PortJ();
}

void Init_Port1(void){
  // Configure PORT 1
  // P1_0_LED1               (0x01)
  // P1_1_LED2               (0x02)
  // V_THUMB                 (0x04)
  // TEST_PROBE              (0x08)
  // V_DETECT_R              (0x10)
  // V_DETECT_L              (0x20)
  // SD_MOSI                 (0x40)
  // SD_MISO                 (0x80)
  P1SEL0 = GP_IO;             // GP I/O
  P1SEL1 = GP_IO;             // GP I/O
  P1DIR = DIR_OUT;            // DIRECTION = INPUT
  //P1OUT = 0x00;
  
  //P1_0
  P1SEL0 &= ~P1_0_LED1;                  // P1_0_LED1 as GP I/O 
  P1SEL1 &= ~P1_0_LED1;                  // P1_0_LED1 as GP I/O 
  P1OUT |= P1_0_LED1;                    // Set Red LED On 
  P1DIR |= P1_0_LED1;                    // Set Red LED direction to output 
  //P1_1
  P1SEL0 &= ~P1_1_LED2;                  // P1_1_LED2 as GP I/O 
  P1SEL1 &= ~P1_1_LED2;                  // P1_1_LED2 as GP I/O 
  P1OUT |= P1_1_LED2;                    // Set Green LED On 
  P1DIR |= P1_1_LED2;                    // Set Green LED direction to output
  //P1_2
  P1SEL0 |= V_THUMB;                   // ADC input for Thumbwheel 
  P1SEL1 |= V_THUMB;                   // ADC input for Thumbwheel 
  //P1_3
  P1SEL0 &= ~TEST_PROBE;               // TEST_PROBE as GP I/O 
  P1SEL1 &= ~TEST_PROBE;               // TEST_PROBE as GP I/O 
  P1OUT &= ~TEST_PROBE;                // Set TEST_PROBE Off 
  P1DIR |= TEST_PROBE;                 // Set TEST_PROBE direction to output 
  //P1_4
  P1SEL0 |= V_DETECT_R;                 // ADC input for Right Detector 
  P1SEL1 |= V_DETECT_R;                // ADC input for Right Detector
  //P1_5
  P1SEL0 |= V_DETECT_L;                // ADC input for Left Detector 
  P1SEL1 |= V_DETECT_L;                // ADC input for Left Detector 
  //P1_6
  P1SEL0 &= ~SD_MOSI;              // USCI_B1 MOSI pin 
  P1SEL1 |= SD_MOSI;               // USCI_B1 MOSI pin 
  //P1_7
  P1SEL0 &= ~SD_MISO;              // USCI_B1 MISO pin 
  P1SEL1 |= SD_MISO;               // USCI_B1 MISO pin
}
void Init_Port2(void){
  // Configure PORT 2
  // UCA0TXD                 (0x01)   
  // UCA0RXD                 (0x02)
  // SD_SPICLK               (0x04)
  // P2_3                    (0x08)
  // P2_4                    (0x10)
  // UCA1TXD                 (0x20)
  // UCA1RXD                 (0x40)
  // P2_7                    (0x80)
  
  P2SEL0 = GP_IO;                        //GP I/O
  P2SEL1 = GP_IO;                        // GP I/O
  //P2OUT = DIR_OUT;                         // DIRECTION INPUT
  // P2DIR = 0x00;                      //
  
  //P2_0
  P2SEL0 &= ~UCA0TXD;
  P2SEL1 |= UCA0TXD;
  //P2_1
  P2SEL0 &= ~UCA0RXD;
  P2SEL1 |= UCA0RXD;
  //P2_2
  P2SEL0 &= ~SD_SPICLK;
  P2SEL1 |= SD_SPICLK;
  //P2_3
  P2SEL0 &= ~P2_3;               //GP I/O
  P2SEL1 &= ~P2_3;               //GP I/O
  P2DIR &= ~P2_3;               //INPUT
  //P2_4
  P2SEL0 &= ~P2_4;               //GP I/O
  P2SEL1 &= ~P2_4;               //GP I/O
  P2DIR &= ~P2_4;               //INPUT
  //P2_5
  P2SEL0 &= ~UCA1TXD;
  P2SEL1 |= UCA1TXD;
  //P2_6
  P2SEL0 &= ~UCA1RXD;
  P2SEL1 |= UCA1RXD;
  //P2_7
  P2SEL0 &= ~P2_7;               //GP I/O
  P2SEL1 &= ~P2_7;               //GP I/O
  P2DIR &= ~P2_7;               //INPUT
}
void Init_Port3(unsigned char value){
  // Configure PORT 3
  // IOT_RESET               (0x01)
  // IOT_PROG_MODE           (0x02)
  // IOT_LINK                (0x04)
  // IOT_PROG_SEL            (0x08)
  // L_REVERSE               (0x10)
  // L_FORWARD               (0x20)
  // R_REVERSE               (0x40)
  // R_FORWARD               (0x80)
    P3DIR = DIR_OUT;              // SET P1 DIRECTION TO OUTPUT ????????????
    P3OUT = SET_LOW;              // P1 SET LOW
    //P3_0
    P3SEL0 &= ~IOT_RESET;           // Set to GP I/O
    P3SEL1 &= ~IOT_RESET;           // Set to GP I/O 
    P3OUT &= ~IOT_RESET;            // Set out value Low [active] 
    P3DIR |= IOT_RESET;             // Set direction to output
    //P3_1
    P3SEL0 &= ~IOT_PROG_MODE;       // Set to GP I/O 
    P3SEL1 &= ~IOT_PROG_MODE;       // Set to GP I/O 
    P3DIR &= ~IOT_PROG_MODE;  // Set direction to input
    //P3_2
    P3SEL0 &= ~IOT_LINK;            // Set to GP I/O 
    P3SEL1 &= ~IOT_LINK;            // Set to GP I/O 
    P3OUT &= ~IOT_LINK;             // Set out value to LOw
    P3DIR &= ~IOT_LINK;             // Set direction to inpuT
    //P3_3
    P3SEL0 &= ~IOT_PROG_SEL;        // Set to GP I/O 
    P3SEL1 &= ~IOT_PROG_SEL;        // Set to GP I/O 
    P3DIR &= ~ IOT_PROG_SEL;        // Set direction to input
    //P3_4 (changed for hw_04
    switch(value){
      case USE_SMCLK:
        //set pin to be used as small clock
        //P3_4  changed for hw_04
        P3SEL0 |= L_REVERSE;           // Set to SMCLK 
        P3SEL1 |= L_REVERSE;           // Set to SMCLK
        P3DIR |= L_REVERSE;             // Set direction to OUTPut
        
      case USE_L_REVERSE:
        //set pin to be used as a reverse pin
        //P3_4
        P3SEL0 |= L_REVERSE;           // Set to Function 
        P3SEL1 &= ~L_REVERSE;           // Set to Function 
        P3DIR |= L_REVERSE;             // Set direction to output
        //P3OUT &= ~L_REVERSE;
    }
    //P3_5
    P3SEL0 |= L_FORWARD;           // Set to Function 
    P3SEL1 &= ~L_FORWARD;           // Set to Function 
    P3DIR |= L_FORWARD;             // Set direction to output
    //P3OUT &= ~L_FORWARD; //tried to force it here too
    //P3_6
    P3SEL0 |= R_REVERSE;           // Set to Function 
    P3SEL1 &= ~R_REVERSE;           // Set to Function 
    P3DIR |= R_REVERSE;             // Set direction to output
    //P3OUT &= ~R_REVERSE;
    //P3_7
    P3SEL0 |= R_FORWARD;           // Set to Function
    P3SEL1 &= ~R_FORWARD;           // Set to Function 
    P3DIR |= R_FORWARD;             // Set direction to output
    //P3OUT &= ~R_FORWARD;
  //------------------------------------------------------------------------------
}
void Init_Port4(void){
  // Configure PORT 4
  // SD_CS                   (0x01) 
  //  J4_31                  (0x02)
  // J4_32                   (0x04)
  // J4_33                   (0x08)
  // UCB1_CS_LCD             (0x10)
  // P4_4                    (0x20)
  // P4_5                    (0x40)
  // J3_29                   (0x80)
  
  P4SEL0 = GP_IO;
  P4SEL1 = GP_IO;
  P4DIR = DIR_OUT;
  //P4OUT = 0x00;
  
  //P4_0
  P4SEL0 &= ~SD_CS;           // Set to GP I/O 
  P4SEL1 &= ~SD_CS;           // Set to GP I/O 
  P4DIR &= ~SD_CS;             // Set direction to output
  //P4_1
  P4SEL0 &= ~J4_31;           // Set to GP I/O 
  P4SEL1 &= ~J4_31;           // Set to GP I/O 
  P4DIR &= ~J4_31;             // Set direction to output
  //P4_2
  P4SEL0 &= ~J4_32;           // Set to GP I/O 
  P4SEL1 &= ~J4_32;           // Set to GP I/O 
  P4DIR &= ~J4_32;             // Set direction to output
  //P4_3
  P4SEL0 &= ~J4_33;           // Set to GP I/O 
  P4SEL1 &= ~J4_33;           // Set to GP I/O 
  P4DIR &= ~J4_33;            // Set direction to output
  //P4_4 ???????????????????????
  P4SEL0 &= ~UCB1_CS_LCD;
  P4SEL1 &= ~UCB1_CS_LCD;
  P4DIR |= UCB1_CS_LCD;
  P4OUT &= ~UCB1_CS_LCD;
  //P4_5
  P4SEL0 &= ~P4_4;           // Set to GP I/O 
  P4SEL1 &= ~P4_4;           // Set to GP I/O 
  P4DIR &= ~P4_4;             // Set direction to output
  //P4_6
  P4SEL0 &= ~P4_5;           // Set to GP I/O 
  P4SEL1 &= ~P4_5;           // Set to GP I/O 
  P4DIR &= ~P4_5;             // Set direction to output
  //P4_7
  P4SEL0 &= ~J3_29;           // Set to GP I/O 
  P4SEL1 &= ~J3_29;           // Set to GP I/O 
  P4DIR &= ~J3_29;             // Set direction to output
}
void Init_Port5(void){
  // Configure PORT 5 
  // SPI_UCB1SIMO         (0x01)    // UCB1SIMO 
  // SPI_UCB1SOMI         (0x02)    // UCB1SOMI 
  // SPI_UCB1CLK          (0x04)    // SPI mode - clock output—UCB1CLK 
  // RESET_LCD            (0x08)    // LCD Reset 
  // BUTTON2              (0x20)    // Button 2 
  // BUTTON1              (0x40)    // Button 1 
  // LCD_BACKLITE         (0x80)    // LCD Backlight
  
    P5SEL0 = GP_IO;                  // GP I/O 
    P5SEL1 = GP_IO;                  // GP I/O
    
  //P5_0 
    P5SEL0 |= SPI_UCB1SIMO;         // USCI_B1 SIMO pin 
    P5SEL1 &= ~SPI_UCB1SIMO;        // USCI_B1 SIMO pin
  //P5_1 
    P5SEL0 |= SPI_UCB1SOMI;         // USCI_B1 SOMI pin 
    P5SEL1 &= ~SPI_UCB1SOMI;        // USCI_B1 SOMI pin
  //P5_2 
    P5SEL0 |= SPI_UCB1CLK;          // USCI_B1 SCLK pin 
    P5SEL1 &= ~SPI_UCB1CLK;         // USCI_B1 SCLK pin
  //P5_3 
    P5SEL0 &= ~RESET_LCD;           // Set GP I/O for RESET_LCD 
    P5SEL1 &= ~RESET_LCD;           // Set GP I/O for RESET_LCD 
    P5OUT |= RESET_LCD;             // Set RESET_LCD Off [High] 
    P5DIR |= RESET_LCD;             // Set RESET_LCD direction to output
  //P5_4 
    P5SEL0 &= ~P5_4_UNUSED;         // Set GP I/O for P5_4_UNUSED 
    P5SEL1 &= ~P5_4_UNUSED;         // Set GP I/O for P5_4_UNUSED 
    P5DIR &= ~P5_4_UNUSED;           // Set RESET_LCD direction to input
  //P5_5 ?????????????????
    P5SEL0 &= ~BUTTON2;            // Set GP I/O for BUTTON2 
    P5SEL1 &= ~BUTTON2;             // Set GP I/O for BUTTON2 
    P5OUT |= BUTTON2;              // Configure pullup resistor 
    P5DIR &= ~BUTTON2;             // Direction = input 
    P5REN |= BUTTON2;              // Enable pullup resistor 
    P5IES |= BUTTON2;            // P5.5 Hi/Lo edge interrupt 
    P5IFG &= ~BUTTON2;           // Clear all P5.6 interrupt flags 
    P5IE |= BUTTON2;             // P5.5 interrupt enabled
  //P5_6 ?????????????????
    P5SEL0 &= ~BUTTON1;         // Set GP I/O for BUTTON1 
    P5SEL1 &= ~BUTTON1;         // Set GP I/O for BUTTON1 
    P5OUT |= BUTTON1;           // Configure pullup resistor 
    P5DIR &= ~BUTTON1;          // Direction = input 
    P5REN |= BUTTON1;           // Enable pullup resistor 
    P5IES |= BUTTON1;         // P5.6 Hi/Lo edge interrupt 
    P5IFG &= ~BUTTON1;        // Clear all P5.5 interrupt flags 
    P5IE |= BUTTON1;          // P5.6 interrupt enabled
  //P5_7 
    P5SEL0 &= ~LCD_BACKLITE;   // Set GP I/O for LCD_BACKLITE 
    P5SEL1 &= ~LCD_BACKLITE;   // Set GP I/O for LCD_BACKLITE 
    P5OUT |= LCD_BACKLITE;     // Set LCD_BACKLITE On [High] 
    P5DIR |= LCD_BACKLITE;     // Set LCD_BACKLITE direction to output 
    //-------------------------------------------------------------------
}
void Init_Port6(void){
  // Configure PORT 6
  // UCA3TXD                 (0x01) 
  // UCA3RXD                 (0x02)
  // J1_5                    (0x04)
  // MAG_INT                 (0x08)
  // P6_4                    (0x10)
  // P6_5                    (0x20)
  // P6_6                    (0x40)
  // P6_7                    (0x80)
  
  P6SEL0 = GP_IO;
  P6SEL1 = GP_IO;
  P6DIR = DIR_OUT;
 // P6OUT = 0x00;
  
  //P6_0
  P6SEL0 |= UCA3TXD;
  P6SEL1 &= ~UCA3TXD;
   //P6_1
  P6SEL0 |= UCA3RXD;
  P6SEL1 &= ~UCA3RXD;
  //P6_2
  P6SEL0 &= ~J1_5;
  P6SEL1 &= ~J1_5;
  P6DIR &= ~J1_5;
  //P6_3
  P6SEL0 &= ~MAG_INT;
  P6SEL1 &= ~MAG_INT;
  P6DIR &= ~MAG_INT;
  //P6_4
  P6SEL0 &= ~P6_4;
  P6SEL1 &= ~P6_4;
  P6DIR &= ~P6_4;
  //P6_5
  P6SEL0 &= ~P6_5;
  P6SEL1 &= ~P6_5;
  P6DIR &= ~P6_5;
  //P6_6
  P6SEL0 &= ~P6_6;
  P6SEL1 &= ~P6_6;
  P6DIR &= ~P6_6;
  //P6_7
  P6SEL0 &= ~P6_7;
  P6SEL1 &= ~P6_7;
  P6DIR &= ~P6_7;
}
void Init_Port7(void){
  // Configure PORT 7
  // I2CSDA                  (0x01)
  // I2CSCL                  (0x02)
  // SD_DETECT               (0x04)
  // J4_36                   (0x08)
  // P7_4                    (0x10)
  // P7_5                    (0x20)
  // P7_6                    (0x40)
  // P7_7                    (0x80)
  
  P7SEL0 = GP_IO;
  P7SEL1 = GP_IO;
  P7DIR = DIR_OUT;
  //P7OUT = 0x00;
  
  //P7_0
  P7SEL0 &= ~I2CSDA;
  P7SEL1 &= ~I2CSDA;
  P7DIR &= ~I2CSDA;
  //P7_1
  P7SEL0 &= ~I2CSCL;
  P7SEL1 &= ~I2CSCL;
  P7DIR &= ~I2CSCL;
  //P7_2
  P7SEL0 &= ~SD_DETECT;
  P7SEL1 &= ~SD_DETECT;
  P7DIR &= ~SD_DETECT;
  //P7_3
  P7SEL0 &= ~J4_36;
  P7SEL1 &= ~J4_36;
  P7DIR &= ~J4_36;
  //P7_4
  P7SEL0 &= ~P7_4;
  P7SEL1 &= ~P7_4;
  P7DIR &= ~P7_4;
  //P7_5
  P7SEL0 &= ~P7_5;
  P7SEL1 &= ~P7_5;
  P7DIR &= ~P7_5;
  //P7_6
  P7SEL0 &= ~P7_6;
  P7SEL1 &= ~P7_6;
  P7DIR &= ~P7_6;
  //P7_7
  P7SEL0 &= ~P7_7;
  P7SEL1 &= ~P7_7;
  P7DIR &= ~P7_7;
}
void Init_Port8(void){
  // Configure PORT 8
  // IR_LED                  (0x01)
  // OPT_INT                 (0x02)
  // TMP_INT                 (0x04)
  // INT2                    (0x08)
  
  P8SEL0 = GP_IO;
  P8SEL1 = GP_IO;
  P8DIR = DIR_OUT;
  //P8OUT = 0x00;
  
  
  //P8_0 ***changed for project 6***
  P8SEL0 &= ~IR_LED;
  P8SEL1 &= ~IR_LED;
  P8DIR |= IR_LED;
  P8OUT &= ~IR_LED;

  //P8_1
  P8SEL0 &= ~OPT_INT;
  P8SEL1 &= ~OPT_INT;
  P8DIR &= ~OPT_INT;
  //P8_2
  P8SEL0 &= ~TMP_INT;
  P8SEL1 &= ~TMP_INT;
  P8DIR &= ~TMP_INT;
  //P8_3
  P8SEL0 &= ~INT2;
  P8SEL1 &= ~INT2;
  P8DIR &= ~INT2;
}
void Init_PortJ(void){
  // Configure PORT j
  // PJ_0                    (0x01) 
  // PJ_1                    (0x02)
  // PJ_2                    (0x04)
  // PJ_3                    (0x08)
  // LFXIN                   (0x10)
  // LFXOUT                  (0x20)
  // HFXIN                   (0x40)
  // HFXOUT                  (0x80)
  
  PJSEL0 = GP_IO;
  PJSEL1 = GP_IO;
  PJDIR = DIR_OUT;
  PJOUT = SET_LOW;
  
  PJSEL0 |= LFXIN;   // For XT1
  PJSEL1 &= ~LFXIN;  // For XT1

  PJSEL0 |= LFXOUT;  // For XT1
  PJSEL1 &= ~LFXOUT; // For XT1
  
  PJSEL0 &= ~HFXIN;  // For XT2
  PJSEL1 &= ~HFXIN;  // For XT2

  PJSEL0 &= ~HFXOUT; // For XT2
  PJSEL1 &= ~HFXOUT; // For XT2
}
