#ifndef PADDING_H
#define PADDING_H

// Size of input, input, size of result, result string, padding
char *pad_left(int, char *, int, char *, char);
char *pad_right(int, char *, int, char *, char);
char *pad_both(int, char *, int, char *, char);
char *padding(int, char);

#endif
