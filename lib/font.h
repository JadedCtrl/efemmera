#include <sparrow3d.h>

int fontCount;
spFontPointer fonts[10];
char fontPaths[10][512];


void addFont		( char ttf_path[512] );

void resizeFonts	( void );
void resizeFont		( spFontPointer*, char[512] );

void cleanupFonts	( void );
