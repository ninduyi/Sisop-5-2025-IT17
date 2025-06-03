#ifndef __SHELL_H__
#define __SHELL_H__

#include "std_type.h"

extern int cursor_pos;
void printStringWithColor(char *str, byte color_attr);
void mystrcat(char *dst, char *src);
void shell();
void printPrompt();
void parseCommand(char *buf, char *cmd, char arg[2][64]);

/* Tambahkan fungsi bila perlu */

#endif // __SHELL_H__
