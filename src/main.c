#include "libmcu/board.h"
#include "libmcu/timext.h"
#include "libmcu/logging.h"
#include "libmcu/gpio.h"
#include "libmcu/uart.h"

#include "pinmap.h"

static struct gpio *led;
static struct uart *uart2;

static size_t logging_stdout_writer(const void *data, size_t size)
{
	unused(size);

	static char buf[LOGGING_MESSAGE_MAXLEN];
	size_t len = logging_stringify(buf, sizeof(buf)-1, data);

	buf[len++] = '\n';
	buf[len] = '\0';

	return (size_t)uart_write(uart2, buf, len);
}

static void logging_stdout_backend_init(void)
{
	static struct logging_backend log_console = {
		.write = logging_stdout_writer,
	};

	logging_add_backend(&log_console);
}

int main(void)
{
	board_init(); /* should be called very first. */
	logging_init(board_get_time_since_boot_ms);

	uart2 = uart_create(2);
	uart_enable(uart2, 115200);
	logging_stdout_backend_init();

	int ledval = 0;
	led = gpio_create(PINMAP_LED);
	gpio_enable(led);

	while (1) {
		ledval ^= 1;
		gpio_set(led, ledval);
		debug("Hello");
		sleep_ms(500);
	}

	return 0;
}
