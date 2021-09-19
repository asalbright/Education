//Andrew Albright
//ECE 306
//interrupt_ports.c

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
extern volatile unsigned int Timer_A1_Interrupted;
extern volatile unsigned int Timer_A2_Interrupted;
extern unsigned char Timer_A2_Running;
extern unsigned char Display;
extern unsigned char Baud_Operation;
extern unsigned char Button_Pressed;
extern unsigned char Transmit_Active;
extern unsigned char Baud_Rate;
extern unsigned char Command_Recieved;

extern char Set_Control_Port[];
extern char Set_Cont_Port;
extern unsigned char IOT_Row;
extern unsigned char Operation;


unsigned char Button_Debouncing = RESET;
volatile unsigned int ADC_Thumb;
volatile unsigned int ADC_Right_Detector;
volatile unsigned int ADC_Left_Detector;

volatile unsigned int usb_rx_ring_wr;
volatile unsigned int usb_rx_ring_rd;
volatile unsigned int usb_tx_ring_wr;
volatile unsigned int usb_tx_ring_rd;

volatile char USB_Char_Rx[SMALL_RING_SIZE];
volatile char USB_Char_Tx[SMALL_RING_SIZE];


unsigned int UCA0_index = RESET;
unsigned int UCA3_index = RESET;

char Controlled_Message[SMALL_RING_SIZE];
char IOT_Transmit[CONST_TWO][SMALL_RING_SIZE];
char IP_Address[SMALL_RING_SIZE];

unsigned int IOT_Column_Write = RESET;
unsigned int IOT_Row_Write = UPPER_ROW;


//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Port 5 interrupt. For BUTTONS, they are disabled for the duration
// of the debounce timer. Flag is set that user space can check.
//Include #pragma vector = [Assigned Vector]
#pragma vector = PORT5_VECTOR
__interrupt void BUTTON_interrupt(void){
  // BUTTON 1
  if (P5IFG & BUTTON1) {
    strcpy(display_line[disp_line_0], "DEBOUNCING");
    strcpy(display_line[disp_line_1], " BUTTON 1 ");
    strcpy(display_line[disp_line_2], "          ");
    switch(Display){
    case CONST_THREE:
      strcpy(display_line[disp_line_3], " Transmit ");
      break;
    default:
      strcpy(display_line[disp_line_3], "          ");
      break;
    }    
    enable_display_update();
    Display_Update(CONST_ZERO,CONST_ZERO,CONST_ZERO,CONST_ZERO);
    display_changed = ALWAYS;
    
    P8OUT |= IR_LED;            //activate IR sensors        
    

    P5OUT &= ~LCD_BACKLITE;     //change backlite
    TA0CCTL0 &= ~CCIE;          //disable timer a0
    TA0CCTL2 &= ~CCIE;          //disable timer a2
    Button_Debouncing = BUTTON_1;       //set button debouncing
    Timer_A1_Interrupted = RESET;       //reset button debouncing count
    TA0CCR1 += TA0CCR1_INTERVAL;        //add interval to count 
    TA0CCTL1 |= CCIE;                   //enable timer a1

  }
  // BUTTON 2
  if (P5IFG & BUTTON2) {
    strcpy(display_line[disp_line_0], "DEBOUNCING");
    strcpy(display_line[disp_line_1], " BUTTON 2 ");
    strcpy(display_line[disp_line_2], "          ");
    switch(Display){
      case CONST_FOUR:
        strcpy(display_line[disp_line_3], "Caling IRs");
        break;
      case CONST_THREE:
        strcpy(display_line[disp_line_3], "Chang Baud");
        break;
      default: break;
    }
    enable_display_update();
    Display_Update(CONST_ZERO,CONST_ZERO,CONST_ZERO,CONST_ZERO);
    display_changed = ALWAYS;
    
    P8OUT |= IR_LED;

    P5OUT &= ~LCD_BACKLITE;
    TA0CCTL0 &= ~CCIE;
    TA0CCTL2 &= ~CCIE;
    Button_Debouncing = BUTTON_2;
    Timer_A1_Interrupted = RESET;
    TA0CCR1 += TA0CCR1_INTERVAL;
    TA0CCTL1 |= CCIE;
    
  }
  // Enable the Timer Interrupt for the debounce.
}
//------------------------------------------------------------------------------

