/*
 * SPDX-FileCopyrightText: 2024 Kyunghwan Kwon <k@libmcu.org>
 *
 * SPDX-License-Identifier: MIT
 */

#include "libmcu/board.h"

#include "stm32f4xx_hal.h"
#include "FreeRTOS.h"
#include "task.h"

#define CPULOAD_CALC_INTERVAL_MS	1000
#define NR_CORES			1

static struct cpuload {
	uint32_t idle_time_elapsed;
	uint32_t running_time_elapsed;
	TaskHandle_t prev_task;
	uint8_t cpuload;
} cores[NR_CORES];

void on_task_switch_in(void)
{
	static uint32_t t0;
	static uint32_t sum_elapsed;

	uint32_t t1 = board_get_time_since_boot_ms();
	uint32_t elapsed = t1 - t0;

	/* NOTE: count at least 1 even if the task has run for much shorter time
	 * as millisecond unit timer used here. For fine granularity, introduce
	 * high-resolution timer. */
	if (elapsed == 0) {
		elapsed = 1;
	}

	TaskHandle_t current = xTaskGetCurrentTaskHandle();
	struct cpuload *core = &cores[0];

	if (current == xTaskGetIdleTaskHandle()) {
		if (current == core->prev_task) { /* idle to idle */
			core->idle_time_elapsed += elapsed;
		} else { /* active to idle */
			core->running_time_elapsed += elapsed;
		}
	} else {
		if (current == core->prev_task) { /* active to active */
			core->running_time_elapsed += elapsed;
		} else { /* idle to active */
			core->idle_time_elapsed += elapsed;
		}
	}

	sum_elapsed += elapsed;
	core->cpuload = (uint8_t)(core->running_time_elapsed * 100 /
			(core->running_time_elapsed + core->idle_time_elapsed));

	if (sum_elapsed >= CPULOAD_CALC_INTERVAL_MS) {
		core->running_time_elapsed = core->idle_time_elapsed = 0;
		sum_elapsed = 0;
	}

	t0 = t1;
	core->prev_task = current;
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

uint8_t board_cpuload(int core_id)
{
	return cores[core_id].cpuload;
}
