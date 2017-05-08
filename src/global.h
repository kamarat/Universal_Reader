#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

struct Message {
  char line1[ 21 ];
  char line2[ 21 ];
  char line3[ 21 ];
  char line4[ 21 ];
} msg;

uint32_t charToUint32( uint8_t * arr, uint8_t pocet )
{
  uint32_t n = 0;
  switch ( pocet ) {
    case 3: {
      n = (( uint32_t )arr[ 0 ] << 16 )
        | (( uint32_t )arr[ 1 ] << 8 )
        | (( uint32_t )arr[ 2 ] );
    }break;
    case 4: {
    n = (( uint32_t )arr[ 0 ] << 24 )
      | (( uint32_t )arr[ 1 ] << 16 )
      | (( uint32_t )arr[ 2 ] << 8 )
      | (( uint32_t )arr[ 3 ]  );
    } break;
  }
  return n;
}

#endif  // #ifndef CONFIG_H
