// SPDX-FileCopyrightText: 2021 zocker <zocker@10zen.eu>
//
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef PADDING_H
#define PADDING_H

// input, size of result, result string, padding
char *pad_left(char *, int, char *, char);
char *pad_right(char *, int, char *, char);
char *pad_both(char *, int, char *, char);
char *padding(int, char);

int is_utf8(char *);
int utf8_len(char *);
void utf8_char(char *, char *);
// Stolen from weechat/src/core/wee-utf8.c
void utf8_int_string(unsigned int, char *);
int utf8_char_int(const char *);

#endif
