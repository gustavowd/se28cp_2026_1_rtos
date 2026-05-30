/*
 * keyb.c
 *
 *  Created on: 27 de mai. de 2026
 *      Author: gustavo
 */

#include "main.h"
#include "cmsis_os.h"
#include "keyb.h"

static TimerHandle_t keyt;
static QueueHandle_t keyq;


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
	BaseType_t pxHigherPriorityTaskWoken = pdFALSE;
	HAL_NVIC_DisableIRQ(EXTI15_10_IRQn);
	xTimerStartFromISR(keyt, &pxHigherPriorityTaskWoken);
	portYIELD_FROM_ISR(pxHigherPriorityTaskWoken);
}


static void debounce_callback( TimerHandle_t xTimer ){
	button_t button = NO_BUTTON;
	if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == GPIO_PIN_SET){
		button = BUTTON_A;
	}
	HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
	xQueueSend(keyq, &button, 0);
}


bool keyb_init(void){
	keyt = xTimerCreate("debounce", 50, pdFALSE, NULL, debounce_callback);
	keyq = xQueueCreate(16, sizeof(button_t));

	return ((keyt != NULL) && (keyq != NULL));
}


BaseType_t keyb_read(button_t *button, TickType_t timeout){
	 return xQueueReceive(keyq, button, timeout);
 }


