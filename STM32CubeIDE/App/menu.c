//=============================================================================
// Daniel J. Greenhoe
//=============================================================================
#include <stdio.h>
#include "io.h"
#include "main.h"
#include "LEDs.h"
#include "TxRx.h"
#include "menu.h"
extern UART_HandleTypeDef huart3;
static char* Number_to_BinaryString( const int Number, char *buf );

//-----------------------------------------------------------------------------
// !\brief Display menu options
//-----------------------------------------------------------------------------
int Menu_Options(void)
{
  printf("Menu Options:\r\n");
  printf("  r: Toggle Red LED     ");   printf("  g: Toggle Green LED\r\n"  );
  printf("  y: Toggle Yellow LED  ");   printf("\r\n"                       );
  printf("  0: Toggle LED 0       ");   printf("  4: Toggle LED 4\r\n"      );
  printf("  1: Toggle LED 1       ");   printf("  5: Toggle LED 5\r\n"      );
  printf("  2: Toggle LED 2       ");   printf("  6: Toggle LED 6\r\n"      );
  printf("  3: Toggle LED 3       ");   printf("  7: Toggle LED 7\r\n"      );
  printf("  ): Toggle Tx 0        ");   printf("  $: Toggle Tx 4\r\n"       );
  printf("  !: Toggle Tx 1        ");   printf("  %%: Toggle Tx 5\r\n"      );
  printf("  @: Toggle Tx 2        ");   printf("  ^: Toggle Tx 6\r\n"       );
  printf("  #: Toggle Tx 3        ");   printf("  &: Toggle Tx 7\r\n"       );
  printf("  N: All Tx ON          ");   printf("  F: All Tx OFF\r\n"        );
  printf("  R: Read Rx & Tx Values");   printf("\r\n"                       );
  return 0;
}

//-----------------------------------------------------------------------------
//! \brief Display menu options
//-----------------------------------------------------------------------------
int Menu_Processing( const uint8_t oneChar )
{
  char buf[80];
  int  RxValue, TxValue;
  switch( oneChar )
  {
    case 'M':                                    Menu_Options()  ;  break;
    case 'r':  printf("Toggle Red LED\r\n"    ); LED_Red_Toggle();  break;
    case 'g':  printf("Toggle Green LED\r\n"  ); LED_Grn_Toggle();  break;
    case 'y':  printf("Toggle Yellow LED\r\n" ); LED_Ylw_Toggle();  break;
    case '`':
    case '0':  printf("Toggle LED 0\r\n"      ); LED_0_Toggle()  ;  break;
    case '1':  printf("Toggle LED 1\r\n"      ); LED_1_Toggle()  ;  break;
    case '2':  printf("Toggle LED 2\r\n"      ); LED_2_Toggle()  ;  break;
    case '3':  printf("Toggle LED 3\r\n"      ); LED_3_Toggle()  ;  break;
    case '4':  printf("Toggle LED 4\r\n"      ); LED_4_Toggle()  ;  break;
    case '5':  printf("Toggle LED 5\r\n"      ); LED_5_Toggle()  ;  break;
    case '6':  printf("Toggle LED 6\r\n"      ); LED_6_Toggle()  ;  break;
    case '7':  printf("Toggle LED 7\r\n"      ); LED_7_Toggle()  ;  break;
    case '~':
    case ')':  printf("Toggle Tx 0\r\n"       ); Tx_Toggle( 0 )  ;  break;
    case '!':  printf("Toggle Tx 1\r\n"       ); Tx_Toggle( 1 )  ;  break;
    case '@':  printf("Toggle Tx 2\r\n"       ); Tx_Toggle( 2 )  ;  break;
    case '#':  printf("Toggle Tx 3\r\n"       ); Tx_Toggle( 3 )  ;  break;
    case '$':  printf("Toggle Tx 4\r\n"       ); Tx_Toggle( 4 )  ;  break;
    case '%':  printf("Toggle Tx 5\r\n"       ); Tx_Toggle( 5 )  ;  break;
    case '^':  printf("Toggle Tx 6\r\n"       ); Tx_Toggle( 6 )  ;  break;
    case '&':  printf("Toggle Tx 7\r\n"       ); Tx_Toggle( 7 )  ;  break;
    case 'n':  printf("All Tx ON\r\n"         ); Tx_SetHighAll() ;  break;
    case 'N':  printf("All Tx ON\r\n"         ); Tx_SetHighAll() ;  break;
    case 'f':  printf("All Tx OFF\r\n"        ); Tx_SetLowAll()  ;  break;
    case 'F':  printf("All Tx OFF\r\n"        ); Tx_SetLowAll()  ;  break;
    case 'R':
    case ' ':
      RxValue = Rx_ReadStateAll();
      TxValue = Tx_ReadStateAll();
      printf("Rx: %s = 0x%02X   " , Number_to_BinaryString(RxValue, buf), RxValue );
      printf("Tx: %s = 0x%02X\r\n", Number_to_BinaryString(TxValue, buf), TxValue );
      break;
    default :  printf("Char = %02X = %d ('%c')\r\n", oneChar, oneChar, oneChar ); break;
  }
  return 0;
}

//-----------------------------------------------------------------------------
//! \brief Convert 8 bit number to binary string.
//-----------------------------------------------------------------------------
static char* Number_to_BinaryString( const int Number, char *buf )
{
  int Mask = 0x0080;
  for( int i=0; i<=8; i++ )
  {
    buf[i] = ( Number & Mask )? '1' : '0';
    Mask >>= 1;
    if( i==3 )
    {
      i++;
      buf[i] = '_';
    }
  }
  buf[9] = '\0';
  return buf;
}