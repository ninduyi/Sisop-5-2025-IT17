#include "shell.h"
#include "kernel.h"
#include "std_lib.h" // Diperlukan untuk strcmp dan strcpy

static char current_username[33] = "user";
static char current_gc_title[10] = ""; // Untuk menyimpan "@Storm", "@Serpent", dll.

// Array untuk respons Gurt (dari fitur sebelumnya)
char* gurt_responses[] = {
    "yo\n",
    "ts unami gng </3\n",
    "sygau\n"
};
int num_gurt_responses = 3;

// Fungsi custom modulo (dari fitur sebelumnya)
int custom_unsigned_modulo(unsigned int dividend, int divisor) {
    unsigned int remainder;
    if (divisor == 0) return 0;
    if (divisor < 0) divisor = -divisor;
    remainder = dividend;
    while (remainder >= (unsigned int)divisor) {
        remainder -= (unsigned int)divisor;
    }
    return (int)remainder;
}


void shell() {
  char buf[128];
  char cmd[64];
  char arg[2][64]; // arg[0] untuk nama GC, arg[1] belum dipakai
  bool is_known_command;
  unsigned int tick_value;
  int random_index;

  printString("Welcome to EorzeOS!\n");
  while (true) {
    printString(current_username);
    if (current_gc_title[0] != '\0') { // Jika ada gelar GC
        printString(current_gc_title);
    }
    printString("> ");
    readString(buf);

    cmd[0] = '\0';
    arg[0][0] = '\0';
    arg[1][0] = '\0';

    parseCommand(buf, cmd, arg);

    is_known_command = false;

    if (cmd[0] != '\0') {
      if (strcmp(cmd, "yo") == true) {
        printString("gurt\n");
        is_known_command = true;
      } else if (strcmp(cmd, "gurt") == true) {
        printString("yo\n");
        is_known_command = true;
      } else if (strcmp(cmd, "user") == true) {
        if (arg[0][0] != '\0') {
          int k = 0;
          while (arg[0][k] != '\0' && k < 32) {
            current_username[k] = arg[0][k];
            k++;
          }
          current_username[k] = '\0';
          printString("Username changed to ");
          printString(current_username);
          printString("\n");
        } else {
          strcpy(current_username, "user");
          printString("Username changed to user\n");
        }
        is_known_command = true;
      } else if (strcmp(cmd, "yogurt") == true) {
        tick_value = getBiosTick();
        random_index = custom_unsigned_modulo(tick_value, num_gurt_responses);
        printString("gurt> ");
        printString(gurt_responses[random_index]);
        is_known_command = true;
      } else if (strcmp(cmd, "grandcompany") == true) {
        if (arg[0][0] != '\0') { // Pastikan ada argumen untuk nama GC
          if (strcmp(arg[0], "maelstrom") == true) {
            setTextColor(ATTRIBUTE_MAELSTROM);
            clearScreen(); // Clear dengan warna baru
            strcpy(current_gc_title, "@Storm");
            // Pesan konfirmasi tidak diminta, tapi bisa ditambahkan jika mau
          } else if (strcmp(arg[0], "twinadder") == true) {
            setTextColor(ATTRIBUTE_TWIN_ADDER);
            clearScreen();
            strcpy(current_gc_title, "@Serpent");
          } else if (strcmp(arg[0], "immortalflames") == true) {
            setTextColor(ATTRIBUTE_IMMORTAL_FLAMES);
            clearScreen();
            strcpy(current_gc_title, "@Flame");
          } else {
            printString("Error: Invalid Grand Company specified.\n");
            printString("Usage: grandcompany [maelstrom|twinadder|immortalflames]\n");
          }
        } else {
          printString("Error: Grand Company name required.\n");
          printString("Usage: grandcompany [maelstrom|twinadder|immortalflames]\n");
        }
        is_known_command = true;
      } else if (strcmp(cmd, "clear") == true) {
        setTextColor(ATTRIBUTE_DEFAULT);
        clearScreen(); // Clear dengan warna default
        current_gc_title[0] = '\0'; // Hapus gelar GC
        // Pesan "para Grand Company sedih kamu netral" bisa ditambahkan di sini jika mau.
        // printString("The Grand Companies are saddened by your neutrality.\n");
        is_known_command = true;
      }
      // TODO: Tambahkan perintah kalkulator jika belum ada
    }

    if (!is_known_command) {
      printString(buf);
      printString("\n");
    }
  }
}

// Fungsi parseCommand (asumsikan sudah bisa mem-parsing dua argumen)
void parseCommand(char *buf, char *cmd, char arg[2][64]) {
  int buf_idx = 0;
  int token_idx = 0;

  cmd[0] = '\0';
  arg[0][0] = '\0';
  arg[1][0] = '\0';

  while (buf[buf_idx] == ' ' || buf[buf_idx] == '\t') { buf_idx++; }

  token_idx = 0;
  while (buf[buf_idx] != '\0' && buf[buf_idx] != ' ' && buf[buf_idx] != '\t' && token_idx < 63) {
    cmd[token_idx++] = buf[buf_idx++];
  }
  cmd[token_idx] = '\0';

  if (cmd[0] == '\0' && buf[buf_idx] == '\0') return;

  while (buf[buf_idx] == ' ' || buf[buf_idx] == '\t') { buf_idx++; }

  token_idx = 0;
  while (buf[buf_idx] != '\0' && buf[buf_idx] != ' ' && buf[buf_idx] != '\t' && token_idx < 63) {
    arg[0][token_idx++] = buf[buf_idx++];
  }
  arg[0][token_idx] = '\0';

  while (buf[buf_idx] == ' ' || buf[buf_idx] == '\t') { buf_idx++; }

  token_idx = 0;
  while (buf[buf_idx] != '\0' && buf[buf_idx] != ' ' && buf[buf_idx] != '\t' && token_idx < 63) {
    arg[1][token_idx++] = buf[buf_idx++];
  }
  arg[1][token_idx] = '\0';
}
