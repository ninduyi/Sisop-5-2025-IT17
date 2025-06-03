#include "std_lib.h"

/* Integer division without using / */
int div(int a, int b) {
  int quotient, sign, abs_a, abs_b;

  quotient = 0;
  if (b == 0) return 0; /* Avoid division by zero */
  sign = 1;
  if (a < 0) {
    sign = -sign;
    abs_a = -a;
  } else {
    abs_a = a;
  }
  if (b < 0) {
    sign = -sign;
    abs_b = -b;
  } else {
    abs_b = b;
  }
  while (abs_a >= abs_b) {
    abs_a = abs_a - abs_b;
    quotient++;
  }
  return sign * quotient;
}

/* Modulus without using persen simbol */
int mod(int a, int b) {
  int abs_a, abs_b;

  if (b == 0) return 0; /* Avoid modulus by zero */
  if (a < 0) {
    abs_a = -a;
  } else {
    abs_a = a;
  }
  if (b < 0) {
    abs_b = -b;
  } else {
    abs_b = b;
  }
  while (abs_a >= abs_b) {
    abs_a = abs_a - abs_b;
  }
  if (a < 0) {
    return -abs_a;
  }
  return abs_a;
}

/* Compare two strings */
bool strcmp(char *str1, char *str2) {
  while (*str1 && *str2 && *str1 == *str2) {
    str1++;
    str2++;
  }
  return *str1 == *str2;
}

/* Copy string from src to dst */
void strcpy(char *dst, char *src) {
  while (*src) {
    *dst = *src;
    dst++;
    src++;
  }
  *dst = '\0';
}

/* Clear buffer with zeros */
void clear(byte *buf, unsigned int size) {
  unsigned int i;

  for (i = 0; i < size; i++) {
    buf[i] = 0;
  }
}

/* Convert string to integer */
void atoi(char *str, int *num) {
  int sign, i;

  *num = 0;
  sign = 1;
  i = 0;
  if (str[0] == '-') {
    sign = -1;
    i++;
  }
  while (str[i] >= '0' && str[i] <= '9') {
    *num = *num * 10 + (str[i] - '0');
    i++;
  }
  *num = *num * sign;
}

/* Convert integer to string */
void itoa(int num, char *str) {
  int i, j, digits, temp, sign;
  char buf[12]; /* Enough for -2147483648 + null */

  i = 0;
  if (num == 0) {
    str[0] = '0';
    str[1] = '\0';
    return;
  }
  sign = 1;
  if (num < 0) {
    sign = -1;
    num = -num;
    str[i++] = '-';
  }
  temp = num;
  digits = 0;
  while (temp > 0) {
    buf[digits] = mod(temp, 10) + '0'; /* Use custom mod */
    temp = div(temp, 10); /* Use custom div */
    digits++;
  }
  for (j = digits - 1; j >= 0; j--) {
    str[i] = buf[j];
    i++;
  }
  str[i] = '\0';
}
