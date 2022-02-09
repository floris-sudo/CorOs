//0xA0000 for EGA / VGA graphics modes(64 KB)
//0xB0000 for monochrome text mode(32 KB)
//0xB8000 for color text modeand CGA - compatible graphics modes(32 KB)

#include "kernel.h"

uint32 vga_index;

static uint32 next_line_index = 1;

uint8 g_fore_color = WHITE, g_back_color = BLUE;

int digit_ascii_codes[10] = { 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39 };

/*
16 bit video buffer elements(register ax)
8 bits(ah) higher :
  lower 4 bits - forec olor
  higher 4 bits - back color

8 bits(al) lower :
  8 bits : ASCII character to print
*/

uint16 vga_entry(unsigned char ch, uint8 fore_color, uint8 back_color) {
	
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

void clear_vga_buffer(uint16** buffer, uint8 fore_color, uint8 back_color) {

	uint32 i;
	for (i = 0; i < BUFSIZE; i++) {

		(*buffer)[i] = vga_entry(NULL, fore_color, back_color);

	}

	next_line_index = 1;
	vga_index = 0;

}

void init_vga(uint8 fore_color, uint8 back_color) {

	vga_buffer = (uint16*)VGA_ADDRESS;
	clear_vga_buffer(&vga_buffer, fore_color, back_color);
	g_fore_color = fore_color;
	g_back_color = back_color;

}

void print_new_line() {

	if (next_line_index >= 55) {

		next_line_index = 0;
		clear_vga_buffer(&vga_buffer, g_fore_color, g_back_color);

	}

	vga_index = 80 * next_line_index;
	next_line_index++;

}

void print_char(char ch) {

	vga_buffer[vga_index] = vga_entry(ch, g_fore_color, g_back_color);
	vga_index++;

}

uint32 strlen(const char* str) {


	uint32 length = 0;
	while (str[length]) {

		length++;

	}

	return length;
}

uint32 digit_count(int num) {

	uint32 count = 0;

	if (num == 0) {

		return 1;

	}
	
	while (num > 0) {

		count++;
		num = num / 10;

	}

	return count;

}

