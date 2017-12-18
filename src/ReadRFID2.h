#ifndef READ_RFID2_H
#define READ_RFID2_H

/* UART INTERFACE OUTPUT
 * Data Head | Length | Card Type | Card Type | BCC Check             | Data End
 * 0x02      | 0x0A   | 0x01      | SN0-SN5   | XOR check except data | 0x03
 *                                              head and data end
 */

#include <SoftwareSerial.h>
#include "global.h"

/*== GLOBALNE PREMENNE ==
 *=======================
 */
/*== Deklaracia konstant ==
 */
 const uint8_t RFID_DATA_HEAD = 0x02;
 const uint8_t RFID_DATA_END = 0x03;

/*== Deklaracia premennych ==
 */
//SoftwareSerial RFID( 2, 3 ); // RX and TX

uint8_t byteRead;       // pocitadlo precitanych bajtov
uint8_t lengthRead;     // pocet bajtov spravy z citacky
uint8_t code[ 10 ] = {0};  // pole s bajtmi kodu, 0 - typ chipu, 1-5 - kód

const char * getTypeName2( byte cardType );

uint8_t readRFID2( struct Message * m )
{
  Serial.begin( 9600 );    // start serial to RFID reader

  if ( Serial.available() > 0 ) {
    delay( 1 );
    if ( Serial.read() == RFID_DATA_HEAD ) {
      if ( Serial.available() > 0 ) {
        lengthRead = Serial.read();
        // vytvorit dynamicke pole code = malloc
        byteRead = 0;

        while ( byteRead < ( lengthRead - 2 )) {
          if ( Serial.available() > 0 ) {
            code[ byteRead ] = Serial.read();
            byteRead++;
          }
        }

        // Line 1
        sprintf( m->line1, "CARD:%s%c", getTypeName2( code[ 0 ]), '\0' );

        // Line 2
        char * ptr = m->line2;
        ptr += sprintf( ptr, "HEX:" );
        for ( uint8_t i = 1; i < 5 ; i++ )
          ptr += sprintf( ptr, "%02X", code[ i ] );
        *ptr = '\0';

        // Line 3
        //sprintf( m->line3, "DEC:%lu%c", charToUint32( code + 3, 3 ), '\0' );

        // Line 4
        //m->line4[ 0 ] = '\0';

        // Line 3
        sprintf( m->line3, "DEC:%c", '\0' );

        // Line 4
        uint64ToChar( m->line4, binToUint64( code + 1, 4 ));

        #if DEBUG >= 1
          DPRINTLN( m->line2 );
        #endif

        return 0;
      }
    }
  }
  return 1;
}

const char * getTypeName2( byte cardType )  // One of the PICC_Type enums.
{
  switch ( cardType ) {
    case 0x02:  return "EM4100";
    case 0x01:  return "MIFARE 1KB";
    case 0x03:  return "MIFARE 4KB";
    case 0x10:  return "HID Card";
    case 0x11:  return "T5567";
    case 0x20:  return "2nd Card";
    case 0x21:  return "ISO14443B";
    case 0x22:  return "FELICA";
    case 0x30:  return "15693 Label";
    case 0x50:  return "CPU Card";
    case 0x51:  return "Sector Information";
    case 0xFF:  return "Keyboard Data";
    default:  return "Unknown type";
  }
}

#endif  // #ifndef READ_RFID2_H
