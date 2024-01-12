/*
 * SPDX-FileCopyrightText: 2022 Kyunghwan Kwon <k@mononn.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "libmcu/cli_overrides.h"
//#include "pusb/usbd.h"

struct cli_io const *cli_io_create(void)
{
#if 0
	static const struct cli_io io = {
		.read = usbd_cdc_acm_read,
		.write = usbd_cdc_acm_write,
	};

	return &io;
#else
	return 0;
#endif
}
