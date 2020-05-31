#include <sparrow3d.h>
#include <string.h>
#include "font.h"

int fontCount = 0;
spFontPointer fonts[10] = { NULL };
char fontPaths[10][512];


// ============================================================================
// add a TTF font at given path to the global `font` array
void
add_font ( char ttf_path[512] )
{
	strcpy(fontPaths[fontCount], ttf_path);
	fontCount++;
	resize_fonts();
}

// ============================================================================
// resizes/updates all fonts; should be run whenever window resizes
void
resize_fonts ( void )
{
	for ( int i = 0; i < fontCount; i++ ) {
		resize_font(&fonts[i], fontPaths[i]);
	}
}

// resizes/updates a given font
void
resize_font ( spFontPointer* font, char ttf_path[512] )
{
	spFontShadeButtons(1);
	
	if ( *(font) )
		spFontDelete( *(font) );

	*(font) = spFontLoad( ttf_path,
		           spFixedToInt(10 * spGetSizeFactor()) );
	spFontSetShadeColor(0);
	
	//Every letter you want to use, you have to add here. 63345 is spGetRGB
	spFontAdd( *(font), SP_FONT_GROUP_ASCII, 65535 ); //whole ASCII
	spFontAddBorder( *(font), 0 );
	
	//Have a look, how [S] in line 21 is drawn as a Button image.
	spFontAddButton( *(font), 'E', SP_BUTTON_SELECT_NAME, 65535,
		         spGetRGB( 64, 64, 64 ) );
	spFontAddButton( *(font), 'S', SP_BUTTON_START_NAME, 65535,
		         spGetRGB( 64, 64, 64 ) );
}

// ============================================================================
// cleans up all fonts in global array `fonts`
void
cleanup_fonts ( void )
{
	for ( int i = 0; i < fontCount; i++ ) {
		spFontDelete( fonts[i] );
	}
}

