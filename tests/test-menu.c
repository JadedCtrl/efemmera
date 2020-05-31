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

	draw_menu ( testMenu->surface, testMenu );
	spBlitSurface( spGetWindowSurface()->w/2, spGetWindowSurface()->h/2, 0,
		       testMenu->surface );

	spFontDrawMiddle( spGetWindowSurface()->w/2,
		          spGetWindowSurface()->h-fonts[0]->maxheight*2.5, 0,
			  "Press [S] to select", fonts[0] );
	spFontDrawMiddle( spGetWindowSurface()->w/2,
		          spGetWindowSurface()->h-fonts[0]->maxheight-2, 0,
			  "Press [E] to exit", fonts[0] );
	spFlip();
}

// input for the menu test
int
calc_test ( Uint32 steps )
{
	int menucode = calc_menu ( testMenu, SP_BUTTON_START );
	if ( menucode == -1 )
		if ( spGetInput()->button[SP_BUTTON_SELECT] )
			return -1;
	else
		return 0;

	if ( menucode > 0 )
		spSleep(700000);
		// sleep long enough after selection to play selection sound lol
	return menucode;
}

void
resize ( Uint16 w, Uint16 h )
{
	spSelectRenderTarget(spGetWindowSurface());
	resize_fonts();
	resize_menu(testMenu);
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
	init_menu( menu, "what do you do? <3", &fonts[1], &fonts[0],
		   spGetRGB(80,80,80), spGetRGB(35,71,107) );
	menu->titleCentered = 0;
	menu->textCentered = 0;
	menu->moveSound = sounds[0];
	menu->selectSound = sounds[1];
	add_menu_element(menu, "give up");
	add_menu_element(menu, "run away");
	add_menu_element(menu, "eat a baby");
	add_menu_element(menu, "wave hello");
	add_menu_element(menu, "hug a stranger until they blush");
	add_menu_element(menu, "oh well");
}	

void
init_fonts ( void )
{
	add_font("data/font/cozette-vector.ttf");
	add_font("data/font/love_me_chain.ttf");
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
	add_sound("data/sound/tamborine.ogg");
	add_sound("data/sound/eeuh.ogg");
}


// ============================================================================
// CLEANUP
// ============================================================================
int
cleanup ( void )
{
	cleanup_fonts();
	cleanup_sounds();
	spDeleteSurface( menuSurface );
	spQuitCore();
}
