/*
 * SPDX-FileCopyrightText: 2023 Kyunghwan Kwon <k@mononn.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "libmcu/port/gpio.h"
#include "gpio.h"
#include "pinmap.h"
#include <errno.h>

struct gpio {
	uint16_t pin;
	gpio_handler_t handler;
	void *handler_ctx;
};

static void enable_gpios(void)
{
	MX_GPIO_InitRecursive();
}

static GPIO_TypeDef *pin_to_port(uint16_t pin)
{
	int port = pin / 16;
	switch (port) {
	case 0:
		return GPIOA;
	case 1:
		return GPIOB;
	case 2:
		return GPIOC;
	case 3:
		return GPIOD;
	case 4:
		return GPIOE;
	case 5:
		return GPIOF;
	default:
		return 0;
	}
}

static uint16_t pin_to_portpin(uint16_t pin)
{
	switch (pin % 16) {
	case 0:
		return GPIO_PIN_0;
	case 1:
		return GPIO_PIN_1;
	case 2:
		return GPIO_PIN_2;
	case 3:
		return GPIO_PIN_3;
	case 4:
		return GPIO_PIN_4;
	case 5:
		return GPIO_PIN_5;
	case 6:
		return GPIO_PIN_6;
	case 7:
		return GPIO_PIN_7;
	case 8:
		return GPIO_PIN_8;
	case 9:
		return GPIO_PIN_9;
	case 10:
		return GPIO_PIN_10;
	case 11:
		return GPIO_PIN_11;
	case 12:
		return GPIO_PIN_12;
	case 13:
		return GPIO_PIN_13;
	case 14:
		return GPIO_PIN_14;
	case 15:
		return GPIO_PIN_15;
	default:
		return 0;
	}
}

int gpio_port_enable(struct gpio *self)
{
	switch (self->pin) {
	case PINMAP_LED:
		enable_gpios();
		break;
	default:
		return -ERANGE;
	}

	return 0;
}

int gpio_port_disable(struct gpio *self)
{
	(void)self;
	return 0;
}

int gpio_port_set(struct gpio *self, int value)
{
	HAL_GPIO_WritePin(pin_to_port(self->pin), pin_to_portpin(self->pin),
			(GPIO_PinState)value);

	return 0;
}

int gpio_port_get(struct gpio *self)
{
	return HAL_GPIO_ReadPin(pin_to_port(self->pin),
			pin_to_portpin(self->pin));
}

int gpio_port_register_handler(struct gpio *self,
		gpio_handler_t handler, void *ctx)
{
	self->handler = handler;
	self->handler_ctx = ctx;
	return 0;
}

struct gpio *gpio_port_create(uint16_t pin)
{
	static struct gpio led;

	struct gpio *p;

	switch (pin) {
	case PINMAP_LED:
		p = &led;
		break;
	default:
		return NULL;
	}

	p->pin = pin;

	return p;
}

void gpio_port_delete(struct gpio *self)
{
	(void)self;
}
