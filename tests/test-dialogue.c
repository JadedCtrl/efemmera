#include <sparrow3d.h>
#include <string.h>
#include "../lib/font.h"
#include "../lib/scene.h"
#include "test-dialogue.h"

SDL_Surface* screen = NULL;

struct eScene* mainScene = NULL;
struct eActor* girl = NULL;

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
	spSelectRenderTarget(spGetWindowSurface());
	spClearTarget( spGetRGB(64,64,64) );

	screen = spGetWindowSurface();
	drawScene( mainScene );
	spBlitSurface(screen->w/2,screen->h/2,0, mainScene->surface);

	spFlip();
}

// input for the sprite test
int
calc_test ( Uint32 steps )
{
	if ( spGetInput()->button[SP_BUTTON_SELECT] )
		return -1;
	return 0;
}

void
resize ( Uint16 w, Uint16 h )
{
	spSelectRenderTarget( spGetWindowSurface());
	resizeScene( mainScene );
	resizeActor( girl );
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
	init_scenes();
	resize( spGetWindowSurface()->w, spGetWindowSurface()->h );
}
 
void
init_fonts ( void )
{
	addFont("data/font/cozette-vector.ttf");
	addFont("data/font/love_me_chain.ttf");
}

void
init_scenes ( void )
{
	girl = malloc(sizeof(struct eActor));
	initActor(girl, "Girl");
	addEmote(girl, "data/image/girls_are_weird/girl_happy.png");
	addEmote(girl, "data/image/girls_are_weird/girl_bored.png");
	addEmote(girl, "data/image/girls_are_weird/girl_sad.png");

	addEmote(girl, "data/image/girls_are_weird/girl_angry.png");
	girl->emoteSelection = GIRL_HAPPY;

	mainScene = malloc(sizeof(struct eScene));
	initScene(mainScene, "data/image/girls_are_weird/background.png", girl);
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