#pragma vector = ADC12_B_VECTOR
__interrupt void ADC12_ISR(void){
 switch(__even_in_range(ADC12IV, ADC12IV__ADC12RDYIFG)){
 case ADC12IV__NONE: break; // Vector 0: No interrupt
 case ADC12IV__ADC12OVIFG: break; // Vector 2: ADC12MEMx Overflow
 case ADC12IV__ADC12TOVIFG: break; // Vector 4: Conversion time overflow
 case ADC12IV__ADC12HIIFG: break; // Vector 6: ADC12BHI
 case ADC12IV__ADC12LOIFG: break; // Vector 8: ADC12BLO
 case ADC12IV__ADC12INIFG: break; // Vector 10: ADC12BIN
 case ADC12IV__ADC12IFG0: break; // Vector 12: ADC12MEM0 Interrupt
 case ADC12IV__ADC12IFG1: break; // Vector 14: ADC12MEM1 Interrupt
 case ADC12IV__ADC12IFG2: // Vector 16: ADC12MEM2 Interrupt
 ADC_Thumb = ADC12MEM0; // A02 ADC10INCH_2
 ADC_Right_Detector = ADC12MEM1; // A05 ADC10INCH_4
 ADC_Left_Detector = ADC12MEM2; // A04 ADC10INCH_5
 break;
 case ADC12IV__ADC12IFG3: break; // Vector 18: ADC12MEM3
 case ADC12IV__ADC12IFG4: break; // Vector 20: ADC12MEM4
 case ADC12IV__ADC12IFG5: break; // Vector 22: ADC12MEM5
 case ADC12IV__ADC12IFG6: break; // Vector 24: ADC12MEM6
 case ADC12IV__ADC12IFG7: break; // Vector 26: ADC12MEM7
 case ADC12IV__ADC12IFG8: break; // Vector 28: ADC12MEM8
 case ADC12IV__ADC12IFG9: break; // Vector 30: ADC12MEM9
 case ADC12IV__ADC12IFG10: break; // Vector 32: ADC12MEM10
 case ADC12IV__ADC12IFG11: break; // Vector 34: ADC12MEM11
 case ADC12IV__ADC12IFG12: break; // Vector 36: ADC12MEM12
 case ADC12IV__ADC12IFG13: break; // Vector 38: ADC12MEM13
 case ADC12IV__ADC12IFG14: break; // Vector 40: ADC12MEM14
 case ADC12IV__ADC12IFG15: break; // Vector 42: ADC12MEM15
 case ADC12IV__ADC12IFG16: break; // Vector 44: ADC12MEM16
 case ADC12IV__ADC12IFG17: break; // Vector 46: ADC12MEM17
 case ADC12IV__ADC12IFG18: break; // Vector 48: ADC12MEM18
 case ADC12IV__ADC12IFG19: break; // Vector 50: ADC12MEM19
 case ADC12IV__ADC12IFG20: break; // Vector 52: ADC12MEM20
 case ADC12IV__ADC12IFG21: break; // Vector 54: ADC12MEM21
 case ADC12IV__ADC12IFG22: break; // Vector 56: ADC12MEM22
 case ADC12IV__ADC12IFG23: break; // Vector 58: ADC12MEM23
 case ADC12IV__ADC12IFG24: break; // Vector 60: ADC12MEM24
 case ADC12IV__ADC12IFG25: break; // Vector 62: ADC12MEM25
 case ADC12IV__ADC12IFG26: break; // Vector 64: ADC12MEM26
 case ADC12IV__ADC12IFG27: break; // Vector 66: ADC12MEM27
 case ADC12IV__ADC12IFG28: break; // Vector 68: ADC12MEM28
 case ADC12IV__ADC12IFG29: break; // Vector 70: ADC12MEM29
 case ADC12IV__ADC12IFG30: break; // Vector 72: ADC12MEM30
 case ADC12IV__ADC12IFG31: break; // Vector 74: ADC12MEM31
 case ADC12IV__ADC12RDYIFG: break; // Vector 76: ADC12RDY
 default: break;
 }
}

