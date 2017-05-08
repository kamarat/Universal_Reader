/*== Universal Reader ==
 *======================
 *
 * Universal_Reader.ino
 *
 * Program cita a vypisuje informacie z roznych zdrojov
 *
 * @author: kamarat
 * @date:   april 2017
 * @version: [0.1.0-alfa] - 2017-04
 *
 * kamarat (cleft) 2017
 */

/*== ZAPOJENIE PINOV ==
 *=====================
 *
 * ARDUINO --- PERIFERIE
 *
 * D 22 --- kontakt TM citacky 1 iButton
 * Rezistor 2k2 - medzi D22 a 5V
 *
 * D 24 --- Wiegand DATA0
 * D 25 --- Wiegand DATA1
 */

/*== KNIZNICE A SUBORY ==
 *=======================
 */
#define DEBUG 1  // Definicia odladovania a vypisov

#include "headers.h"

/*== GLOBALNE PREMENNE ==
 *=======================
 */
/*== Deklaracia konstant ==
 */
const uint16_t INIT_TIME = 5000;    // in ms
const uint16_t TASKER_TIME = 1000;  // in ms

/*== Deklaracia premennych ==
 */
LiquidCrystal_I2C lcd( 0x27, 20, 4 );  // nastavenie adresy LCD a rozlisenia displeja

TaskCallback call[] = {
  readOneWire,
  readWiegand,
  readRFID
};

/*== Deklaracia funkcii ==
 */

/*== INICIALIZACIA ==
 *===================
 */
void setup()
{
  #if DEBUG >= 1
    Serial.begin( 57600 );  // Inicializacia serioveho vystupu
    DPRINTSLN( "Start inicializacie." );
  #endif

  lcd.init();
  lcd.backlight();
  lcdSetcPrintS( 0, 0, "Univerzalna citacka" );
  lcdSetcPrintS( 0, 1, "Verzia: 0.1.0-alfa" );
  lcdSetcPrintS( 0, 2, "Inicializacia" );
  lcdSetc( 0, 3 );
  for ( uint8_t i = 0; i < 20; i++ ) {
    lcdPrintS( "." );
    delay( INIT_TIME / 20 );
  }
  lcdSetcPrintS( 18, 3, "OK" );

  #if DEBUG >= 1
    DPRINTSLN( "Inicializacia ukoncena." );
  #endif
}

/*== HLAVNY PROGRAM ==
 *====================
 */
void loop()
{
  for ( uint8_t i = 0; i < sizeof( call ) / sizeof( call[ 0 ] ); i++ ) {
    #if DEBUG >= 2
      DPRINTLN2( "i = ", i );
    #endif

    if ( !taskInterval( call[ i ], 100, &msg )) {
      lcd.clear();
      lcdSetcPrint( 0, 0, msg.line1 );
      lcdSetcPrint( 0, 1, msg.line2 );
      lcdSetcPrint( 0, 2, msg.line3 );
      lcdSetcPrint( 0, 3, msg.line4 );
    }
  }
}
