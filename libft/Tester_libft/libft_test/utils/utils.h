// SPDX-FileCopyrightText: 2020 The at42 Libft Unit Tests Contributors (see CONTRIBUTORS.md)
//
// SPDX-License-Identifier: GPL-3.0-or-later

#define TIMEOUT 5

#ifndef _UUTILS_H_
#define _UUTILS_H_

int ft_must_open(const char *path, int flags);
void ft_must_read(int fd, void *buf, int n);
__attribute__((format (printf, 1, 2))) __attribute__((noreturn)) void ft_fatalf(
	const char *format,
	...);
void ft_must_close(int fd);

__attribute__((malloc)) __attribute__((returns_nonnull)) void *ft_malloc(
	unsigned int n);
void ft_free(void *ptr);
int int_to_bool(int c);

#endif
