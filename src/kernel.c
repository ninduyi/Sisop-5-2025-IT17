#include "shell.h"
#include "kernel.h"

// Variabel global untuk menyimpan atribut teks saat ini
static byte current_text_attribute = ATTRIBUTE_DEFAULT; // Default Light Gray

// Deklarasi fungsi assembly eksternal dari kernel.asm
extern int interrupt(int number, int AX, int BX, int CX, int DX);
// extern unsigned int getBiosTick(); // Sudah ada di kernel.h

int main() {
  // Set warna default saat OS dimulai, meskipun clearScreen juga akan melakukannya.
  // Tidak perlu setTextColor eksplisit di sini jika clearScreen sudah benar.
  clearScreen(); // Membersihkan layar dengan warna default
  shell();
  // Loop tak terbatas agar sistem tidak berhenti (jika shell() kembali)
  while (true) {}
  return 0; // Seharusnya tidak pernah sampai sini
}

// Fungsi baru untuk mengatur atribut teks global
void setTextColor(byte attribute) {
  current_text_attribute = attribute;
}

// Modifikasi fungsi untuk mencetak string dengan warna saat ini
void printString(char *str) {
  int i = 0;
  while (str[i] != '\0') {
    if (str[i] == '\n') {
      interrupt(0x10, 0x0E00 | '\r', (0x00 << 8) | (current_text_attribute & 0x0F), 0x0000, 0x0000);
      interrupt(0x10, 0x0E00 | '\n', (0x00 << 8) | (current_text_attribute & 0x0F), 0x0000, 0x0000);
    } else {
      // AH = 0x0E (Teletype output)
      // AL = Karakter
      // BH = Nomor halaman display (0)
      // BL = Warna foreground (atribut teks saat ini, hanya bagian foreground)
      interrupt(0x10, 0x0E00 | str[i], (0x00 << 8) | (current_text_attribute & 0x0F), 0x0000, 0x0000);
    }
    i++;
  }
}

// Modifikasi fungsi untuk membaca string, echo dengan warna saat ini
void readString(char *buf) {
  int i = 0;
  char current_char;

  while (i < 127) { // Batasi panjang buffer -1 untuk null terminator
    current_char = interrupt(0x16, 0x0000, 0x0000, 0x0000, 0x0000) & 0xFF;

    if (current_char == '\r') {
      buf[i] = '\0';
      printString("\n"); // Akan menggunakan warna saat ini
      return;
    } else if (current_char == '\b') {
      if (i > 0) {
        i--;
        // Mundurkan kursor, cetak spasi (dengan warna bg saat ini), mundurkan kursor lagi
        // Untuk backspace yang benar-benar menghapus dengan warna latar belakang:
        // 1. Mundur kursor: interrupt(0x10, 0x0E00 | '\b', BX_color, CX, DX)
        // 2. Cetak spasi dengan atribut saat ini: interrupt(0x10, 0x0900 | ' ', BX_color_attribute, 0x0001, DX)
        // 3. Mundur kursor lagi: interrupt(0x10, 0x0E00 | '\b', BX_color, CX, DX)
        // Untuk kesederhanaan, kita gunakan teletype untuk backspace, spasi, backspace
        // Ini akan menggunakan warna foreground untuk spasi, yang biasanya OK.
        interrupt(0x10, 0x0E00 | '\b', (0x00 << 8) | (current_text_attribute & 0x0F), 0x0000, 0x0000);
        interrupt(0x10, 0x0E00 | ' ',  (0x00 << 8) | (current_text_attribute & 0x0F), 0x0000, 0x0000);
        interrupt(0x10, 0x0E00 | '\b', (0x00 << 8) | (current_text_attribute & 0x0F), 0x0000, 0x0000);
      }
    } else {
      buf[i] = current_char;
      // Echo karakter ke layar dengan warna saat ini
      interrupt(0x10, 0x0E00 | current_char, (0x00 << 8) | (current_text_attribute & 0x0F), 0x0000, 0x0000);
      i++;
    }
  }
  buf[127] = '\0';
  printString("\n"); // Akan menggunakan warna saat ini
}

// Modifikasi fungsi untuk membersihkan layar dengan warna saat ini
void clearScreen() {

  interrupt(0x10, 0x0600, (current_text_attribute << 8) | 0x00, 0x0000, 0x184F);

  interrupt(0x10, 0x0200, 0x0000, 0x0000, 0x0000);
}
