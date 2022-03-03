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

	strncat(p, b, strlen(b));
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

	strncat(p, b1, strlen(b1));
	strncat(p, s, strlen(s));
	strncat(p, b1, strlen(b1));

	free(b1);

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
	strncat(p, b, strlen(b));

	free(b);

	return p;
}

/*
 * Takes an integer size and a character p and a string
 * containing p size times. Size is the number of characters,
 * not the allocate memory!
 */
char *padding(int size, char *p)
{
	char *tmp =  calloc(5, sizeof(char));
	utf8_int_string(utf8_char_int(p), tmp);
	if (utf8_strlen(tmp) == 1 && strlen(tmp) != 1)
		size *= strlen(tmp);

	char *s = calloc(size + 1, sizeof(char));

	for (int i = 0; i < size - strlen(tmp); i += strlen(tmp))
		for (int j = 0; j < strlen(tmp); ++j)
			s[i + j] = tmp[j];
	s[size] = '\0';

	free(tmp);
	return s;
}
