﻿//0xA0000 for EGA / VGA graphics modes(64 KB)
//0xB0000 for monochrome text mode(32 KB)
//0xB8000 for color text modeand CGA - compatible graphics modes(32 KB)

#include "kernel.h"

/*
16 bit video buffer elements(register ax)
8 bits(ah) higher :
  lower 4 bits - forec olor
  higher 4 bits - back color

8 bits(al) lower :
  8 bits : ASCII character to print
*/

uint16 vga_entry(unsigned char ch, uint8 fore_color, uint8 back_color) 
{
	uint16 ax = 0;
	uint8 ah = 0, al = 0;
	ah = back_color;
	ah <<= 4;
	ah |= fore_color;
	ax = ah;
	ax <<= 8;
	al = ch;
	ax |= al;

	return ax;
}

void clear_vga_buffer(uint16** buffer, uint8 fore_color, uint8 back_color) 
{
	uint32 i;
	for (i = 0; i < BUFSIZE; i++) {
		(*buffer)[i] = vga_entry(NULL, fore_color, back_color);
	}
}

void init_vga(uint8 fore_color, uint8 back_color)
{
	vga_buffer = (uint16*)VGA_ADDRESS;
	clear_vga_buffer(&vga_buffer, fore_color, back_color);
}

void kernel_entry()
{
	init_vga(WHITE, BLACK);

	vga_buffer[0] = vga_entry('H', WHITE, BLACK);
	vga_buffer[1] = vga_entry('E', WHITE, BLACK);
	vga_buffer[2] = vga_entry('L', WHITE, BLACK);
	vga_buffer[3] = vga_entry('L', WHITE, BLACK);
	vga_buffer[4] = vga_entry('O', WHITE, BLACK);
	vga_buffer[5] = vga_entry(' ', WHITE, BLACK);
	vga_buffer[6] = vga_entry('W', WHITE, BLACK);
	vga_buffer[7] = vga_entry('O', WHITE, BLACK);
	vga_buffer[8] = vga_entry('R', WHITE, BLACK);
	vga_buffer[9] = vga_entry('L', WHITE, BLACK);
	vga_buffer[10] = vga_entry('D', WHITE, BLACK);

	
}