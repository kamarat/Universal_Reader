#ifndef TASKER_H
#define TASKER_H

#include <Arduino.h>
//#include "config.h"

/*== Deklaracia funkcii ==
 */
typedef uint8_t ( *TaskCallback )( struct Message * );
uint8_t taskInterval( TaskCallback funcTask, uint32_t interval, struct Message * msg );

/*== Definicia funkcii ==
 */
uint8_t taskInterval( TaskCallback funcTask, uint32_t interval, struct Message * msg )
{
  uint32_t time = millis();
  uint8_t result = 1;
  while (( millis() - time < interval ) && result )
    result = funcTask( msg );
  return result;
}

#endif  // #ifndef TASKER_H
