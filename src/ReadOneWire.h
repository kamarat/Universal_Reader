#ifndef READ_ONE_WIRE_H
#define READ_ONE_WIRE_H

#include <OneWire.h>
#include "FamilyCode.h"
#include "global.h"

/*== GLOBALNE PREMENNE ==
 *=======================
 */
/*== Deklaracia konstant ==
 */
const uint8_t IBUTTON_CITACKA = 4;

/*== Deklaracia premennych ==
 */
OneWire citacka ( IBUTTON_CITACKA );

uint8_t unikatnyROMKod[ 8 ] = {0};  // adresa + identifikator zariadenia - 8 bajtove pole

enum vysledkyNacitania {
  OK = 0,
  CRC_INVALID,
  NO_IBUTTON
} vysledokNacitania;

uint32_t charToUint32( uint8_t * arr, uint8_t pocet );

uint8_t readOneWire( struct Message * m )
{
  #if DEBUG >= 2
    DPRINTLN_POINT( "" );
  #endif

  /* Vyhladanie aktivneho kluca na citacke. Ak je kluc najdeny, pole unikatnyROMKod je naplnene
  * jedinecnym cislom a metoda search vrati TRUE. Ak kluc nie je najdeny, metoda vrati FALSE.
  */
  if ( citacka.search( unikatnyROMKod )) {
    // Vypocet a kontrola CRC nad polom unikatnyROMKod.
    if ( OneWire::crc8( unikatnyROMKod, 7 ) == unikatnyROMKod[ 7 ]) {
      // Line 1
      sprintf( m->line1, "iButton: %s%c", chips[ unikatnyROMKod[ 0 ] - 1 ].part, '\0' );

      // Line 2
      char * ptr = m->line2;
      ptr += sprintf( ptr, "HEX:" );
      for ( uint8_t i = 0; i < 8; i++ )
        ptr += sprintf( ptr, "%02X", unikatnyROMKod[ i ] );
      *ptr = '\0';

      // Line 3
      sprintf( m->line3, "W26:%lu%c", charToUint32( unikatnyROMKod + 1, 3 ), '\0' );

      // Line 4
      sprintf( m->line4, "W34:%lu%c", charToUint32( unikatnyROMKod + 1, 4 ), '\0' );

      return 0;
    }
    // Zacatie noveho vyhladavania kluca. Dalsie pouzitie search vrati udaje o dalsom kluci.
    citacka.reset_search();
  }
  return 1;
} // uint8_t readOneWire( struct Message * m )

#endif  // #ifndef READ_ONE_WIRE_H
