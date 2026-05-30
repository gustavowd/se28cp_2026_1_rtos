/*
 * keyb.h
 *
 *  Created on: 27 de mai. de 2026
 *      Author: gustavo
 */

#ifndef INC_KEYB_H_
#define INC_KEYB_H_

#include <stdbool.h>

typedef enum button_t_ {
	BUTTON_A,
	BUTTON_B,
	BUTTON_C,
	NO_BUTTON
}button_t;

bool keyb_init(void);
BaseType_t keyb_read(button_t *button, TickType_t timeout);

#endif /* INC_KEYB_H_ */
