#include <sparrow3d.h>

int fontCount;
spFontPointer fonts[10];
char fontPaths[10][512];


void add_font		( char ttf_path[512] );

void resize_fonts	( void );
void resize_font	( spFontPointer*, char[512] );

void cleanup_fonts	( void );
