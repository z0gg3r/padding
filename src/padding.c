// SPDX-FileCopyrightText: 2021 zocker <zocker@10zen.eu>
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "wee-utf8.h" // stolen from Weechat (https://weechat.org)
#include "padding.h"

/*
 * Takes an input string, a result string buffer and a character
 * and pads the input string to the size of the result buffer,
 * with the differnce in size being filled up with the char.
 * Char will be added to the left of the string.
 * Size should not count the null terminator.
 */
char *pad_left(char *s, int size, char *p, char *_pad)
{
	if (strlen(s) >= size)
		return s;

	char *b = padding(size - strlen(s), _pad);

	strncat(p, b, size - strlen(s));
	strncat(p, s, strlen(s));

	free(b);
	return p;
}

/*
 * Char will be added to both sides of the string.
 */
char *pad_both(char *s, int size, char *p, char *_pad)
{
	if (strlen(s) >= size)
		return s;
	int b_size = (size - strlen(s)) / 2;

	char *b1 = padding(b_size, _pad);
	char *b2 = padding(b_size, _pad);

	strncat(p, b1, strlen(b1));
	strncat(p, s, strlen(s));
	strncat(p, b2, strlen(b2));

	free(b1);
	free(b2);

	return p;
}
/*
 * Char will be added to the left of the string.
 */
char *pad_right(char *s, int size, char *p, char *_pad)
{
	if (strlen(s) >= size)
		return s;

	char *b = padding(size - strlen(s), _pad);

	strncat(p, s, strlen(s));
	strncat(p, b, size - strlen(s));

	free(b);

	return p;
}

/*
 * Takes an integer size and a character p and a string
 * containing p size times. Expects n to not count the
 * null terminator.
 */
char *padding(int size, char *p)
{
	char *tmp =  malloc(sizeof(char) * 12); // utf8_int_string wants => 6, so we use 12
	utf8_int_string(utf8_char_int(p), tmp);
	if (utf8_strlen(tmp) == 1 && strlen(tmp) != 1)
		size *= strlen(tmp);

	char *s = malloc(sizeof(char) * (size + 1));

	for (int i = 0; i < size; ++i)
		strncat(s, tmp, strlen(tmp));
	s[size] = '\0';

	free(tmp);
	return s;
}
