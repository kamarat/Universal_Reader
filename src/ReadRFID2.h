#ifndef READ_RFID2_H
#define READ_RFID2_H

/* UART INTERFACE OUTPUT
 * Data Head | Length | Card Type | Card Type | BCC Check             | Data End
 * 0x02      | 0x0A   | 0x01      | SN0-SN5   | XOR check except data | 0x03
 *                                              head and data end
 */

//#include <SoftwareSerial.h>
#include "global.h"

/*== GLOBALNE PREMENNE ==
 *=======================
 */
/*== Deklaracia konstant ==
 */
 const uint8_t RFID_DATA_HEAD = 0x02; // startovaci bajt spravy - hlavicka
 const uint8_t RFID_DATA_END = 0x03;  // ukoncovaci bajt spravy

/*== Deklaracia premennych ==
 */
uint8_t byteRead;           // pocitadlo precitanych bajtov
uint8_t lengthRead;         // pocet bajtov spravy z citacky
uint8_t code[ 10 ] = {0};   // pole s bajtmi kodu, 0 - typ cipu, 1-5 - kód

/*== Deklaracia funkcii ==
 */
const char * getTypeName2( byte cardType );

/*******************************************************************************
 *    Function: readRFID2
 * Description: nacitanie informacii z karty RFID 125 kHz
 *   Parameter: [OUT] struct Message * m - riadky pre zobrazenie na LCD
 *      Return: uint8_t 0 - karta nacitana
 *                      1 - karta nenacitana
 ******************************************************************************/
uint8_t readRFID2( struct Message * m )
{
  if ( Serial.available() > 0 ) {
    delay( 1 );
    if ( Serial.read() == RFID_DATA_HEAD ) {
      if ( Serial.available() > 0 ) {
        lengthRead = Serial.read(); // nacitanie dlzky spravy
        // vytvorit dynamicke pole code = malloc
        byteRead = 0; // nulovanie pocitadla bajtov spravy

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
        for ( uint8_t i = 1; i <= 5 ; i++ )
          ptr += sprintf( ptr, "%02X", code[ i ] );
        *ptr = '\0';

        //Line 3
        uint64ToChar( m->line4, binToUint64( code + 1, 5 ));
        sprintf( m->line3, "DEC:%s", m->line4 );

        // Line 4
        sprintf( m->line4, "%c", '\0' );

        #if DEBUG >= 1
          DPRINTLN( m->line2 );
        #endif

        return 0;
      }
    }
  }
  return 1;
}

/*******************************************************************************
 *    Function: getTypeName2
 * Description: urcenie cipu podla kodu
 *   Parameter: [IN] byte cardType - kod / typ karty
 *      Return: char * - retazec s popisom cipu / karty
 ******************************************************************************/
const char * getTypeName2( byte cardType )
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
