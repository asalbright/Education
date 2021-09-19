//Andrew Albright
//ECE 306, Homework_03
//macros.h
//------------------------------------------------------------------------------

#include  "msp430.h"
#include  "functions.h"
#include <string.h>
//------------------------------------------------------------------------------


#define ALWAYS                  (1)
#define RESET_STATE             (0)
#define RESET                   (0)
#define RED_LED                 (0x01) // RED LED 0
#define GRN_LED                 (0x02) // GREEN LED 1
#define PORTS                   (0x00) // PORTS
#define PWM_MODE                (0x01) // PWM_MODE
#define GP_IO                   (0x00) // SET PIN TO GP I/O MODE
#define FUNCTION_0              (0X00) // SET PIN TO FUNCTION MODE (ZERO)
#define FUNCTION_1              (0X01) // SET PIN TO FUNCTION MODE (ONE) 
#define DIR_OUT                 (0x00) // SET PIN DIRECTION TO OUT
#define DIR_IN                  (0X00) // SET PIN DIRECTION TO IN
#define SET_HIGH                (0x01) // SET PIN TO HIGH
#define SET_LOW                 (0x00) // SET PIN TO LOW
#define OFF                     (0)
#define ON                      (1)
#define NONE                    (0)


//Homework 03
#define CONST_ZERO              (0)
#define CONST_ONE               (1)
#define CONST_TWO               (2)
#define CONST_THREE             (3)
#define CONST_FOUR              (4)
#define CONST_FIVE              (5)
#define CONST_SIX               (6)
#define CONST_SEVEN             (7)
#define CONST_EIGHT             (8)
#define CONST_NINE              (9)
#define CONST_TEN               (10)
#define CONST_ELEVEN            (11)
#define CONST_TWELVE            (12)
#define CONST_THIRTEEN          (13)
#define CONST_FOURTEEN          (14)
#define CONST_FIFTEEN           (15)
#define CONST_SIXTEEN           (16)
#define CONST_TWENTY            (20)
#define CONST_TWENTYFIVE        (25)
#define CONST_THIRTY            (30)

#define disp_line_0             (0)
#define disp_line_1             (1)
#define disp_line_2             (2)
#define disp_line_3             (3)
#define disp_line_4             (4)
#define disp_line_5             (5)
#define disp_line_6             (6)
#define disp_line_7             (7)
#define disp_line_8             (8)
#define disp_line_9             (9)
#define disp_line_10            (10)
#define disp_line_11            (11)

#define disp_column_0             (0)
#define disp_column_1             (1)
#define disp_column_2             (2)
#define disp_column_3             (3)
#define disp_column_4             (4)
#define disp_column_5             (5)
#define disp_column_6             (6)
#define disp_column_7             (7)
#define disp_column_8             (8)
#define disp_column_9             (9)
#define disp_column_10            (10)
#define disp_column_11            (11)

#define disp_0                  (0)
#define disp_1                  (1)
#define disp_2                  (2)
#define disp_3                  (3)
#define disp_4                  (4)

#define FIRST_CHARACTER         (0)
#define LAST_CHARACTER          (11)

//Homework 04
#define USE_L_REVERSE           (0x00)
#define USE_SMCLK               (0x01)

//Homework 06
#define TA0CCR0_INTERVAL        (10000) //20ms
#define TA0CCR1_INTERVAL        (50000)  //100ms
#define TA0CCR2_INTERVAL        (5000)  //10ms
#define BACKLITE_BLINK_TIME     (25)
#define RESET_TIME_SEQUENCE     (150)
#define CCR1_INTERRUPT          (2)
#define CCR2_INTERRUPT          (4)
#define OVERFLOW_INTERRUPT      (14)
#define BUTTON_1                (1)
#define BUTTON_2                (2)

//Project 06
#define Black_Detected          (Black_Line)
#define White_Detected          (White_Line)
#define WHITE_LINE              ((White_Line + 100))
#define Line_Found            ((Black_Line + White_Line) / 2)
#define Less_Than_Thousand      (999)
#define Less_Than_Hundred       (99)
#define Less_Than_Ten           (9)
#define CONST_THOUSAND         (1000)
#define CONST_HUNDRED           (100)
#define Char_Hex_Offset         (0x30)
#define P8OUT_HIGH              (0x0F)

//Project 07
#define ONE_SEC                 (1)
#define TWO_SEC                 (2)
#define THREE_SEC               (3)   
#define FIVE_SEC                (5)
#define TEN_SEC                 (10)
#define FIFTEEN_SEC             (15)
#define SEVENTEEN_SEC           (17)
#define TWENTY_SEC              (20)

#define ONE_SECOND              (50)
#define TENTH_SECOND            (5)
#define HALF_SECOND             (25)

