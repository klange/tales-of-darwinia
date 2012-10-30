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

	PrintConsole top_screen;

	videoSetMode(MODE_0_2D);
	videoSetModeSub(MODE_0_2D);

	vramSetBankA(VRAM_A_MAIN_BG);
	vramSetBankC(VRAM_C_SUB_BG);

	consoleInit(&top_screen, 3,BgType_Text4bpp, BgSize_T_256x256, 31, 0, true, true);

	irqSet(IRQ_VBLANK, Vblank);

	iprintf("Tales of Darwinia\n");

	while(1) {

		swiWaitForVBlank();
		touchRead(&touchXY);

		iprintf("\033[23;0H%d  %d,%d        ", frame, touchXY.px, touchXY.py);
	
	}

	return 0;
}
