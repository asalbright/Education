//Andrew Albright
//ECE 306
//commands.c

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

//added
extern char IOT_Transmit[CONST_TWO][SMALL_RING_SIZE];
extern volatile unsigned int ADC_Thumb;
extern volatile unsigned int ADC_Right_Detector;
extern volatile unsigned int ADC_Left_Detector;
extern volatile unsigned int Timer_A2_Interrupted;
extern unsigned int IOT_Row_Write;
extern unsigned char Display;


char* Transmit_Index = IOT_Transmit[UPPER_ROW];

unsigned char Command_Recieved = RESET;
unsigned int Timer_A2_Time = RESET;//could use a MACRO
unsigned char Timer_A2_Running = OFF;
unsigned int Black_Line;
unsigned int White_Line;
unsigned int Time_to_Wait = RESET;
unsigned char Operation = IOT_MODE;
unsigned char Last_Operation = RESET;
unsigned int Run_Time = RESET;

unsigned int Right_Speed = FIFTEEN_SPEED;
unsigned int Left_Speed = FIFTEEN_SPEED;

char Find_IP[] = {"AT+NSTAT=?"};
char Set_Control_Port[] = {"AT+NSTCP=9698,1"};

unsigned char IOT_Row = RESET;
char* IOT_Read_Index;
char Check_Timer = RUNNING;


//------------------------------------------------------------------------------
//translate_commands functions purpose is to translate the commands set into the
// global string by the transmit interrupt. Function takes in nothing and returns
//nothing.
//------------------------------------------------------------------------------
void translate_commands(void){
  switch(Command_Recieved){
  case FIND_IP_ADDRESS:
    for(int i = RESET; i < CONST_TEN; i++){
      out_character(Find_IP[i]);
    }
    out_character(CARREAGE_RETURN);
    Command_Recieved = RESET;
    break;
    
  case IOT_CONNECTED:
    for(int i = RESET; i < CONST_FIFTEEN; i++){
      out_character(Set_Control_Port[i]);
    }
    out_character(CARREAGE_RETURN);
    Display = MAIN_MENU;
    Command_Recieved = READ_COMMAND;
    break;
    
  case READ_COMMAND:
    switch(Timer_A2_Running){
    case RUNNING:
      Check_Timer = RUNNING;
      break;
    default: 
      break;
    }
    Check_Command_Buffer();
    break;
    
  case RUN_COMMAND:
    switch(IOT_Row){
    case UPPER_ROW:
      IOT_Read_Index = IOT_Transmit[UPPER_ROW];
      Run_Command();
      break;
    case LOWER_ROW:
      IOT_Read_Index = IOT_Transmit[LOWER_ROW];
      Run_Command();
      break;
      
    default: break;
    }
    break;
    
  default: break;
  }
}
//------------------------------------------------------------------------------

//functions
//------------------------------------------------------------------------------
//out_character functions purpose is to for a character to the transmit buffer of
//the transmit interrupt. Function takes in character to transmit and returns
//nothing.
//------------------------------------------------------------------------------
void out_character(char character){
//------------------------------------------------------------------------------
// The while loop will stall as long as the Flag is not set [port is busy]
 while (!(UCA3IFG & UCTXIFG)); // USCI_A0 TX buffer ready?
 UCA3TXBUF = character;
//------------------------------------------------------------------------------
}

