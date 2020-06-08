#include <sparrow3d.h>

#define FN_COZETTE	0
#define FN_LOVEMECHAIN	1
#define SF_TAMBORINE	0
#define SF_EEUH		1

#define GIRL_HAPPY	0
#define GIRL_BORED	1
#define GIRL_SAD	2
#define GIRL_ANGRY	3


int  calc_test		( Uint32 );
void draw_test		( void );
void draw_scene		( void );
void draw_hud		( void );
void resize		( Uint16, Uint16 );

int init		( void );

void init_scenes	( void );
void init_images	( void );
void init_fonts		( void );
void init_sparrow3d	( void );

int cleanup		( void );
