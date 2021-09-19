//Andrew Albright
//ECE 306
//init_serial.c

#include  "msp430.h"
#include  "functions.h"
#include  "macros.h"
#include <string.h>

//GLOBALS
extern unsigned char Baud_Rate;
extern volatile unsigned int usb_rx_ring_wr;
extern volatile unsigned int usb_rx_ring_rd;
extern volatile unsigned int usb_tx_ring_wr;
extern volatile unsigned int usb_tx_ring_rd;
extern volatile char USB_Char_Rx[SMALL_RING_SIZE];
extern volatile char USB_Char_Tx[SMALL_RING_SIZE];

//------------------------------------------------------------------------------

void Init_Serial_UCA3(char Baud_Rate){
  int i;
  for(i=RESET; i<SMALL_RING_SIZE; i++){
    USB_Char_Rx[i] = CHAR_NULL; // USB Rx Buffer
  }
  usb_rx_ring_wr = BEGINNING;
  usb_rx_ring_rd = BEGINNING;
  
  for(i=RESET; i<SMALL_RING_SIZE; i++){ // May not use this
    USB_Char_Tx[i] = CHAR_NULL; // USB Tx Buffer
  }
  usb_tx_ring_wr = BEGINNING;
  usb_tx_ring_rd = BEGINNING;
  
  // Configure UART 3
  UCA3CTLW0 = RESET; // Use word register
  UCA3CTLW0 |= UCSSEL__SMCLK; // Set SMCLK as fBRCLK
  UCA3CTLW0 |= UCSWRST; // Set Software reset enable
  
  if(Baud_Rate == FAST_BAUD){
    UCA3BRW = CONST_ONE; // 
    // UCA0MCTLW = UCSx concatenate UCFx concatenate UCOS16;
    // UCA0MCTLW = 0x49 concatenate 1 concatenate 1;
    UCA3MCTLW = MCTLW_HIGH;
  }
  
  else if(Baud_Rate == SLOW_BAUD){
    UCA3BRW = CONST_FOUR; // 
    // UCA0MCTLW = UCSx concatenate UCFx concatenate UCOS16;
    // UCA0MCTLW = 0x49 concatenate 1 concatenate 1;
    UCA3MCTLW = MCTLW_LOW ;
  }
  UCA3CTL1 &= ~UCSWRST; // Release from reset
  UCA3IE |= UCRXIE; // Enable RX interrupt
}
//------------------------------------------------------------------------------

void Init_Serial_UCA0(){
  int i;
  for(i=RESET; i<SMALL_RING_SIZE; i++){
    USB_Char_Rx[i] = CHAR_NULL; // USB Rx Buffer
  }
  usb_rx_ring_wr = BEGINNING;
  usb_rx_ring_rd = BEGINNING;
  
  for(i=RESET; i<SMALL_RING_SIZE; i++){ // May not use this
    USB_Char_Tx[i] = CHAR_NULL; // USB Tx Buffer
  }
  usb_tx_ring_wr = BEGINNING;
  usb_tx_ring_rd = BEGINNING;
  
  // Configure UART 0
  UCA0CTLW0 = RESET; // Use word register
  UCA0CTLW0 |= UCSSEL__SMCLK; // Set SMCLK as fBRCLK
  UCA0CTLW0 |= UCSWRST; // Set Software reset enable
  
  if(Baud_Rate == FAST_BAUD){
    UCA0BRW = CONST_ONE; // 480,000 Baud
    // UCA0MCTLW = UCSx concatenate UCFx concatenate UCOS16;
    // UCA0MCTLW = 0x49 concatenate 1 concatenate 1;
    UCA0MCTLW = MCTLW_HIGH;
  }
  
  else if(Baud_Rate == SLOW_BAUD){
    UCA0BRW = CONST_FOUR; // 115,200 Baud
    // UCA0MCTLW = UCSx concatenate UCFx concatenate UCOS16;
    // UCA0MCTLW = 0x49 concatenate 1 concatenate 1;
    UCA0MCTLW = MCTLW_LOW;
  }
  UCA0CTL1 &= ~UCSWRST; // Release from reset
  UCA0IE |= UCRXIE; // Enable RX interrupt
}
//------------------------------------------------------------------------------