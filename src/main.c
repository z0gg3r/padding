#include <stdlib.h>
#include <string.h>
#ifndef _LIB
#include <stdio.h>
#endif
#include "main.h"

int main()
{
	return 0;
}

/*
 * Takes an input string, a result string buffer and a character
 * and pads the input string to the size of the result buffer,
 * with the differnce in size being filled up with the char.
 * Char will be added to the left of the string.
 * Neither size nor sc should count the null terminator.
 */
char *pad_left(int sc, char *s, int size, char *p, char _pad)
{
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
char *pad_both(int sc, char *s, int size, char *p, char _pad)
{
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
char *pad_right(int sc, char *s, int size, char *p, char _pad)
{
	if (sc >= size)
		return s;

	char *b = padding(size - sc, _pad);

	strncat(p, s, sc);
	strncat(p, b, size - sc);

	free(b);

	return p;
}

/*
 * Takes an integer n and a character c and a string
 * containing c n times. Expects n to not count the
 * null terminator.
 */
char *padding(int size, char p)
{
	char *s = malloc(sizeof(char) * (size + 1));

	for (int i = 0; i < size - 1; ++i)
		s[i] = p;
	s[size - 1] = '\0';

	return s;
}
