

#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "std_types.h"
#include "common_macros.h"
#include "micro_config.h"
 /************************** preprocessor Macros **************/
#define Keypad_col 4
#define Keypad_row 4

#define Keypad_IO DDRA
#define Keypad_OP PORTA  /*for cols */
#define Keypad_IP PINA   /* for rows */

/************************* prototypes ***********************/
//void Keypad_init (void);
uint8 Keypad_get_Num (void);

#endif /* KEYPAD_H_ */