//------------------------------------------------------------------------------
//Check_Command_Buffer functions purpose is to ensure the code was entered when 
//command was sent. Function takes in nothing and returns nothing.
//------------------------------------------------------------------------------
void Check_Command_Buffer(void){
  if(strstr(IOT_Transmit[IOT_Row], "9698_S")){
    IOT_Row = IOT_Row;
    Command_Recieved = RUN_COMMAND;
  }
  else if(strstr(IOT_Transmit[UPPER_ROW], "9698_")){
    if(Timer_A2_Running == OFF){
      IOT_Row = UPPER_ROW;
    }
    Command_Recieved = RUN_COMMAND;
  }
  else if(strstr(IOT_Transmit[LOWER_ROW], "9698_")){
    if(Timer_A2_Running == OFF){
      IOT_Row = LOWER_ROW;
    }
    Command_Recieved = RUN_COMMAND;
  }
  else Command_Recieved = READ_COMMAND;
}
//------------------------------------------------------------------------------
//Run_Command functions purpose is to decifer and run the command sent by the client.
//Function takes in nothing and returns nothing.
//------------------------------------------------------------------------------
void Run_Command(void){
  switch(*(COMMAND)){
  case MOVE_FORWARD:
    Move_Forward(Set_Run_Time(*(RUN_TIME)));
    break;
  case MOVE_BACKWARD:
    Move_Backward(Set_Run_Time(*(RUN_TIME)));
    break;
  case TURN_RIGHT:
    Turn_Right(Set_Run_Time(*(RUN_TIME)));
    break;
  case TURN_LEFT:
    Turn_Left(Set_Run_Time(*(RUN_TIME)));
    break;
  case CHANGE_SPEED:
    Change_Wheel_Speed(*(WHEEL_TO_CHANGE), *(SPEED_CHANGE)); 
    break;
  case AUTO_MODE:
    Operation = AUTO_MODE;
    memset(IOT_Transmit[IOT_Row], CHAR_NULL, SMALL_RING_SIZE);
    break;
  case STOP_WHEELS:
  default: 
    Hault_Movement();
    Command_Recieved = READ_COMMAND;
    break;
  }
}

//------------------------------------------------------------------------------
//Set_Run_Timer functions purpose is to set a global variable used by Timer A2 to
//allow operations to run for a certian time. Function takes in char sent by client
//and returns integer to be set nothing.
//------------------------------------------------------------------------------
int Set_Run_Time(char Run_Time){
  int Time = RESET;
  switch(Run_Time){
  case CHAR_ZERO:
    Time = A2_TENTH_SECOND;
    break;
    case CHAR_ONE:
    Time = A2_1_SECOND;
    break;
    case CHAR_TWO:
    Time = A2_2_SECOND;
    break;
  default: break;
  }
  return Time;
}

