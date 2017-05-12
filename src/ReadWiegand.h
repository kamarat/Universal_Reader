#ifndef READ_WIEGAND_H
#define READ_WIEGAND_H

#include <Wiegand.hpp>
#include "global.h"

/*== GLOBALNE PREMENNE ==
 *=======================
 */
/*== Deklaracia konstant ==
 */
const uint8_t DATA0 = 5;
const uint8_t DATA1 = 6;

/*== Deklaracia premennych ==
 */
// D0 - pin 24, D1 - pin 25, bez kontroly parity - 0
WIEGAND wg( DATA0, DATA1, 0 );
static uint8_t startWG = 0;

uint8_t readWiegand( struct Message * m )
{
  if ( !startWG ) {
    wg.begin();
    startWG = 1;

    #if DEBUG >= 2
      DPRINTLN_POINT( "" );
    #endif
  }

  if( !wg.available() )
  {
    uint8_t type = wg.getWiegandType();
    char code[ 14 ];
    // Line 1
    sprintf( m->line1, "Wiegand: %d%c", type, '\0' );

    // Line 2
    wg.getCodeHex( code, 14 );
    sprintf( m->line2, "HEX:%s", code );

    // Line 3
    wg.getCodeDec( code, 14 );
    sprintf( m->line3, "DEC:%s", code );

    // Line 4
    m->line4[ 0 ] = '\0';

    #if DEBUG >= 1
      DPRINTLN( m->line2 );
    #endif

    return 0;
  }
  return 1;
}

#endif  // #ifndef READ_WIEGAND_H
