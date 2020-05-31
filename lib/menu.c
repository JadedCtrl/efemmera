#include <sparrow3d.h>
#include <string.h>
#include "menu.h"

// ============================================================================
// INIT
// ============================================================================
// init a menu with the given title text.
void
init_menu
( struct eMenu* menu, char title[512],
  spFontPointer* titleFont, spFontPointer* elementFont,
  int menuBackgroundColor, int selectBackgroundColor )
{
	strcpy(menu->title, title);

	menu->width = 0;
	menu->height = 0;
	menu->surface = NULL;

	menu->font = titleFont;
	menu->elementFont = elementFont;
	menu->titleCentered = 1;
	menu->textCentered = 1;

	menu->selection = 0;
	menu->elementCount = 0;

	menu->menuBgColor = menuBackgroundColor;
	menu->selectBgColor = selectBackgroundColor;

	menu->moveSound = NULL;
	menu->selectSound = NULL;
	menu->soundChannel = 0;
}

// init the given eMenuElement with the given text in an eMenu.
void
init_menu_element
( struct eMenu* menu, struct eMenuElement* element, char text[512] )
{
	int count = menu->elementCount;

	strcpy(element->text, text);
	element->parentMenu = menu;
	element->index = count;
	menu->elements[count] = element;
	menu->elementCount = menu->elementCount + 1;
}

// create a new eMenuElement with given text, and append to eMenu.
void
add_menu_element
( struct eMenu* menu, char text[512] )
{
	struct eMenuElement* element = malloc(sizeof(struct eMenuElement));
	init_menu_element( menu, element, text );
}

// -------------------------------------------------------------------
// resize a menu (executed by resize loop)
void
resize_menu ( struct eMenu* menu )
{
	if ( menu->height == 0 )
		menu->height = ideal_menu_height(menu);
	if ( menu->width == 0 )
		menu->width = ideal_menu_width(menu);

	menu->scaleFactor = spFixedToInt(spGetSizeFactor());
	int height        = menu->height * menu->scaleFactor;
	int width         = menu->width  * menu->scaleFactor;


	if ( menu->surface != NULL )
		spDeleteSurface( menu->surface );

	menu->surface = spCreateSurface(width, height);
}


// ============================================================================
// DRAW
// ============================================================================
// draw an eMenu on it's surface.
void
draw_menu ( SDL_Surface* surface, struct eMenu* menu )
{
	SDL_Surface* old_surface = spGetRenderTarget( );
	spSelectRenderTarget( menu->surface );

	spClearTarget( menu->menuBgColor );
	if ( menu->textCentered == 0 )
		spFontDrawMiddle ( menu->width / 2 * menu->scaleFactor,0,0, menu->title, *(menu->font) );
	else
		spFontDraw ( 0,0,0, menu->title, *(menu->font) );

	for ( int i=0; i < menu->elementCount; i++ ) {
		draw_menu_element( menu->elements[i]);
	}

	spSelectRenderTarget( old_surface );
}

// draw an eMenuElement on current target surface
void
draw_menu_element ( struct eMenuElement* element )
{
	struct eMenu* parent = element->parentMenu;
	int index = element->index;
	int selection = parent->selection;
	
	spFontPointer font = *(parent->elementFont);
	int fontHeight = font->maxheight;

	if ( index == selection ) {
		index++;
		spRectangle( 0,(index * fontHeight) + (fontHeight * .6),0,
			     parent->width * parent->scaleFactor * 2,
			     fontHeight,
			     parent->selectBgColor );
	}
	else index++;

	if ( parent->textCentered == 0 )
		spFontDrawMiddle(parent->width / 2 * parent->scaleFactor,index * fontHeight,0,
				 element->text, *(parent->elementFont));
	else
		spFontDraw(20,index * fontHeight,0,
			   element->text, *(parent->elementFont));
}


// ============================================================================
// INPUT
// ============================================================================
// calc the input for the given menu.
// returns -1 if no menu-related buttons were pressed,
// 0 if not buttons were pressed,
// otherwise return the item selected + 1.
int
calc_menu ( struct eMenu* menu, int sp_select_button )
{
	spSleep(50000);
	if ( spGetInput()->button[sp_select_button] )
		return menu_select( menu );
	else if ( spGetInput()->button[SP_BUTTON_DOWN] )
		menu_select_down( menu ); 
	else if ( spGetInput()->button[SP_BUTTON_UP] )
		menu_select_up( menu ); 
	else
		return -1;
	return 0;
}

// -------------------------------------------------------------------
// returns selected menu item, and plays proper sound
int
menu_select ( struct eMenu* menu )
{
	if ( menu->moveSound != NULL )
		spSoundPlay( menu->selectSound, menu->soundChannel,0,0,-1 );
	return menu->selection + 1;
}

// move an eMenu's selected element up by one (if possible)
void
menu_select_up ( struct eMenu* menu )
{
	if ( 0 < menu->selection ) {
		menu->selection -= 1;
		if ( menu->moveSound != NULL )
			spSoundPlay(menu->moveSound, menu->soundChannel,0,0,-1);
	}
}

// move an eMenu's selected element down by one (if possible)
void
menu_select_down ( struct eMenu* menu )
{
	if ( (menu->elementCount - 1) > menu->selection ) {
		menu->selection += 1;
		if ( menu->moveSound != NULL )
			spSoundPlay(menu->moveSound, menu->soundChannel,0,0,-1);
	}
}


// ============================================================================
// UTIL
// ============================================================================
// return menu's ideal (smallest while displaying everything) calculated height
int
ideal_menu_height ( struct eMenu* menu )
{
	spFontPointer font        = *(menu->font);
	spFontPointer elementFont = *(menu->elementFont);
	int titleHeight   = font->maxheight;
	int elementHeight = elementFont->maxheight + 2;

	return titleHeight + (elementHeight * menu->elementCount);
}

// return menu's ideal (smallest while displaying everything) calculated width
int
ideal_menu_width ( struct eMenu* menu )
{
	struct eMenuElement* element;
	int top_len = spFontWidth( menu->title, *(menu->font) );

	for ( int i = 0; i < menu->elementCount; i++ ) {
		element = menu->elements[i];
		int len = spFontWidth( element->text, *(menu->elementFont));
		if ( len > top_len )
			top_len = len;
	}
	return top_len;
}