#define WHEEL_PERIOD            (60000)
#define WHEEL_OFF               (0)
#define SEVEN_SPEED             (7000)
#define EIGHT_SPEED             (8000)
#define NINE_SPEED              (9000)
#define TEN_SPEED               (10000)
#define ELEVEN_SPEED            (11000)
#define TWELVE_SPEED            (12000)
#define THIRTEEN_SPEED          (13000)
#define FOURTEEN_SPEED          (14000)
#define FIFTEEN_SPEED           (15000)
#define TWENTY_SPEED            (20000)
#define MAX_SPEED               (40000)
#define MIN_SPEED               (8000)
#define SPEED_SHIFT             (1000)
#define TURBO_SHIFT             (5000)

#define LEFT_REVERSE_SPEED (TB0CCR3)
#define LEFT_FORWARD_SPEED (TB0CCR4)
#define RIGHT_REVERSE_SPEED (TB0CCR5)
#define RIGHT_FORWARD_SPEED (TB0CCR6)

#define RESET_TIMER             (5)
#define FIND_THE_LINE           ('F')
#define ALIGN_TO_LINE           ('G')
#define FOLLOW_THE_LINE         ('L')
#define ALIGN_PERPED_LINE       ('P')
#define DRIVE_FORWARD           ('E')
#define WAIT                    (35)
#define FINISHED                (40)

//Homework 08
#define CHAR_ZERO               ('0')
#define EIGHT_PAGE_MENU         (500)
#define TWO_PAGE_MENU                (2000)
#define CHAR_NULL               (0x00)
#define MCTLW_HIGH              (0x4A11)
#define MCTLW_LOW               (0x5551)
#define HEX_EIGHT               (0x08)
#define CARREAGE_RETURN         (0x0D)
#define LINE_FEED               (0x0A)
#define MESSAGE_LENGTH          (10)

#define MESSAGE_CHAR_ZERO       (0)
#define MESSAGE_CHAR_ONE        (1)
#define MESSAGE_CHAR_TWO        (2)
#define MESSAGE_CHAR_THREE      (3)
#define MESSAGE_CHAR_FOUR       (4)
#define MESSAGE_CHAR_FIVE       (5)
#define MESSAGE_CHAR_SIX        (6)
#define MESSAGE_CHAR_SEVEN      (7)
#define MESSAGE_CHAR_EIGHT      (8)
#define MESSAGE_CHAR_NINE       (9)
#define MESSAGE_CHAR_TEN        (10)
#define MESSAGE_CHAR_ELEVEN     (11)
#define MESSAGE_CHAR_TWELVE     (12)

#define FAST_BAUD               ('F')
#define SLOW_BAUD               ('S')
#define YES                     ('Y')
#define NO                      ('N')
#define TRANSMIT                ('T')
#define RECIEVE                 ('R')
#define WAITING                 ('W')
#define BEGINNING               (0)
#define SMALL_RING_SIZE         (16)

//project 09
#define START_TRANSMIT          ('^')
#define END_TRANSMIT            ('!')
#define FOUND_IP                ('=')
#define COPY_IP                 ('C')
#define END_IP                  (' ')
#define IOT_CONNECTED           ('A')
#define FIND_IP_ADDRESS         ('F')

#define READ_COMMAND            ('D')
#define RUN_COMMAND             ('R')
#define IP_ADDRESS              (10.123.169.174)
#define ACTIVE                  ('a')
#define INACTIVE                ('i')
#define STOP                    ('S')
#define UPPER_ROW               (0)
#define LOWER_ROW               (1)
#define COMMAND                 (IOT_Read_Index + 6)
#define RUN_TIME                (IOT_Read_Index + 7)
#define WHEEL_TO_CHANGE         (IOT_Read_Index + 7)
#define SPEED_CHANGE            (IOT_Read_Index + 8)
#define MOVE_FORWARD            ('F')
#define MOVE_BACKWARD           ('B')
#define TURN_RIGHT              ('R')
#define TURN_LEFT               ('L')
#define CHANGE_SPEED            ('S')
#define STOP_WHEELS             ('H')
#define AUTO_MODE               ('A')
#define IOT_MODE                ('I')
#define RUNNING                 ('H')
#define RIGHT_WHEEL             ('R')
#define LEFT_WHEEL              ('L')
#define BOTH_WHEELS             ('B')
#define SPEED_INCREASE          ('i')
#define SPEED_DECREASE          ('d')
#define TURBO_INCREASE          ('I')
#define TURBO_DECREASE          ('D')
#define RESET_SPEED             ('R')

