#include <sparrow3d.h>

#define FN_COZETTE	0
#define FN_LOVEMECHAIN	1
#define SF_TAMBORINE	0
#define SF_EEUH		1

int  calc_test		( Uint32 );
void draw_test		( void );
void resize		( Uint16, Uint16 );

int init		( void );

void init_fonts		( void );
void init_sparrow3d	( void );
void init_sounds	( void );
void init_test_menu	( struct eMenu* );

int cleanup		( void );
