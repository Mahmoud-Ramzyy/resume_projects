#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "Micro_config.h"
#include "std_types.h"
#include "Popular_Macros.h"

/* Keypad configurations for number of rows and columns */
#define N_col 3
#define N_row 4

/* Keypad Port Configurations */
#define KEYPAD_OUT PORTA
#define KEYPAD_IN  PINA
#define KEYPAD_PORT_DIR DDRA

/******************************************************************************
 * Function responsible for getting the pressed keypad key                   */

uint8 KeyPad_getPressedKey(void);


#endif /* KEYPAD_H_ */
