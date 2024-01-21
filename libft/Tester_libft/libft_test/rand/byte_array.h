// SPDX-FileCopyrightText: 2020 The at42 Libft Unit Tests Contributors (see CONTRIBUTORS.md)
//
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef _BYTE_ARRAY_H_
#define _BYTE_ARRAY_H_

typedef unsigned char (*t_generator)();

void ft_byte_array(unsigned int n, void **copy0, void **copy1);
void ft_elem_array(
	unsigned int n,
	unsigned int size,
	void **copy0,
	void **copy1);
void ft_byte_array_generator(
	unsigned int n,
	void **copy0,
	void **copy1,
	t_generator g);
void ft_elem_array_generator(
	unsigned int n,
	unsigned int size,
	void **copy0,
	void **copy1,
	t_generator g);

#endif
