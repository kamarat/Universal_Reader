#ifndef TASKER_H
#define TASKER_H

#include <Arduino.h>


/*== FUNKCIE ==
 *=============
 */
/*== Deklaracia funkcii ==
 */
typedef uint8_t ( *TaskCallback )( struct Message * );
uint8_t taskInterval( TaskCallback funcTask, uint32_t interval, struct Message * msg );

/*== Definicia funkcii ==
 */
/*******************************************************************************
 *    Function: taskInterval
 * Description: volanie callback funkcie a jej spustenie s pridelenym casovym
 *              intervalom
 *   Parameter: [IN] TaskCallback funcTask - smernik na callback funkciu
 *              [IN] uint32_t interval - prideleny casovy intervalom
 *              [OUT] struct Message * msg - smernik na strukturu riadkov
 *                                            s vypisom funkcie
 *      Return: uint8_t 0 - callback funkcia vykonana s vysledkom
 *                      1 - callback funkcia vykonana bez vysledku
 ******************************************************************************/
uint8_t taskInterval( TaskCallback funcTask, uint32_t interval, struct Message * msg )
{
  uint32_t time = millis();
  uint8_t result = 1;
  while (( millis() - time < interval ) && result )
    result = funcTask( msg );
  return result;
}

#endif  // #ifndef TASKER_H
