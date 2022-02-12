#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"

int getsw(void) {
	return ((PORTD & 0x00000f00) >> 8); /* 0000 0000 0000 0000 0000 1111 0000 0000 = 0x00000f00 */
}

int getbtns(void) {
	return ((PORTD & 0x000000e0) >> 5); /* 0000 0000 0000 0000 0000 0000 1110 0000 = 0x000000e0 */
}
