#include <sparrow3d.h>
#include <string.h>
#include "../lib/font.h"
#include "../lib/sound.h"
#include "../lib/menu.h"
#include "test-menu.h"

SDL_Surface* screen = NULL;
SDL_Surface* menuSurface = NULL;

struct eMenu* testMenu;

// ============================================================================

int
main ( int argc, char **argv )
{
	testMenu = malloc(sizeof(struct eMenu));

	init();
	int ret_code = spLoop( draw_test, calc_test, 10, resize, NULL );
	cleanup();

	if ( ret_code != -1 ) {
		ret_code--;
		struct eMenuElement* targetElement = testMenu->elements[ret_code];
		printf("Here's the menu item you selected:\n");
		printf("Index: %i\tText: %s\n", ret_code, targetElement->text);
	}

	return 0;
}

// ============================================================================
// TEST
// ============================================================================
// draw this whole menu test (aka, simple background, text, and the testMenu.
void
draw_test ( void )
{
	spClearTarget( spGetRGB(64,64,64) );
	spSelectRenderTarget(spGetWindowSurface());

	drawMenu ( testMenu );
	spBlitSurface( spGetWindowSurface()->w/2, spGetWindowSurface()->h/2, 0,
		       testMenu->surface );

	spFontDrawMiddle( spGetWindowSurface()->w/2,
		          spGetWindowSurface()->h
			  - fonts[FN_COZETTE]->maxheight * 2.5, 0,
			  "Press [S] to select", fonts[FN_COZETTE] );
	spFontDrawMiddle( spGetWindowSurface()->w/2,
	          spGetWindowSurface()->h
			  - fonts[FN_COZETTE]->maxheight -2, 0,
			  "Press [E] to exit", fonts[FN_COZETTE] );
	spFlip();
}

// input for the menu test
// if non-zero return int, it's the index of the selected menu item + 1.
int
calc_test ( Uint32 steps )
{
	int menucode = calcMenu( testMenu, SP_BUTTON_START, steps );
	// no input? interpret keypress as our own
	if ( menucode == CALCMENU_NOINPUT ) {
		if ( spGetInput()->button[SP_BUTTON_SELECT] )
			return -1;
		return 0;
	}
	// greater than _MOVED means it returned the inc'd menu selection index
	if ( menucode > CALCMENU_MOVED )
		spSleep(700000);
		// sleep long enough after selection to play selection sound lol
	return menucode;
}

void
resize ( Uint16 w, Uint16 h )
{
	spSelectRenderTarget( spGetWindowSurface());
	resizeFonts();
	resizeMenu( testMenu );
}


// ============================================================================
// INIT
// ============================================================================
int
init ( void )
{
	init_sparrow3d();
	init_sounds();
	init_fonts();
	init_test_menu(testMenu);
	resize( spGetWindowSurface()->w, spGetWindowSurface()->h );
}
 
void
init_test_menu ( struct eMenu* menu )
{
	initMenu( menu, "what do you do? <3",
		  &fonts[FN_LOVEMECHAIN], &fonts[FN_COZETTE],
		  spGetRGB(80,80,80), spGetRGB(35,71,107) );
	menu->titleCentered = 0;
	menu->textCentered = 0;
	menu->moveSound   = sounds[SF_TAMBORINE];
	menu->selectSound = sounds[SF_EEUH];
	addMenuElement(menu, "give up");
	addMenuElement(menu, "run away");
	addMenuElement(menu, "eat a baby");
	addMenuElement(menu, "wave hello");
	addMenuElement(menu, "hug a stranger until they blush");
	addMenuElement(menu, "oh well");
}	

void
init_fonts ( void )
{
	addFont("data/font/cozette-vector.ttf");
	addFont("data/font/love_me_chain.ttf");
}

void
init_sparrow3d ( void )
{
	spSetDefaultWindowSize( 320, 240 );
	spInitCore();
	spCreateDefaultWindow();
	spSetZSet(0);
	spSetZTest(0);
}

void
init_sounds ( void )
{
	spSoundInit();
	addSound("data/sound/tamborine.ogg");
	addSound("data/sound/eeuh.ogg");
}


// ============================================================================
// CLEANUP
// ============================================================================
int
cleanup ( void )
{
	cleanupFonts();
	cleanupSounds();
	spDeleteSurface( menuSurface );
	spQuitCore();
}