//------------------------------------------------------------------------------
//Move_Forward functions purpose is to allow the car to drive forward. Function takes 
//in integer time to move forward and returns nothing.
//------------------------------------------------------------------------------
void Move_Forward(int Time){
  switch(Timer_A2_Running){
  case ON:
    Timer_A2_ON();
    break;
  case RUNNING:
    switch(Check_Timer){
    case RUNNING:
      Timer_A2_Running = OFF;
      Check_Timer = RESET;
      break;
    default: 
      RIGHT_FORWARD_SPEED = Right_Speed;
      LEFT_FORWARD_SPEED = Left_Speed;
      break;
    }
    break;
  case OFF:
    Timer_A2_OFF(Time);
    break;
  case STOP:
    Timer_A2_STOP();
    break;
  default: break;
  }
}
//------------------------------------------------------------------------------
//Move_Backward functions purpose is to allow the car to drive backward. Function 
//takes in integer time to move backward and returns nothing.
//------------------------------------------------------------------------------
void Move_Backward(int Time){
  switch(Timer_A2_Running){
  case ON:
    Timer_A2_ON();
    break;
  case RUNNING:
    switch(Check_Timer){
    case RUNNING:
      Timer_A2_Running = OFF;
      Check_Timer = RESET;
      break;
    default: 
      RIGHT_REVERSE_SPEED = Right_Speed;
      LEFT_REVERSE_SPEED = Left_Speed;
      break;
    }
    break;
  case OFF:
    Timer_A2_OFF(Time);
      break;
  case STOP:
    Timer_A2_STOP();
    break;
  default: break;
  }
}
//------------------------------------------------------------------------------
//Turn_Right functions purpose is to allow the car to drive turn right. Function 
//takes in integer time to turn and returns nothing.
//------------------------------------------------------------------------------
void Turn_Right(int Time){
  switch(Timer_A2_Running){
  case ON:
    Timer_A2_ON();
    break;
  case RUNNING:
    switch(Check_Timer){
    case RUNNING:
      Timer_A2_Running = OFF;
      Check_Timer = RESET;
      break;
    default: 
      RIGHT_REVERSE_SPEED = Right_Speed;
      LEFT_FORWARD_SPEED = Left_Speed;
      break;
    }
    break;
  case OFF:
    Timer_A2_OFF(Time);
      break;
  case STOP:
    Timer_A2_STOP();
    break;
  default: break;
  }
}
//------------------------------------------------------------------------------
//Turn_Left functions purpose is to allow the car to drive turn left. Function 
//takes in integer time to turn and returns nothing.
//------------------------------------------------------------------------------
void Turn_Left(int Time){
  switch(Timer_A2_Running){
  case ON:
    Timer_A2_ON();
    break;
  case RUNNING:
    switch(Check_Timer){
    case RUNNING:
      Timer_A2_Running = OFF;
      Check_Timer = RESET;
      break;
    default: 
      RIGHT_FORWARD_SPEED = Right_Speed;
      LEFT_REVERSE_SPEED = Left_Speed;
      break;
    }
    break;
  case OFF:
    Timer_A2_OFF(Time);
      break;
  case STOP:
    Timer_A2_STOP();
    break;
  default: break;
  }
}
//------------------------------------------------------------------------------
//Hault_Movement functions purpose is to allow the car to stop moving. Function 
//takes in nothing and returns nothing.
//------------------------------------------------------------------------------
void Hault_Movement(void){
  RIGHT_FORWARD_SPEED = WHEEL_OFF;
  LEFT_FORWARD_SPEED = WHEEL_OFF;
  RIGHT_REVERSE_SPEED = WHEEL_OFF;
  LEFT_REVERSE_SPEED = WHEEL_OFF;
}
//------------------------------------------------------------------------------
//Change_Wheel_Speed functions purpose is to allow the car to change independent
//or both wheel speed. Function takes in char describing what wheel or both wheels
// and the speed change requested to change to, function returns nothing.
//------------------------------------------------------------------------------
void Change_Wheel_Speed(char Wheel, char Speed_Change){
  switch(Wheel){
  case RIGHT_WHEEL:
    switch(Speed_Change){
    case SPEED_INCREASE:
      if(Right_Speed + SPEED_SHIFT <= MAX_SPEED) Right_Speed += SPEED_SHIFT;
      break;
    case SPEED_DECREASE:
      if(Right_Speed - SPEED_SHIFT >= MIN_SPEED) Right_Speed -= SPEED_SHIFT;
      break;
      case TURBO_INCREASE:
      if(Right_Speed + TURBO_SHIFT <= MAX_SPEED) Right_Speed += TURBO_SHIFT;
      break;
    case TURBO_DECREASE:
      if(Right_Speed - TURBO_SHIFT >= MIN_SPEED) Right_Speed -= TURBO_SHIFT;
      break;
    case RESET_SPEED:
      Right_Speed = FIFTEEN_SPEED;
      break;
    default:
      memset(IOT_Transmit[IOT_Row], CHAR_NULL, SMALL_RING_SIZE);
      Command_Recieved = READ_COMMAND;
      break;
    }
    break;
  case LEFT_WHEEL:
    switch(Speed_Change){
    case SPEED_INCREASE:
      if(Left_Speed + SPEED_SHIFT <= MAX_SPEED) Left_Speed += SPEED_SHIFT;
      break;
    case SPEED_DECREASE:
      if(Left_Speed - SPEED_SHIFT >= MIN_SPEED) Left_Speed -= SPEED_SHIFT;
      break;
    case TURBO_INCREASE:
      if(Left_Speed + TURBO_SHIFT <= MAX_SPEED) Left_Speed += TURBO_SHIFT;
      break;
    case TURBO_DECREASE:
      if(Left_Speed - TURBO_SHIFT >= MIN_SPEED) Left_Speed -= TURBO_SHIFT;
      break;
    case RESET_SPEED:
      Left_Speed = FIFTEEN_SPEED;
      break;
    default:
      memset(IOT_Transmit[IOT_Row], CHAR_NULL, SMALL_RING_SIZE);
      Command_Recieved = READ_COMMAND; 
      break;
    }
    break;
  case BOTH_WHEELS:
    switch(Speed_Change){
    case SPEED_INCREASE:
      if(Left_Speed + SPEED_SHIFT <= MAX_SPEED && Right_Speed + SPEED_SHIFT <= MAX_SPEED){
        Left_Speed += SPEED_SHIFT;
        Right_Speed += SPEED_SHIFT;
      }
      break;
    case SPEED_DECREASE:
      if(Left_Speed - SPEED_SHIFT >= MIN_SPEED && Right_Speed - SPEED_SHIFT >= MIN_SPEED){
        Left_Speed -= SPEED_SHIFT;
        Right_Speed -= SPEED_SHIFT;
      }
      case TURBO_INCREASE:
      if(Left_Speed + TURBO_SHIFT <= MAX_SPEED && Right_Speed + TURBO_SHIFT <= MAX_SPEED){
        Left_Speed += TURBO_SHIFT;
        Right_Speed += TURBO_SHIFT;
      }
      break;
    case TURBO_DECREASE:
      if(Left_Speed - TURBO_SHIFT >= MIN_SPEED && Right_Speed - TURBO_SHIFT >= MIN_SPEED){
        Left_Speed -= TURBO_SHIFT;
        Right_Speed -= TURBO_SHIFT;
      }
      break;
    case RESET_SPEED:
      Left_Speed = TWELVE_SPEED;
      Right_Speed = TWELVE_SPEED;
      break;
      break;
    default:
      memset(IOT_Transmit[IOT_Row], CHAR_NULL, SMALL_RING_SIZE);
      Command_Recieved = READ_COMMAND; 
      break;
    }
    break;
  default: 
    memset(IOT_Transmit[IOT_Row], CHAR_NULL, SMALL_RING_SIZE);
    Command_Recieved = READ_COMMAND;
    break;
  }
  switch(Timer_A2_Running){
  case RUNNING:
    break;
  default:
    IOT_Row_Write = UPPER_ROW;
    break;
  }
  memset(IOT_Transmit[IOT_Row], CHAR_NULL, SMALL_RING_SIZE);
  Command_Recieved = READ_COMMAND;
}
//------------------------------------------------------------------------------
//Timer_A2_ON functions purpose is to change the operation if timer A2 is currently 
//ON. Function takes in nothing and returns nothing.
//------------------------------------------------------------------------------
void Timer_A2_ON(void){
  Hault_Movement();
  Timer_A2_Running = RUNNING;
}
//------------------------------------------------------------------------------
//Timer_A2_OFF functions purpose is to change the operation if timer A2 is currently 
//OFF. Function takes in nothing and returns nothing.
//------------------------------------------------------------------------------
void Timer_A2_OFF(int Time){
  Command_Recieved = RUN_COMMAND;
  Timer_A2_Running = ON;
  Timer_A2_Time = Time;
  Timer_A2_Interrupted = RESET;
  TA0CCR2 += TA0CCR2_INTERVAL;
  TA0CCTL2 |= CCIE;
}
//------------------------------------------------------------------------------
//Timer_A2_STOP functions purpose is to change the operation if timer A2 is currently 
//running to STOP. Function takes in nothing and returns nothing.
//------------------------------------------------------------------------------
void Timer_A2_STOP(void){
  IOT_Row_Write = UPPER_ROW;
  memset(IOT_Transmit[IOT_Row], CHAR_NULL, SMALL_RING_SIZE);
  Hault_Movement();
  Command_Recieved = READ_COMMAND;
  Timer_A2_Running = OFF;
}

     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     