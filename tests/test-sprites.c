#include <sparrow3d.h>
#include <string.h>
#include "../lib/font.h"
#include "test-sprites.h"

SDL_Surface* screen = NULL;
SDL_Surface* sprites_texture = NULL;

spSpritePointer sprite;
spSpriteCollectionPointer collection;

// ============================================================================

int
main ( int argc, char **argv )
{
	init();
	spLoop( draw_test, calc_test, 10, resize, NULL );

	cleanup();
	return 0;
}

// ============================================================================
// TEST
// ============================================================================
// draw this whole sprite test (aka, simple background, text, and the sprites.)
void
draw_test ( void )
{
	spClearTarget( spGetRGB(64,64,64) );
	spSelectRenderTarget(spGetWindowSurface());

	screen = spGetWindowSurface();
	sprite->zoomX *= -1;
	sprite->zoomX = sprite->zoomY = spGetSizeFactor() ;
	spDrawSprite( 4 * screen->w / 5, 5 * screen->h / 8, 0, sprite );

	draw_hud( );

	spFlip();
}

void
draw_hud ( )
{
	spFontDrawMiddle( spGetWindowSurface()->w/2,
			  spGetWindowSurface()->h
			  - fonts[FN_COZETTE]->maxheight -2, 0,
			  "Press [E] to exit", fonts[FN_COZETTE] );
}

// input for the sprite test
int
calc_test ( Uint32 steps )
{
	spUpdateSprite( sprite, steps );
	if ( spGetInput()->button[SP_BUTTON_SELECT] )
		return -1;
	return 0;
}

void
resize ( Uint16 w, Uint16 h )
{
	spSelectRenderTarget( spGetWindowSurface());
	resizeFonts();
}


// ============================================================================
// INIT
// ============================================================================
int
init ( void )
{
	init_sparrow3d();
	init_fonts();
	init_sprites();
	resize( spGetWindowSurface()->w, spGetWindowSurface()->h );
}
 
void
init_fonts ( void )
{
	addFont("data/font/cozette-vector.ttf");
	addFont("data/font/love_me_chain.ttf");
}

void
init_sprites ( void )
{
	sprites_texture = spLoadSurface( "data/sprite/scientist.png" );
	collection = spLoadSpriteCollection("data/sprite/scientist.ssc",sprites_texture);
	sprite = spActiveSprite(collection);
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


// ============================================================================
// CLEANUP
// ============================================================================
int
cleanup ( void )
{
	cleanupFonts();
	spQuitCore();
}
