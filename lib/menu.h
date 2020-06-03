#include <sparrow3d.h>

#define CALCMENU_NOINPUT -1
#define CALCMENU_MOVED   0

struct eMenu;
struct eMenuElement;

struct eMenuElement
{
	struct eMenu* parentMenu;
	char text[512];
	int index;
};


struct eMenu
{
	char title[512];
	int width;
	int height;
	int scaleFactor;

	int selection;

	spFontPointer* font;
	spFontPointer* elementFont;
	int titleCentered;
	int textCentered;

	int inputDelayStep;
	int inputCutoffStep;
	int inputDisable;
	int inputReset;
	int inputImmediate;

	int menuBgColor;
	int selectBgColor;

	SDL_Surface* surface;

	int soundChannel;
	spSound* moveSound;
	spSound* selectSound;

	int elementCount;
	struct eMenuElement *(elements[20]);
};


void initMenu		( struct eMenu*, char title[512],
			  spFontPointer*, spFontPointer*, int, int );
void initMenuElement	( struct eMenu*, struct eMenuElement*, char[512] );
void addMenuElement	( struct eMenu*, char[512] );

void drawMenu		( SDL_Surface*, struct eMenu* );
void drawMenuElement	( struct eMenuElement* );

int calcMenu		( struct eMenu*, int, Uint32 );

void resizeMenu		( struct eMenu* );

int menuSelect		( struct eMenu*, Uint32 );
void menuSelectUp	( struct eMenu*, Uint32 );
void menuSelectDown	( struct eMenu*, Uint32 );

int  idealMenuHeight	( struct eMenu* );
int  idealMenuWidth	( struct eMenu* );
