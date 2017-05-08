#ifndef LCD_MACRO_H
#define LCD_MACRO_H

  #ifndef LCD
    #define LCD lcd
  #endif  // #ifndef LCD

  #define lcdSetc( s, r ) LCD.setCursor( s, r )
  #define lcdPrint(...) LCD.print( __VA_ARGS__ )
  #define lcdPrintS(...) LCD.print( F( __VA_ARGS__ ))
  #define lcdPrint2( str, ... ) lcdPrintS( str ); lcdPrint( __VA_ARGS__ )
  #define lcdSetcPrint( s, r, ... ) lcdSetc( s, r ); lcdPrint( __VA_ARGS__ )
  #define lcdSetcPrintS( s, r, str ) lcdSetc( s, r ); lcdPrintS( str )
  #define lcdSetcPrint2( s, r, str, ... ) lcdSetc( s, r ); lcdPrintS( str ); lcdPrint( __VA_ARGS__ )
  #define lcdCleanChars( r, s ) lcdSetc( 0, r ); for ( uint8_t i = 0; i < ; i++ ) lcdPrint( " " )

#endif  // #ifndef LCD_MACRO_H
