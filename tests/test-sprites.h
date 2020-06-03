#include <sparrow3d.h>

#define FN_COZETTE	0
#define FN_LOVEMECHAIN	1
#define SF_TAMBORINE	0
#define SF_EEUH		1

SDL_Surface* screen;
SDL_Surface* sprites;

spSpritePointer sprite;
spSpriteCollectionPointer collection;

int  calc_test		( Uint32 );
void draw_test		( void );
void draw_hud		( void );
void resize		( Uint16, Uint16 );

int init		( void );

void init_sprites	( void );
void init_fonts		( void );
void init_sounds	( void );
void init_sparrow3d	( void );

int cleanup		( void );
