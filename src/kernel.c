#include "shell.h"
#include "kernel.h"

int main() {
  clearScreen();
  shell();
}

void printString(char *str) {
  int i = 0;
  while (str[i] != '\0') {
    putInMemory(0xB800, i * 2, str[i]); // Write character to VGA
    putInMemory(0xB800, i * 2 + 1, 0x0F); // White text on black
    i++;
  }
}

void readString(char *buf) {
  int i = 0;
  char c;
  int ret;
  char debug_buf[16];

  /* Flush keyboard buffer */
  do {
    ret = interrupt(0x16, 1, 0, 0, 0); // Check for keystroke (ah=1)
  } while (ret != 0);

  do {
    // BIOS interrupt 0x16, AH=0: Read key press
    ret = interrupt(0x16, 0, 0, 0, 0); // Get character
    c = (char)(ret & 0xFF); // Extract low byte (AL) as character

    /* Debug: Print return value and cursor position */
    printStringWithColor("Int ret: ", 0x0F);
    itoa(ret, debug_buf);
    printStringWithColor(debug_buf, 0x0F);
    printStringWithColor(" Char: ", 0x0F);
    itoa(c, debug_buf);
    printStringWithColor(debug_buf, 0x0F);
    printStringWithColor(" Pos: ", 0x0F);
    itoa(cursor_pos, debug_buf);
    printStringWithColor(debug_buf, 0x0F);
    printStringWithColor("\n", 0x0F);

    if (c == '\r') { // Enter key
      buf[i] = '\0';
      cursor_pos = ((cursor_pos / 80) + 1) * 80; // Move to start of next line
      break;
    } else if (c == '\b' && i > 0) { // Backspace
      i--;
      cursor_pos--;
      putInMemory(0xB800, cursor_pos * 2, ' '); // Erase character
      putInMemory(0xB800, cursor_pos * 2 + 1, 0x0F);
    } else if (c >= 32 && c <= 126) { // Printable ASCII
      buf[i] = c;
      putInMemory(0xB800, cursor_pos * 2, c); // Display character
      putInMemory(0xB800, cursor_pos * 2 + 1, 0x0F);
      i++;
      cursor_pos++;
    }
    /* Check screen boundary */
    if (cursor_pos >= 80 * 25) {
      scrollScreen();
    }
  } while (i < 127); // Buffer limit
  buf[i] = '\0';
}

void clearScreen() {
  int i;
  for (i = 0; i < 80 * 25 * 2; i += 2) { // 80x25 VGA text mode
    putInMemory(0xB800, i, ' '); // Clear to space
    putInMemory(0xB800, i + 1, 0x0F); // White on black
  }
  cursor_pos = 0; // Reset cursor position
}