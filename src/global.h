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
uint64_t binToUint64( uint8_t * arr, uint8_t pocet )
{
  uint64_t n = 0;
  for ( uint8_t i = 0; i < pocet; i++ ) {
    n |= ( uint64_t )arr[ i ] << ((( pocet - 1 ) << 3 ) - ( i << 3 ));
  }
  return n;
}

void uint64ToChar( char * line, uint64_t n )
{
  uint64_t temp = n;
  uint8_t strLen = 1;

  while ( temp ) {
    temp = temp / 10;
    strLen++;
  }

  //if ( size >= strLen ) {
    *( line + --strLen ) = '\0';
    temp = n;

    do {
      *( line + strLen - 1) = ( temp %  10 ) + '0';
      temp = temp / 10;
    } while ( strLen--);
  //}
}

#endif  // #ifndef CONFIG_H
