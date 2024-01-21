// SPDX-FileCopyrightText: 2020 The at42 Libft Unit Tests Contributors (see CONTRIBUTORS.md)
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "utils.h"
#include "../utils/utils.h"
#include <stdlib.h>
#include <fcntl.h>

static __attribute__((constructor)) void init(void)
{
	int rand_fd;
	unsigned int seed;

	rand_fd = ft_must_open("/dev/urandom", O_RDONLY);
	ft_must_read(rand_fd, &seed, sizeof(seed));
	ft_must_close(rand_fd);

	srand(seed);
}
