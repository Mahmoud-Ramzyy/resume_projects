
#ifndef ADC_H_
#define ADC_H_

#include "std_types.h"
#include "common_macros.h"
#include "micro_config.h"

/********************************preprocessor**********************************/
#define ACD_io DDRA
#define ACD_ip PINA
#define ACD_op PORTA

/*******************************Functions ***********************************/
void ADC_init(void);
uint16 ADC_readChannel(uint8 ch_num);
#endif /* ADC_H_ */
