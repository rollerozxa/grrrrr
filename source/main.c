#include <grrlib.h>

#include <stdlib.h>
#include <stdio.h>
#include <wiiuse/wpad.h>
#include <ogc/lwp_watchdog.h>
#include <ogc/stm.h>
#include <math.h>

#include "hsv2rgb.h"

// Font
#include "FreeMonoBold_ttf.h"

#include "blaahaj_jpg.h"

int main(int argc, char **argv) {

	GRRLIB_Init();

	WPAD_Init();

	GRRLIB_ttfFont *myFont = GRRLIB_LoadTTF(FreeMonoBold_ttf, FreeMonoBold_ttf_size);

	GRRLIB_texImg *blaahaj = GRRLIB_LoadTexture(blaahaj_jpg);

	GRRLIB_Settings.antialias = true;

	GRRLIB_SetBackgroundColour(0x00, 0x00, 0x00, 0xFF);

	double timer = 0;

	char text[] = "Hello Wii Homebrew World...";

	char printchar[2] = {0,0};

	while (1) {
		WPAD_ScanPads();

		if (WPAD_ButtonsDown(0) & WPAD_BUTTON_HOME)
			break;

		for (size_t i = 0; i < sizeof(text)-1; i++) {
			int xOffset = (i*15);
			int yOffset = (int)(sin(timer/15+i)*10);

			int color = hsv2rgb_grr(( ((int)timer*2) + (i*10) ) % 360, 100, 100);

			for (size_t j = 0; j < 3; j++) {
				if (j == 1) printchar[0] = text[i];
				else		printchar[0] = '=';

				int x = 680+xOffset-timer;
				int y = (24+j*24)+yOffset;

				GRRLIB_PrintfTTF(x, y, myFont, printchar, 24, color);
			}
		}

		//GRRLIB_DrawImg(250, 150, blaahaj, 0, 1, 1, 0xFFFFFFFF);


		//GRRLIB_PrintfTTF(24, 24, myFont, "Hello Wii...", 24, 0xFFFFFFFF);

		timer++;

		GRRLIB_Render();
	}

	GRRLIB_FreeTTF(myFont);
	GRRLIB_Exit();

	exit(0);
}
