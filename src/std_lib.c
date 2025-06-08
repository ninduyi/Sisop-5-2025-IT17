#include "std_lib.h"

int div(int a, int b) {
  int negative;
  int result;
  negative = 0;
  result = 0;

  if (b == 0) return 0; // Avoid division by zero

  if (a < 0) {
    a = -a;
    negative = !negative;
  }
  if (b < 0) {
    b = -b;
    negative = !negative;
  }

  while (a >= b) {
    a = a - b;
    result++;
  }

  if (negative) result = -result;
  return result;
}

int mod(int a, int b) {
  int negative = 0;

  if (b == 0) return 0;

  if (a < 0) {
    a = -a;
    negative = 1;
  }
  if (b < 0) b = -b;

  while (a >= b) {
    a = a - b;
  }

  if (negative) a = -a;
  return a;
}

bool strcmp(char *str1, char *str2) {
  int i = 0;
  while (str1[i] != '\0' && str2[i] != '\0') {
    if (str1[i] != str2[i]) {
      return false;
    }
    i++;
  }
  return (str1[i] == '\0' && str2[i] == '\0');
}

void strcpy(char *dst, char *src) {
  int i = 0;
  while (src[i] != '\0') {
    dst[i] = src[i];
    i++;
  }
  dst[i] = '\0'; // Jangan lupa null terminator
}

void clear(byte *buf, unsigned int size) {
  // TODO: Implementasi pembersihan buffer
}

void atoi(char *str, int *num) {
  int i = 0;
  int sign = 1;
  int result = 0;

  if (str[0] == '-') {
    sign = -1;
    i++;
  }

  while (str[i] != '\0') {
    result = result * 10 + (str[i] - '0');
    i++;
  }

  *num = sign * result;
}


  // TODO: Implementasi konversi integer ke string
  // NOTE: HARUS BISA ANGKA NEGATIF
void itoa(int num, char *str) {
  int i = 0;
  int isNegative = 0;
  char tempStr[20];
  int j;

  if (num == 0) {
    str[0] = '0';
    str[1] = '\0';
    return;
  }

  if (num < 0) {
    isNegative = 1;
    num = -num;
  }

  while (num != 0) {
    int remainder = mod(num, 10);
    tempStr[i++] = remainder + '0';
    num = div(num, 10);
  }

  if (isNegative) {
    tempStr[i++] = '-';
  }

  for (j = 0; j < i; j++) {
    str[j] = tempStr[i - j - 1];
  }
  str[j] = '\0';
}
