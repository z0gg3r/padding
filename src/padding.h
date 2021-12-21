#ifndef PADDING_H
#define PADDING_H

// input, size of result, result string, padding
char *pad_left(char *, int, char *, char);
char *pad_right(char *, int, char *, char);
char *pad_both(char *, int, char *, char);
char *padding(int, char);

#endif