#define CHAR_ZERO               ('0')
#define CHAR_ONE                ('1')
#define CHAR_TWO                ('2')
#define CHAR_THREE              ('3')
#define CHAR_FOUR               ('4')
#define CHAR_FIVE               ('5')
#define CHAR_SIX                ('6')
#define CHAR_SEVEN              ('7')
#define CHAR_EIGHT              ('8')
#define CHAR_NINE               ('9')

#define A2_TENTH_SECOND         (10)
#define A2_1_SECOND             (100)
#define A2_2_SECOND             (200)
#define A2_30_SECOND            (3000)
#define A2_2_MIN                (12000)
#define A0_1_SECOND             (50)
#define A0_2TENTH_SECOND         (10)

#define MAIN_MENU               ('M')
#define IOT_MENU                ('I')
#define IR_MENU                 ('R')
#define ARROW                   ('<')
#define FIND_WHITE              ('W')
#define FIND_BLACK              ('B')


//ports
//------------------------------------------------------------------------------

//port_1
#define P1_0_LED1               (0x01)
#define P1_1_LED2               (0x02)
#define V_THUMB                 (0x04)
#define TEST_PROBE              (0x08)
#define V_DETECT_R              (0x10)
#define V_DETECT_L              (0x20)
#define SD_MOSI                 (0x40)
#define SD_MISO                 (0x80)
 
//------------------------------------------------------------------------------

//port_2
#define UCA0TXD                 (0x01)   
#define UCA0RXD                 (0x02)
#define SD_SPICLK               (0x04)
#define P2_3                    (0x08)
#define P2_4                    (0x10)
#define UCA1TXD                 (0x20)
#define UCA1RXD                 (0x40)
#define P2_7                    (0x80)

//------------------------------------------------------------------------------

//port_3
#define IOT_RESET               (0x01)
#define IOT_PROG_MODE           (0x02)
#define IOT_LINK                (0x04)
#define IOT_PROG_SEL            (0x08)
#define L_REVERSE               (0x10)
#define L_FORWARD               (0x20)
#define R_REVERSE               (0x40)
#define R_FORWARD               (0x80)

//------------------------------------------------------------------------------

//port_4
#define SD_CS                   (0x01) 
#define J4_31                   (0x02)
#define J4_32                   (0x04)
#define J4_33                   (0x08)
#define UCB1_CS_LCD             (0x10)
#define P4_4                    (0x20)
#define P4_5                    (0x40)
#define J3_29                   (0x80)

//------------------------------------------------------------------------------

//port_5
#define SPI_UCB1SIMO            (0x01) // UCB1SIMO 
#define SPI_UCB1SOMI            (0x02) // UCB1SOMI 
#define SPI_UCB1CLK             (0x04) // SPI mode - clock output—UCB1CLK 
#define RESET_LCD               (0x08) // LCD Reset 
#define P5_4_UNUSED             (0x10) // UNUSED 
#define BUTTON2                 (0x20) // Button 2 
#define BUTTON1                 (0x40) // Button 1 
#define LCD_BACKLITE            (0x80) // LCD Backlite
//------------------------------------------------------------------------------

//port_6
#define UCA3TXD                 (0x01) 
#define UCA3RXD                 (0x02)
#define J1_5                    (0x04)
#define MAG_INT                 (0x08)
#define P6_4                    (0x10)
#define P6_5                    (0x20)
#define P6_6                    (0x40)
#define P6_7                    (0x80)

//------------------------------------------------------------------------------

//port_7
#define I2CSDA                  (0x01)
#define I2CSCL                  (0x02)
#define SD_DETECT               (0x04)
#define J4_36                   (0x08)
#define P7_4                    (0x10)
#define P7_5                    (0x20)
#define P7_6                    (0x40)
#define P7_7                    (0x80)

//------------------------------------------------------------------------------

//port_8
#define IR_LED                  (0x01)
#define OPT_INT                 (0x02)
#define TMP_INT                 (0x04)
#define INT2                    (0x08)

//------------------------------------------------------------------------------

//port_j
#define PJ_0                    (0x01) 
#define PJ_1                    (0x02)
#define PJ_2                    (0x04)
#define PJ_3                    (0x08)
#define LFXIN                   (0x10)
#define LFXOUT                  (0x20)
#define HFXIN                   (0x40)
#define HFXOUT                  (0x80)


//functions
void out_character(char character);
void Check_Command_Buffer(void);
void Run_Command(void);
int Set_Run_Time(char);
void Change_Wheel_Speed(char, char);
void Timer_A2_ON(void);
void Timer_A2_OFF(int);
void Timer_A2_STOP(void);

void Find_Line(void);
void Align_Line(void);
void Follow_Line(int);
void Align_Ninty_To_Line(int);
void Move_Forward(int);
void Move_Backward(int);
void Turn_Right(int);
void Turn_Left(int);
void Hault_Movement(void);
