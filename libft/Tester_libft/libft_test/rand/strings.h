// SPDX-FileCopyrightText: 2020 The at42 Libft Unit Tests Contributors (see CONTRIBUTORS.md)
//
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef _STRINGS_H_
#define _STRINGS_H_

#define CHARSET_LOWERCASE 1
#define CHARSET_UPPERCASE 2
#define CHARSET_ALPHA 3
#define CHARSET_NUMBERS 4
#define CHARSET_ALPHANUM 7
#define CHARSET_SYMBOLS 8
#define CHARSET_PRINTABLE 15
#define CHARSET_NON_PRINTABLE 16
#define CHARSET_NON_PRINTABLE_NULL 90
#define CHARSET_ALL 31
#define CHARSET_ALL_NULL 94
#define CHARSET_EXTENDED_ONLY 32
#define CHARSET_EXTENDED 63
#define CHARSET_EXTENDED_NULL 127
#define CHARSET_NULL 64

void rand_string(unsigned char flags, int n, void **copy0, void **copy1);

#endif