//USCI_A0
//------------------------------------------------------------------------------
#pragma vector=USCI_A0_VECTOR
__interrupt void USCI_A0_ISR(void){
 unsigned int temp;
 char translate;
 switch(__even_in_range(UCA0IV,HEX_EIGHT)){
   case CONST_ZERO: // Vector 0 - no interrupt
    break;
    
   case CONST_TWO: // Vector 2 - RXIFG
     temp = usb_rx_ring_wr;
     USB_Char_Rx[temp] = UCA0RXBUF; // RX -> USB_Char_Rx character
     translate = UCA0RXBUF;
     UCA3TXBUF = translate;
    
//reset the write pointer if 11 characters have been read
     if (++usb_rx_ring_wr >= (SMALL_RING_SIZE)){
     usb_rx_ring_wr = BEGINNING; // Circular buffer back to beginning
     }
     break;
     
   case CONST_FOUR: // Vector 4 – TXIFG
     switch(UCA0_index++){
       case MESSAGE_CHAR_ZERO: //
       case MESSAGE_CHAR_ONE: //
       case MESSAGE_CHAR_TWO: //
       case MESSAGE_CHAR_THREE: //
       case MESSAGE_CHAR_FOUR: //
       case MESSAGE_CHAR_FIVE: //
       case MESSAGE_CHAR_SIX: //
       case MESSAGE_CHAR_SEVEN: //
       case MESSAGE_CHAR_EIGHT: //
       case MESSAGE_CHAR_NINE: //
       case MESSAGE_CHAR_TEN:
         switch(Controlled_Message[UCA0_index - CONST_ONE]){
         case CARREAGE_RETURN:
           UCA0TXBUF = CARREAGE_RETURN;
           break;
         default: 
           UCA0TXBUF = Controlled_Message[UCA0_index - CONST_ONE];
           break;
         }
         break;
       default:
         Button_Pressed = BUTTON_1;
         Baud_Operation = WAITING;
         UCA0IE &= ~UCTXIE; // Disable TX interrupt
         break;
       } 
       break;
   
   default: break;
 }
}
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
#pragma vector=USCI_A3_VECTOR
__interrupt void USCI_A3_ISR(void){
 unsigned int temp;
 char translate;
 switch(__even_in_range(UCA3IV,HEX_EIGHT)){
   case CONST_ZERO: // Vector 0 - no interrupt
    break;
    
   case CONST_TWO: // Vector 2 - RXIFG
     temp = usb_rx_ring_wr;
     USB_Char_Rx[temp] = UCA3RXBUF; // RX -> USB_Char_Rx character
     Controlled_Message[temp] = UCA3RXBUF;
     translate = UCA3RXBUF;
     UCA0TXBUF = translate;
//decifer characters comming into buffer
     switch(translate){
//begin the transmission of characters
     case START_TRANSMIT:
         Transmit_Active = ACTIVE;
       break;
//end the transmission of characters
     case END_TRANSMIT:
       if(strstr(IOT_Transmit[IOT_Row_Write], "9698_")){
         //has passcode been entered?
         switch(IOT_Row_Write){
         case UPPER_ROW:
           IOT_Row_Write = LOWER_ROW;
           IOT_Row = UPPER_ROW;
           break;
         case LOWER_ROW:
           IOT_Row_Write = UPPER_ROW;
           IOT_Row = LOWER_ROW;
           break;
         default: break;
         }
         if(strstr(IOT_Transmit[IOT_Row_Write], "9698_I")){
           Operation = IOT_MODE;
         }
         //Command_Recieved = READ_COMMAND;
       }
       else{
         memset(IOT_Transmit[IOT_Row_Write], CHAR_NULL, SMALL_RING_SIZE);
       }
       //deactivate copying characters
       Transmit_Active = INACTIVE;
       break;
//find IP address
     case CARREAGE_RETURN:
       if((strstr(Controlled_Message, "NWCONN-SUCCESS"))){
         Command_Recieved = FIND_IP_ADDRESS;
       }
       break;
//copy IP address
     case FOUND_IP:
       if((strstr(Controlled_Message, "IP addr"))){
         Transmit_Active = COPY_IP;
       }
       break;
//to ensure looked for strings will always be in the right place
     case LINE_FEED:
       usb_rx_ring_wr = BEGINNING;
       break;
     default:
       break;
     }
//copy characters 
     switch(Transmit_Active){
       //initiate copy of command
     case ACTIVE:
       switch(IOT_Row_Write){
       case UPPER_ROW:
         switch(IOT_Column_Write){
         case CONST_SIXTEEN:
           IOT_Column_Write = RESET;
         default:
           IOT_Transmit[IOT_Row_Write][IOT_Column_Write] = translate;
           IOT_Column_Write++;
           break;
         }
         break;
       case LOWER_ROW:
         switch(IOT_Column_Write){
         case CONST_SIXTEEN:
           IOT_Column_Write = RESET;
         default:
           IOT_Transmit[IOT_Row_Write][IOT_Column_Write] = translate;
           IOT_Column_Write++;
           break;
         }
         break;
       default: break;
       }
//has a non termitating char been read?
       switch(translate){
       case START_TRANSMIT:
         switch(IOT_Column_Write){
         case CONST_ONE:
           break;
         default: 
           memset(IOT_Transmit[IOT_Row_Write], CHAR_NULL, SMALL_RING_SIZE);
           Transmit_Active = INACTIVE;
           break;
         }
         break;
       case LINE_FEED:
         memset(IOT_Transmit[IOT_Row_Write], CHAR_NULL, SMALL_RING_SIZE);
         Transmit_Active = INACTIVE;
         break;
         
       default: break;
       }
       break;
//COPY IP
     case COPY_IP:
       switch(translate){
       case FOUND_IP:
         break;
       case END_IP:
         Command_Recieved = IOT_CONNECTED;
         Baud_Operation = IOT_CONNECTED;
         Transmit_Active = INACTIVE;
         break;
       default:
         IP_Address[IOT_Column_Write] = translate;
         IOT_Column_Write++;
         break;
       }
       break;
//deactivate command 
     case INACTIVE:
       IOT_Column_Write = RESET;
       break;
       
     default: break;
     }
   

//reset the write pointer if SMALL_RING_SIZE characters have been read
     if (++usb_rx_ring_wr >= (SMALL_RING_SIZE)){
     usb_rx_ring_wr = BEGINNING; // Circular buffer back to beginning
     
     }
     break;
     
   case CONST_FOUR: // Vector 4 – TXIFG
     switch(UCA3_index++){
       case MESSAGE_CHAR_ZERO: //
       case MESSAGE_CHAR_ONE: //
       case MESSAGE_CHAR_TWO: //
       case MESSAGE_CHAR_THREE: //
       case MESSAGE_CHAR_FOUR: //
       case MESSAGE_CHAR_FIVE: //
       case MESSAGE_CHAR_SIX: //
       case MESSAGE_CHAR_SEVEN: //
       case MESSAGE_CHAR_EIGHT: //
       case MESSAGE_CHAR_NINE: //
       case MESSAGE_CHAR_TEN:
         switch(Controlled_Message[UCA3_index - CONST_ONE]){
         case CARREAGE_RETURN:
           UCA3TXBUF = CARREAGE_RETURN;
           break;
         default: 
           UCA3TXBUF = Controlled_Message[UCA3_index - CONST_ONE];
           break;
         }
         break;
       default:
         Button_Pressed = BUTTON_1;
         Baud_Operation = WAITING;
         UCA3IE &= ~UCTXIE; // Disable TX interrupt
         break;
       } 
       break;
   
   default: break;
 }
}
//------------------------------------------------------------------------------
