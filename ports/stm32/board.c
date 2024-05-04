/*
 * SPDX-FileCopyrightText: 2022 Kyunghwan Kwon <k@libmcu.org>
 *
 * SPDX-License-Identifier: MIT
 */

#include "libmcu/board.h"
#include "libmcu/assert.h"
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

#include "stm32f4xx_hal.h"
#include "FreeRTOS.h"
#include "task.h"

#define MAIN_TASK_STACK_SIZE		2048U
#define MAIN_TASK_PRIORITY		1U

static void start_scheduler(void)
{
	extern int main(void);
	if (xTaskCreate((void (*)(void *))main, "Main",
			MAIN_TASK_STACK_SIZE / sizeof(StackType_t), 0,
			MAIN_TASK_PRIORITY, 0) != pdPASS) {
		assert(0);
	}
	vTaskStartScheduler();
}

static void initialize_bsp(void)
{
	extern void SystemClock_Config(void);
	HAL_Init();
	SystemClock_Config();
}

const char *board_get_serial_number_string(void)
{
	static char sn[16+1];

	if (strnlen(sn, sizeof(sn)) == 0) {
		sprintf(sn, "%08lx%08lx", HAL_GetDEVID(), HAL_GetREVID());
	}

	return sn;
}

board_reboot_reason_t board_get_reboot_reason(void)
{
	board_reboot_reason_t reason = BOARD_REBOOT_UNKNOWN;

	if (__HAL_PWR_GET_FLAG(PWR_FLAG_SB)) {
		reason = BOARD_REBOOT_DEEPSLEEP;
	} else if (__HAL_RCC_GET_FLAG(RCC_FLAG_LPWRRST)) {
		reason = BOARD_REBOOT_POWER;
	} else if (__HAL_RCC_GET_FLAG(RCC_FLAG_WWDGRST)) {
		reason = BOARD_REBOOT_WDT;
	} else if (__HAL_RCC_GET_FLAG(RCC_FLAG_IWDGRST)) {
		reason = BOARD_REBOOT_WDT_INT;
	} else if (__HAL_RCC_GET_FLAG(RCC_FLAG_SFTRST)) {
		reason = BOARD_REBOOT_SOFT;
	} else if (__HAL_RCC_GET_FLAG(RCC_FLAG_PINRST)) {
		reason = BOARD_REBOOT_PIN;
	} else if (__HAL_RCC_GET_FLAG(RCC_FLAG_BORRST)) {
		reason = BOARD_REBOOT_BROWNOUT;
	}

	__HAL_RCC_CLEAR_RESET_FLAGS();

	return reason;
}

void board_reboot(void)
{
	NVIC_SystemReset();
}

void board_init(void)
{
	static bool initialized;

	if (!initialized) {
		initialized = true;

		initialize_bsp();
		start_scheduler();
		return; /* never reaches down here */
	}
}
