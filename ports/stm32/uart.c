/*
 * SPDX-FileCopyrightText: 2022 Kyunghwan Kwon <k@libmcu.org>
 *
 * SPDX-License-Identifier: MIT
 */

#include "libmcu/uart.h"

#include <errno.h>
#include <string.h>
#include <stdbool.h>

#include "usart.h"

#define MAX_UART			1

struct uart {
	struct uart_api api;

	UART_HandleTypeDef *handle;
	uint8_t channel;
	uint32_t baudrate;
	bool activated;
};

static int write_uart(struct uart *self, const void *data, size_t data_len)
{
	if (!self || !self->activated) {
		return -EPIPE;
	}

	if (HAL_UART_Transmit(self->handle, (const uint8_t *)data,
		       (uint16_t)data_len, 100U) != HAL_OK) {
		return -EIO;
	}

	return (int)data_len;
}

static int read_uart(struct uart *self, void *buf, size_t bufsize)
{
	if (!self || !self->activated) {
		return -EPIPE;
	}

	if (HAL_UART_Receive(self->handle, (uint8_t *)buf, (uint16_t)bufsize,
			HAL_MAX_DELAY) != HAL_OK) {
		return -EIO;
	}

	/* FIXME: it should return the number of bytes received */
	return (int)bufsize;
}

static int enable_uart(struct uart *self, uint32_t baudrate)
{
	if (!self) {
		return -EPIPE;
	} else if (self->activated) {
		return -EALREADY;
	}

	MX_USART2_UART_Init();

	self->baudrate = baudrate;
	self->activated = true;

	return 0;
}

static int disable_uart(struct uart *self)
{
	if (!self) {
		return -EPIPE;
	} else if (!self->activated) {
		return -EALREADY;
	}

	MX_USART2_UART_DeInit();

	self->activated = false;

	return 0;
}

struct uart *uart_create(uint8_t channel)
{
	static struct uart uart[MAX_UART];

	if (channel != 2 || uart[0].activated) {
		return NULL;
	}

	uart[0].channel = channel;
	uart[0].handle = &huart2;

	uart[0].api = (struct uart_api) {
		.enable = enable_uart,
		.disable = disable_uart,
		.write = write_uart,
		.read = read_uart,
	};

	return &uart[0];
}

void uart_delete(struct uart *self)
{
	memset(self, 0, sizeof(*self));
}
