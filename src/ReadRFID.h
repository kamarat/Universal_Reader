#ifndef READ_RFID_H
#define READ_RFID_H

#include <SPI.h>
#include <MFRC522Extended.h>
#include "global.h"

/*== GLOBALNE PREMENNE ==
 *=======================
 */
/*== Deklaracia konstant ==
 */
const uint8_t SS_PIN = 10;
const uint8_t RST_PIN = 9;

/*== Deklaracia premennych ==
 */
MFRC522 rfid( SS_PIN, RST_PIN );
//MFRC522::MIFARE_Key key;
static uint8_t startRFID = 0;

/*== FUNKCIE ==
 *=============
 */
/*== Deklaracia funkcii ==
 */
const char * getTypeName( byte sak );
//void printHex(byte *buffer, byte bufferSize);
//void printDec(byte *buffer, byte bufferSize);

/*== Definicia funkcii ==
 */
/*******************************************************************************
 *    Function: readRFID
 * Description: nacitanie informacii z karty RFID 13.56 MHz
 *   Parameter: [OUT] struct Message * m - riadky pre zobrazenie na LCD
 *      Return: uint8_t 0 - karta nacitana
 *                      1 - karta nenacitana
 ******************************************************************************/
uint8_t readRFID( struct Message * m )
{
  if ( !startRFID ) {
    SPI.begin();      // Init SPI bus
    rfid.PCD_Init();  // Init MFRC522
    startRFID = 1;

    #if DEBUG >= 2
      DPRINTLN_POINT( "" );
    #endif
  }

  // Look for new cards
  if ( rfid.PICC_IsNewCardPresent() ) {
    // Verify if the NUID has been readed
    if ( rfid.PICC_ReadCardSerial() ) {
      // Line 1
      sprintf( m->line1, "CARD:%s%c", getTypeName( rfid.uid.sak ), '\0' );

      // Line 2
      char * ptr = m->line2;
      ptr += sprintf( ptr, "HEX:" );
      for ( uint8_t i = 0; i < rfid.uid.size; i++ )
        ptr += sprintf( ptr, "%02X", rfid.uid.uidByte[ i ] );
      *ptr = '\0';

      // Line 3
      uint64ToChar( m->line4, binToUint64( rfid.uid.uidByte, rfid.uid.size ));
      sprintf( m->line3, "DEC:%s", m->line4 );

      // Line 4
      sprintf( m->line4, "%c", '\0' );

      rfid.PICC_HaltA();        // halt PICC
      rfid.PCD_StopCrypto1();   // stop encryption on PCD

      #if DEBUG >= 1
        DPRINTLN( m->line2 );
      #endif

      return 0;
    }
  }
  return 1;
}

/*******************************************************************************
 *    Function: getTypeName
 * Description: urcenie cipu podla kodu
 *   Parameter: [IN] byte sak - kod / typ karty
 *      Return: char * - retazec s popisom cipu / karty
 ******************************************************************************/
const char * getTypeName( byte sak )
{
	switch ( sak ) {
    case 0x04: return "UID not complete"; // UID not complete
    case 0x09: return "MIFARE Mini 320";
    case 0x08: return "MIFARE 1KB";
    case 0x18: return "MIFARE 4KB";
    case 0x00: return "MIFARE Ultral";
    case 0x10: return "MIFARE Plus 2K";
    case 0x11: return "MIFARE Plus 4K";
    case 0x01: return "MIFARE TNP3XXX";
    case 0x20: return "ISO/IEC 14443-4";
    case 0x40: return "ISO/IEC 18092 NFC";
    default: return "Unknown type";
  }
}

#endif  // #ifndef READ_RFID_H
