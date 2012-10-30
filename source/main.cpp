/* vim: ts=4 sw=4 noexpandtab
 * Tales of Darwinia
 *
 * A Game by Yelp Engineers
 *
 * Henri Bai
 * Paul Berens
 * Patrick Tiet
 * Kevin Lange
 *
 */

#include <nds.h>
#include <stdio.h>

volatile int frame = 0;

void Vblank() {
	frame++;
}

int main(void) {

	touchPosition touchXY;

	irqSet(IRQ_VBLANK, Vblank);

	consoleDemoInit();

	iprintf("Tales of Darwinia\n");

	while(1) {

		swiWaitForVBlank();
		touchRead(&touchXY);

		iprintf("\033[23;0H%d  %d,%d        ", frame, touchXY.px, touchXY.py);
	
	}

	return 0;
}
