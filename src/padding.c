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

void utf8_char(char *s, char *buf)
{
	utf8_int_string(utf8_char_int(s), buf);
}

/*
 * utf8_int_string and utf8_char_int are part of Weechat's wee-utf8.c
 * Copyright (C) 2003-2022 Sébastien Helleu <flashcode@flashtux.org>
 * Copyright (C) 2006 Emmanuel Bouthenot <kolter@openics.org>
 *
 * Licensed under GPLv3, no modifications werde made
 */
void utf8_int_string (unsigned int unicode_value, char *string)
{
	if (!string)
		return;

	string[0] = '\0';

	if (unicode_value <= 0x007F)
	{
		/* UTF-8, 1 byte: 0vvvvvvv */
		string[0] = unicode_value;
		string[1] = '\0';
	}
	else if (unicode_value <= 0x07FF)
	{
		/* UTF-8, 2 bytes: 110vvvvv 10vvvvvv */
		string[0] = 0xC0 | ((unicode_value >> 6) & 0x1F);
		string[1] = 0x80 | (unicode_value & 0x3F);
		string[2] = '\0';
	}
	else if (unicode_value <= 0xFFFF)
	{
		/* UTF-8, 3 bytes: 1110vvvv 10vvvvvv 10vvvvvv */
		string[0] = 0xE0 | ((unicode_value >> 12) & 0x0F);
		string[1] = 0x80 | ((unicode_value >> 6) & 0x3F);
		string[2] = 0x80 | (unicode_value & 0x3F);
		string[3] = '\0';
	}
	else if (unicode_value <= 0x1FFFFF)
	{
		/* UTF-8, 4 bytes: 11110vvv 10vvvvvv 10vvvvvv 10vvvvvv */
		string[0] = 0xF0 | ((unicode_value >> 18) & 0x07);
		string[1] = 0x80 | ((unicode_value >> 12) & 0x3F);
		string[2] = 0x80 | ((unicode_value >> 6) & 0x3F);
		string[3] = 0x80 | (unicode_value & 0x3F);
		string[4] = '\0';
	}
}

int utf8_char_int (const char *string)
{
	const unsigned char *ptr_string;

	if (!string)
		return 0;

	ptr_string = (unsigned char *)string;

	/* UTF-8, 2 bytes: 110vvvvv 10vvvvvv */
	if ((ptr_string[0] & 0xE0) == 0xC0)
	{
		if (!ptr_string[1])
			return (int)(ptr_string[0] & 0x1F);
		return ((int)(ptr_string[0] & 0x1F) << 6) +
		       ((int)(ptr_string[1] & 0x3F));
	}
	/* UTF-8, 3 bytes: 1110vvvv 10vvvvvv 10vvvvvv */
	else if ((ptr_string[0] & 0xF0) == 0xE0)
	{
		if (!ptr_string[1])
			return (int)(ptr_string[0] & 0x0F);
		if (!ptr_string[2])
			return (((int)(ptr_string[0] & 0x0F)) << 6) +
			       ((int)(ptr_string[1] & 0x3F));
		return (((int)(ptr_string[0] & 0x0F)) << 12) +
		       (((int)(ptr_string[1] & 0x3F)) << 6) +
		       ((int)(ptr_string[2] & 0x3F));
	}
	/* UTF-8, 4 bytes: 11110vvv 10vvvvvv 10vvvvvv 10vvvvvv */
	else if ((ptr_string[0] & 0xF8) == 0xF0)
	{
		if (!ptr_string[1])
			return (int)(ptr_string[0] & 0x07);
		if (!ptr_string[2])
			return (((int)(ptr_string[0] & 0x07)) << 6) +
			       ((int)(ptr_string[1] & 0x3F));
		if (!ptr_string[3])
			return (((int)(ptr_string[0] & 0x07)) << 12) +
			       (((int)(ptr_string[1] & 0x3F)) << 6) +
			       ((int)(ptr_string[2] & 0x3F));
		return (((int)(ptr_string[0] & 0x07)) << 18) +
		       (((int)(ptr_string[1] & 0x3F)) << 12) +
		       (((int)(ptr_string[2] & 0x3F)) << 6) +
		       ((int)(ptr_string[3] & 0x3F));
	}
	/* UTF-8, 1 byte: 0vvvvvvv */
	return (int)ptr_string[0];
}
