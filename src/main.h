#ifndef MAIN_H
#define MAIN_H

#define AUTHOR "zocker"
#define MAIL "zocker@10zen.eu"
#define LICENSE "GPLv3"
#define VERSION "0.0.1"

// Size of input, input, size of result, result string, padding
char *pad_left(int, char *, int, char *, char);
char *pad_right(int, char *, int, char *, char);
char *pad_both(int, char *, int, char *, char);
char *padding(int, char);

#endif
