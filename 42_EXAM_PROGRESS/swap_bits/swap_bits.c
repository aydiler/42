#include <stdio.h>

unsigned char swap_bits(unsigned char octet)
{
	unsigned char upper;
	unsigned char lower;

	upper = (octet & 0xF0) >> 4;
	lower = (octet & 0x0F) << 4;
	unsigned char new = lower | upper;
	return new;
}
