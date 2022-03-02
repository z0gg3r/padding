// SPDX-FileCopyrightText: 2021 zocker <zocker@10zen.eu>
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <grapheme.h>
#include "padding.h"

/*
 * Takes an input string, a result string buffer and a character
 * and pads the input string to the size of the result buffer,
 * with the differnce in size being filled up with the char.
 * Char will be added to the left of the string.
 * Size should not count the null terminator.
 */
char *pad_left(char *s, int size, char *p, char _pad)
{
	int sc = strlen(s);
	if (sc >= size)
		return s;

	char *b = padding(size - sc, _pad);

	strncat(p, b, size - sc);
	strncat(p, s, sc);

	free(b);
	return p;
}

/*
 * Char will be added to both sides of the string.
 */
char *pad_both(char *s, int size, char *p, char _pad)
{
	int sc = strlen(s);
	if (sc >= size)
		return s;
	int b_size = (size - sc) / 2;

	char *b1 = padding(b_size, _pad);
	char *b2 = padding(b_size, _pad);

	strncat(p, b1, b_size);
	strncat(p, s, sc);
	strncat(p, b2, b_size);

	free(b1);
	free(b2);

	return p;
}
/*
 * Char will be added to the left of the string.
 */
char *pad_right(char *s, int size, char *p, char _pad)
{
	int sc =  strlen(s);
	if (sc >= size)
		return s;

	char *b = padding(size - sc, _pad);

	strncat(p, s, sc);
	strncat(p, b, size - sc);

	free(b);

	return p;
}

/*
 * Takes an integer size and a character p and a string
 * containing p size times. Expects n to not count the
 * null terminator.
 */
char *padding(int size, char p)
{
	char *s = malloc(sizeof(char) * (size + 1));

	for (int i = 0; i < size; ++i)
		s[i] = p;
	s[size] = '\0';

	return s;
}

int is_utf8(char *s)
{
	size_t ret = 0;
	size_t off = 0;
	int len = 0;

	while (1) {
		if (s[off] == '\0')
			break;
		ret = grapheme_next_character_break(s + off, SIZE_MAX);
		if (ret == 1)
			++len;
		off += ret;
	}

	return len != strlen(s);
}

int utf8_len(char *s)
{
	size_t ret = 0;
	size_t off = 0;
	int len = 0;

	for (; s[off] != '\0'; off += ret) {
		ret = grapheme_next_character_break(s + off, SIZE_MAX);
		if (ret > 1)
			++len;
	}

	return len;
}

void utf8_char(char *s, int buf_len, char *buf)
{
	if (!is_utf8(s)) {
		buf[0] = s[0];
		for (int i = 1; i < buf_len; ++i)
			buf[i] = '\0';
	} else {
		size_t ret = 0;
		size_t off = 0;
		size_t tmp = -1;

		while (1) {
			if (s[off] == '\0')
				break;
			
			ret = grapheme_next_character_break(s + off, SIZE_MAX);
			
			if (ret > 1 && tmp == -1)
				tmp = off;
			else
				break;

			off += ret;
		}

		printf("off: %ld\ntmp: %ld\n", off, tmp);

		int needed = snprintf(NULL, 0, "%.*s", (int) off, s + tmp);

		if (needed <= buf_len) {
			snprintf(buf, needed, "%.*s", (int) off, s + tmp);
		} else {
			buf[0] = ' ';
			for (int i = 1; i < buf_len; ++i)
				buf[i] = '\0';
		}
			
	}
}
