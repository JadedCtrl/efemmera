#include <sparrow3d.h>

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

	int menuBgColor;
	int selectBgColor;

	SDL_Surface* surface;

	int soundChannel;
	spSound* moveSound;
	spSound* selectSound;

	int elementCount;
	struct eMenuElement *(elements[20]);
};


void init_menu		( struct eMenu*, char title[512],
			  spFontPointer*, spFontPointer*, int, int );
void init_menu_element	( struct eMenu*, struct eMenuElement*, char[512] );
void add_menu_element	( struct eMenu*, char[512] );

void draw_menu		( SDL_Surface*, struct eMenu* );
void draw_menu_element	( struct eMenuElement* );

int calc_menu ( struct eMenu*, int );

void resize_menu	( struct eMenu* );

void menu_select_up	(struct eMenu* );
void menu_select_down	(struct eMenu* );

int  ideal_menu_height	( struct eMenu* );
int  ideal_menu_width	( struct eMenu* );
