/*
 * SPDX-FileCopyrightText: 2024 Kyunghwan Kwon <k@libmcu.org>
 *
 * SPDX-License-Identifier: MIT
 */

#include "libmcu/board.h"

#include "stm32g4xx_hal.h"
#include "FreeRTOS.h"
#include "task.h"

#define CPULOAD_CALC_INTERVAL_MS	1000

static uint32_t idle_time_elapsed;
static uint32_t running_time_elapsed;

void on_task_switch_in(void)
{
	static TaskHandle_t prev;

	static uint32_t t0;
	static uint32_t sum_elapsed;

	uint32_t t1 = board_get_time_since_boot_ms();
	uint32_t elapsed = t1 - t0;

	TaskHandle_t current = xTaskGetCurrentTaskHandle();

	if (current == xTaskGetIdleTaskHandle()) {
		if (current == prev) { /* idle to idle */
			idle_time_elapsed += elapsed;
		} else { /* active to idle */
			running_time_elapsed += elapsed? elapsed : 1;
		}
	} else {
		if (current == prev) { /* active to active */
			running_time_elapsed += elapsed;
		} else { /* idle to active */
			idle_time_elapsed += elapsed;
		}
	}

	if ((sum_elapsed += elapsed) >= CPULOAD_CALC_INTERVAL_MS) {
		sum_elapsed = 0;
		running_time_elapsed = idle_time_elapsed = 0;
	}

	t0 = t1;
	prev = current;
}

void on_sleep_enter(uint32_t tick)
{
#if 0
	HAL_SuspendTick();
#endif
	(void)tick;
}

void on_sleep_exit(uint32_t tick)
{
#if 0
	HAL_ResumeTick();
#endif
	(void)tick;
}

uint8_t board_cpuload(void)
{
	return (uint8_t)(running_time_elapsed * 100 /
			(running_time_elapsed + idle_time_elapsed));
}
