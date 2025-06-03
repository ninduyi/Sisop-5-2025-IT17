#include "shell.h"
#include "kernel.h"
#include "std_lib.h"

char username[50] = "user";
char grandcompany[50] = "";
byte color = 0x0F;
int cursor_pos = 0;

/* Moved from inside shell() */
char *phrases[] = {"yo", "ts unami gng </3", "sygau"};

void scrollScreen() {
  int i;
  /* Copy rows 1-24 to 0-23 (shift up) */
  for (i = 0; i < 80 * 24 * 2; i += 2) {
    putInMemory(0xB800, i, ' '); // Clear as we go
    putInMemory(0xB800, i + 1, 0x0F);
  }
  /* Clear last row (row 24) */
  for (i = 80 * 24 * 2; i < 80 * 25 * 2; i += 2) {
    putInMemory(0xB800, i, ' ');
    putInMemory(0xB800, i + 1, 0x0F);
  }
  cursor_pos = 80 * 24; /* Set cursor to start of last row */
}

void printStringWithColor(char *str, byte color_attr) {
  while (*str) {
    /* Check if cursor_pos exceeds screen size (80x25 = 2000 chars) */
    if (cursor_pos >= 80 * 25) {
      scrollScreen();
    }
    if (*str == '\n') {
      /* Move to start of next line */
      cursor_pos = ((cursor_pos / 80) + 1) * 80;
      str++;
      continue;
    }
    putInMemory(0xB800, cursor_pos * 2, *str);
    putInMemory(0xB800, cursor_pos * 2 + 1, color_attr);
    str++;
    cursor_pos++;
  }
}

void printPrompt() {
  char prompt[64];
  if (grandcompany[0] == '\0') {
    strcpy(prompt, username);
    mystrcat(prompt, "> ");
  } else {
    strcpy(prompt, username);
    mystrcat(prompt, "@");
    mystrcat(prompt, grandcompany);
    mystrcat(prompt, "> ");
  }
  printStringWithColor(prompt, color);
}

/* Renamed to avoid clashing with stdlib strcat */
void mystrcat(char *dst, char *src) {
  while (*dst) dst++;
  strcpy(dst, src);
}

void shell() {
  char buf[128];
  char cmd[64];
  char arg[2][64];
  int x, y;
  char result[16];
  int index;

  printStringWithColor("Welcome to EorzeOS!\n", color);
  while (true) {
    printPrompt();
    readString(buf);
    parseCommand(buf, cmd, arg);

    if (strcmp(cmd, "user") == 0) {
      if (arg[0][0] != '\0') {
        strcpy(username, arg[0]);
        printStringWithColor("Username changed to ", color);
        printStringWithColor(username, color);
        printStringWithColor("\n", color);
      } else {
        strcpy(username, "user");
        printStringWithColor("Username changed to user\n", color);
      }
    } else if (strcmp(cmd, "grandcompany") == 0) {
      if (strcmp(arg[0], "maelstrom") == 0) {
        color = 0x04; /* Red text on black */
        strcpy(grandcompany, "Storm");
        clearScreen();
      } else if (strcmp(arg[0], "twinadder") == 0) {
        color = 0x0E; /* Yellow text on black */
        strcpy(grandcompany, "Serpent");
        clearScreen();
      } else if (strcmp(arg[0], "immortalflames") == 0) {
        color = 0x09; /* Light blue text on black */
        strcpy(grandcompany, "Flame");
        clearScreen();
      } else {
        printStringWithColor("Invalid grand company\n", color);
      }
    } else if (strcmp(cmd, "clear") == 0) {
      color = 0x0F; /* White on black */
      grandcompany[0] = '\0';
      clearScreen();
    } else if (strcmp(cmd, "add") == 0) {
      atoi(arg[0], &x);
      atoi(arg[1], &y);
      itoa(x + y, result);
      printStringWithColor(result, color);
      printStringWithColor("\n", color);
    } else if (strcmp(cmd, "sub") == 0) {
      atoi(arg[0], &x);
      atoi(arg[1], &y);
      itoa(x - y, result);
      printStringWithColor(result, color);
      printStringWithColor("\n", color);
    } else if (strcmp(cmd, "mul") == 0) {
      atoi(arg[0], &x);
      atoi(arg[1], &y);
      itoa(x * y, result);
      printStringWithColor(result, color);
      printStringWithColor("\n", color);
    } else if (strcmp(cmd, "div") == 0) {
      atoi(arg[0], &x);
      atoi(arg[1], &y);
      if (y == 0) {
        printStringWithColor("Division by zero\n", color);
      } else {
        itoa(div(x, y), result);
        printStringWithColor(result, color);
        printStringWithColor("\n", color);
      }
    } else if (strcmp(cmd, "yogurt") == 0) {
      index = 0; /* getBiosTick not implemented */
      printStringWithColor("gurt> ", color);
      printStringWithColor(phrases[index], color);
      printStringWithColor("\n", color);
    } else if (strcmp(cmd, "yo") == 0) {
      printStringWithColor("gurt\n", color);
    } else if (strcmp(cmd, "gurt") == 0) {
      printStringWithColor("yo\n", color);
    } else {
      /* Echo feature: print input if not a valid command */
      printStringWithColor(buf, color);
      printStringWithColor("\n", color);
    }
  }
}

void parseCommand(char *buf, char *cmd, char arg[2][64]) {
  int i, cmd_i, arg_i, arg_idx;
  clear((byte *)cmd, 64);
  clear((byte *)arg[0], 64);
  clear((byte *)arg[1], 64);
  i = 0;
  cmd_i = 0;
  arg_i = 0;
  arg_idx = 0;

  while (buf[i] == ' ') i++;
  while (buf[i] != ' ' && buf[i] != '\0') {
    cmd[cmd_i++] = buf[i++];
  }
  while (buf[i] == ' ') i++; /* skip space */
  while (buf[i] != '\0' && arg_idx < 2) {
    arg[arg_idx][arg_i++] = buf[i++];
    if (buf[i] == ' ' || buf[i] == '\0') {
      arg[arg_idx][arg_i] = '\0';
      arg_i = 0;
      arg_idx++;
      while (buf[i] == ' ') i++; /* skip space */
    }
  }
}