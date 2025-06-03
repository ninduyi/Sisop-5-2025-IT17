#ifndef __KERNEL_H__
#define __KERNEL_H__

#include "std_type.h"

// BIOS Color Attributes (Background is Black 0x0?)
#define ATTRIBUTE_DEFAULT       0x07 // Light Gray on Black
#define ATTRIBUTE_MAELSTROM     0x04 // Red on Black
#define ATTRIBUTE_TWIN_ADDER    0x0E // Light Yellow on Black
#define ATTRIBUTE_IMMORTAL_FLAMES 0x09 // Light Blue on Black


extern void putInMemory(int segment, int address, char character);
extern int interrupt(int number, int AX, int BX, int CX, int DX);
unsigned int getBiosTick();

void printString(char* str);
void readString(char* buf);
void clearScreen();
void setTextColor(byte attribute); // Fungsi baru untuk mengatur warna teks

#endif // __KERNEL_H__
