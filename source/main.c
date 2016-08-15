#include <stdlib.h>
#include <stdio.h>
#include <3ds.h>
#include "http.h"
#include "pid.h"
#include "catch.h"
#include "util.h"
#include "database.h"
#include "inject.h"
#include "pokemon.h"

#define ENTRIES 12

#define V1 1
#define V2 9
#define V3 3

void intro(PrintConsole topScreen, PrintConsole bottomScreen, int currentEntry, char* menuEntries[]){
	consoleSelect(&bottomScreen);
	printf("\x1b[26;0HEvent Assistant v%d.%d.%d", V1, V2, V3);
	printf("\n\nBernardo Giordano & ctrulib");
	consoleSelect(&topScreen);
	printf("\x1b[2J");
	printf("\x1b[47;1;34m                  EventAssistant                  \x1b[0m\n");

	refresh(currentEntry, topScreen, menuEntries, ENTRIES);

	consoleSelect(&topScreen);
	printf("\x1b[29;15HPress Start to exit.");
}

int main() {
	gfxInitDefault();
	aptInit();

	PrintConsole topScreen, bottomScreen;
	consoleInit(GFX_TOP, &topScreen);
	consoleInit(GFX_BOTTOM, &bottomScreen);

	char *menuEntries[ENTRIES] = {"Gen VI's Event Database", "Save file editor", "Pokemon editor", "Wi-Fi distributions", "Code distributions", "Local distributions", "Capture probability calculator", "PID Checker", "Common PS dates database", "Changelog", "Credits", "Update .cia"};
	int currentEntry = 0;
	
	int game[1] = {0};
	
	// initializing save file editor variables
	int nInjected[3] = {0, 0, 0};
	int injectCont[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	
	// initializing pokemon editor variables
	int pokemonCont[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	/*
		0 : currentEntry
	    1 : boxnumber
		2 : indexnumber
		3 : NotOTfriendship counter
		4 : EVs counter
		5 : Hidden Power counter
		6 : clone boxnumber
		7 : clone indexnumber
	*/

	consoleSelect(&topScreen);
	intro(topScreen, bottomScreen, currentEntry, menuEntries);

	while (aptMainLoop()) {
		gspWaitForVBlank();
		hidScanInput();

		if (hidKeysDown() & KEY_START)
			break;

		if (hidKeysDown() & KEY_DUP) {
			if (currentEntry == 0) {
				currentEntry = ENTRIES - 1;
				refresh(currentEntry, topScreen, menuEntries, ENTRIES);
			}
			else if (currentEntry > 0) {
				currentEntry--;
				refresh(currentEntry, topScreen, menuEntries, ENTRIES);
			}
		}

		if (hidKeysDown() & KEY_DDOWN) {
			if (currentEntry == ENTRIES - 1) {
				currentEntry = 0;
				refresh(currentEntry, topScreen, menuEntries, ENTRIES);
			}
			else if (currentEntry < ENTRIES - 1) {
				currentEntry++;
				refresh(currentEntry, topScreen, menuEntries, ENTRIES);
			}
		}

		if (hidKeysDown() & KEY_A) {
			switch (currentEntry) {
				case 0 : {
					eventDatabase(topScreen, bottomScreen, game);
					consoleSelect(&bottomScreen);
					printf("\x1b[2J");
					consoleSelect(&topScreen);
					intro(topScreen, bottomScreen, currentEntry, menuEntries);
					break;
				}

				case 1 : {
					int ret = saveFileEditor(topScreen, bottomScreen, game, nInjected, injectCont);
					consoleSelect(&bottomScreen);
					if (ret == 1) printf("\x1b[6;0H\x1b[32mSettings changed correctly\x1b[0m.");
					else if (ret != 1 && ret != 0) printf("\x1b[6;0HAn error occurred.");
					if (ret == -1) printf("\x1b[31m Game not found\x1b[0m.");
					else if (ret == -2) printf("\x1b[31m Maximum items reached\x1b[0m");
					else if (ret == -13) printf("\x1b[31m Game selected doesn'tmatch the game chosen previously\x1b[0m.");
					printf("\nPress B to return.");

					if (ret != 0) {
						while (aptMainLoop()) {
							gspWaitForVBlank();
							hidScanInput();

							if (hidKeysDown() & KEY_B) break;

							gfxFlushBuffers();
							gfxSwapBuffers();
						}
					}

					printf("\x1b[2J");
					consoleSelect(&topScreen);
					intro(topScreen, bottomScreen, currentEntry, menuEntries);
					break;
				}
				
				case 2 : {
					int ret = pokemonEditor(topScreen, bottomScreen, game, pokemonCont);
					consoleSelect(&bottomScreen);
					if (ret == 1) printf("\x1b[6;0H\x1b[32mChanges applied correctly\x1b[0m.");
					else if (ret != 1 && ret != 0) printf("\x1b[6;0HAn error occurred.");
					if (ret == -1) printf("\x1b[31m Game not found\x1b[0m.");
					else if (ret == -3) printf("\x1b[31m No pokemon found in the selected location\x1b[0m.");
					else if (ret == -13) printf("\x1b[31m Game selected doesn'tmatch the game chosen previously\x1b[0m.");
					printf("\nPress B to return.");

					if (ret != 0) {
						while (aptMainLoop()) {
							gspWaitForVBlank();
							hidScanInput();

							if (hidKeysDown() & KEY_B) break;

							gfxFlushBuffers();
							gfxSwapBuffers();
						}
					}

					printf("\x1b[2J");
					consoleSelect(&topScreen);
					intro(topScreen, bottomScreen, currentEntry, menuEntries);
					break;
				}

				case 3 :  {
					printDistro(topScreen, bottomScreen, "https://raw.githubusercontent.com/BernardoGiordano/EventAssistant/master/resources/worldwide1.txt");
					consoleSelect(&bottomScreen);
					printf("\x1b[2J");
					consoleSelect(&topScreen);
					intro(topScreen, bottomScreen, currentEntry, menuEntries);
					break;
				}

				case 4 : {
					printDistro(topScreen, bottomScreen, "https://raw.githubusercontent.com/BernardoGiordano/EventAssistant/master/resources/worldwide2.txt");
					consoleSelect(&bottomScreen);
					printf("\x1b[2J");
					consoleSelect(&topScreen);
					intro(topScreen, bottomScreen, currentEntry, menuEntries);
					break;
				}

				case 5 : {
					printDistro(topScreen, bottomScreen, "https://raw.githubusercontent.com/BernardoGiordano/EventAssistant/master/resources/local.txt");
					consoleSelect(&bottomScreen);
					printf("\x1b[2J");
					consoleSelect(&topScreen);
					intro(topScreen, bottomScreen, currentEntry, menuEntries);
					break;
				}

				case 6 : {
					catchrate(topScreen, bottomScreen);
					consoleSelect(&bottomScreen);
					printf("\x1b[2J");
					consoleSelect(&topScreen);
					intro(topScreen, bottomScreen, currentEntry, menuEntries);
					break;
				}

				case 7 : {
					PID(topScreen, bottomScreen);
					consoleSelect(&bottomScreen);
					printf("\x1b[2J");
					consoleSelect(&topScreen);
					intro(topScreen, bottomScreen, currentEntry, menuEntries);
					break;
				}

				case 8 : {
					psDates(topScreen, bottomScreen);
					consoleSelect(&bottomScreen);
					printf("\x1b[2J");
					consoleSelect(&topScreen);
					intro(topScreen, bottomScreen, currentEntry, menuEntries);
					break;
				}

				case 9 : {
					printDistro(topScreen, bottomScreen, "https://raw.githubusercontent.com/BernardoGiordano/EventAssistant/master/resources/info.txt");
					consoleSelect(&bottomScreen);
					printf("\x1b[2J");
					consoleSelect(&topScreen);
					intro(topScreen, bottomScreen, currentEntry, menuEntries);
					break;
				}

				case 10 : {
					credits(topScreen, bottomScreen);
					consoleSelect(&bottomScreen);
					printf("\x1b[2J");
					consoleSelect(&topScreen);
					intro(topScreen, bottomScreen, currentEntry, menuEntries);
					break;
				}

				case 11 : {
					update(topScreen, bottomScreen);
					consoleSelect(&bottomScreen);
					printf("\x1b[2J");
					consoleSelect(&topScreen);
					intro(topScreen, bottomScreen, currentEntry, menuEntries);
					break;
				}
			}
		}

		gfxFlushBuffers();
		gfxSwapBuffers();
	}

    aptExit();
	gfxExit();
	return 0;
}
