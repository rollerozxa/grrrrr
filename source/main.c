#include <grrlib.h>

#include <stdlib.h>
#include <stdio.h>
#include <wiiuse/wpad.h>
#include <ogc/lwp_watchdog.h>
#include <ogc/stm.h>
#include <math.h>

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

	while (1) {
		WPAD_ScanPads();

		if (WPAD_ButtonsDown(0) & WPAD_BUTTON_HOME)
			break;

		char text[]   = "Hello Wii Homebrew World...";

		int gay[] = { // THE GAY ARRAY
			0xDC0404FF,
			0xF78801FF,
			0xF6E701FF,
			0x007D26FF,
			0x004CF8FF,
			0x710783FF
		};

		int gayindex = 0; // THE GAY INDEX

		for (size_t i = 0; i < sizeof(text)-1; i++) {
			char tmp[] = {text[i], 0};
			char tmp2[] = {'-', 0};

			int xOffset = (i*15);
			int yOffset = (int)(sin(timer/15+i)*10);

			GRRLIB_PrintfTTF(
				24+xOffset,
				48+yOffset,
				myFont, tmp, 24,
				gay[gayindex%6]
			);

			GRRLIB_PrintfTTF(
				24+xOffset,
				24+yOffset,
				myFont, tmp2, 24,
				gay[gayindex%6]
			);

			GRRLIB_PrintfTTF(
				24+xOffset,
				72+yOffset,
				myFont, tmp2, 24,
				gay[gayindex%6]
			);

			gayindex++;
		}

		GRRLIB_DrawImg(250, 150, blaahaj, 0, 1, 1, 0xFFFFFFFF);


		//GRRLIB_PrintfTTF(24, 24, myFont, "Hello Wii...", 24, 0xFFFFFFFF);

		timer++;

		GRRLIB_Render();
	}

	GRRLIB_FreeTTF(myFont);
	GRRLIB_Exit();

	exit(0);
}
