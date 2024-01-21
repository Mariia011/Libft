// SPDX-FileCopyrightText: 2020 The at42 Libft Unit Tests Contributors (see CONTRIBUTORS.md)
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "utils.h"
#include <stdbool.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>
#include <criterion/alloc.h>

__attribute__((malloc)) __attribute__((returns_nonnull)) void *ft_malloc(
	unsigned int n)
{
	void *ptr;

	ptr = cr_malloc(n + 8);
	if (ptr == NULL)
	{
		ptr = malloc(n + 8);

		if (ptr == NULL)
		{
			ft_fatalf("Failed to malloc %d+8 bytes", n);
		}
		*((char *)ptr) = 1;
	}
	else
	{
		*((char *)ptr) = 0;
	}

	return ((void *)(((char *)ptr) + 8));
}

void ft_free(void *ptr)
{
	if (*(((char *)ptr) - 8) == 1)
	{
		free(((char *)ptr) - 8);
	}
	else
	{
		cr_free(((char *)ptr) - 8);
	}
}

int ft_must_open(const char *path, int flags)
{
	int fd;

	fd = open(path, flags);
	if (fd <= 0)
		ft_fatalf("could not open %s", path);

	return (fd);
}

void ft_must_read(int fd, void *buf, int n)
{
	int rd, ret;

	rd = 0;
	while (rd < n)
	{
		ret = read(fd, &((char *)buf)[rd], n - rd);
		if (ret < 0)
		{
			ft_fatalf("could only read %d bytes out of %d from file descriptor "
					  "%d", rd, n, fd);
		}
		rd += ret;
	}
}

__attribute__((format (printf, 1, 2))) __attribute__((noreturn)) void ft_fatalf(
	const char *format,
	...)
{
	va_list args;

	va_start(args, format);

	vfprintf(stderr, format, args);
	exit(-1);
}

void ft_must_close(int fd)
{
	if (close(fd) < 0)
		ft_fatalf("could not close file descriptor %d", fd);
}

int int_to_bool(int c)
{
	if (c == 0)
		return false;
	return true;
}
