// SPDX-FileCopyrightText: 2020 The at42 Libft Unit Tests Contributors (see CONTRIBUTORS.md)
//
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef _NUMBERS_H_
#define _NUMBERS_H_

unsigned long long rand_number();
unsigned long long rand_number_max(unsigned long long max);
unsigned long long rand_number_between(
	unsigned long long min,
	unsigned long long max);

long long rand_number_signed();
long long rand_number_between_signed(long long min, long long max);

#endif
