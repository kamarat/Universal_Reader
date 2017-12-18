#ifndef HEADERS_H
#define HEADERS_H

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

#if DEBUG >= 1
  #include <DebugUtils.h>
#endif

#include "global.h"
#include "Tasker.h"
#include "lcd_macro.h"
#include "ReadOneWire.h"
#include "ReadWiegand.h"
#include "ReadRFID.h"
#include "ReadRFID2.h"


#endif  // #ifndef HEADERS_H
