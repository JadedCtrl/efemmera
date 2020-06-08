#include <sparrow3d.h>
#include <string.h>
#include "button.h"
#include "menu.h"

// ============================================================================
// INIT
// ============================================================================
// init a menu with the given title text.
void
initMenu
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

	menu->inputDelayStep = 100;
	menu->inputCutoffStep = -1;
	menu->inputImmediate = 1;
	menu->inputDisable = 0;
	menu->inputReset = 1;

	menu->menuBgColor = menuBackgroundColor;
	menu->selectBgColor = selectBackgroundColor;

	menu->moveSound = NULL;
	menu->selectSound = NULL;
	menu->soundChannel = 0;
}

// init the given eMenuElement with the given text in an eMenu.
void
initMenuElement
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
addMenuElement
( struct eMenu* menu, char text[512] )
{
	struct eMenuElement* element = malloc(sizeof(struct eMenuElement));
	initMenuElement( menu, element, text );
}

// -------------------------------------------------------------------
// resize a menu (executed by resize loop)
void
resizeMenu ( struct eMenu* menu )
{
	if ( menu->height == 0 )
		menu->height = idealMenuHeight(menu);
	if ( menu->width == 0 )
		menu->width = idealMenuWidth(menu);

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
drawMenu ( struct eMenu* menu )
{
	SDL_Surface* old_surface = spGetRenderTarget( );
	spSelectRenderTarget( menu->surface );

	spClearTarget( menu->menuBgColor );
	if ( menu->textCentered == 0 )
		spFontDrawMiddle( menu->width / 2 * menu->scaleFactor,0,0,
				  menu->title, *(menu->font) );
	else
		spFontDraw( 0,0,0, menu->title, *(menu->font) );

	for ( int i=0; i < menu->elementCount; i++ ) {
		drawMenuElement( menu->elements[i]);
	}

	spSelectRenderTarget( old_surface );
}

// draw an eMenuElement on current target surface
void
drawMenuElement ( struct eMenuElement* element )
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
		spFontDrawMiddle( parent->width / 2 * parent->scaleFactor,
				  index * fontHeight,0,
				  element->text, *(parent->elementFont));
	else
		spFontDraw( 20,index * fontHeight,0,
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
calcMenu ( struct eMenu* menu, int sp_select_button, Uint32 steps )
{
	if ( getButton( sp_select_button, steps ) )
		return menuSelect( menu, steps );
	else if ( getButtonLim( SP_BUTTON_UP, steps,
				menu->inputDelayStep,menu->inputCutoffStep, menu->inputImmediate,
				menu->inputDisable, menu->inputReset ) )
		menuSelectUp( menu, steps ); 
	else if ( getButtonLim( SP_BUTTON_DOWN, steps,
				menu->inputDelayStep,menu->inputCutoffStep, menu->inputImmediate,
				menu->inputDisable, menu->inputReset ) )
		menuSelectDown( menu, steps ); 
	else
		return CALCMENU_NOINPUT;
	return CALCMENU_MOVED;
}


// -------------------------------------------------------------------
// returns selected menu item, and plays proper sound
int
menuSelect ( struct eMenu* menu, Uint32 steps )
{
	if ( menu->moveSound != NULL )
		spSoundPlay( menu->selectSound, menu->soundChannel,0,0,-1 );
	return menu->selection + 1;
}

// move an eMenu's selected element up by one (if possible)
void
menuSelectUp ( struct eMenu* menu, Uint32 steps )
{
	if ( 0 < menu->selection ) {
		menu->selection -= 1;
		if ( menu->moveSound != NULL )
			spSoundPlay(menu->moveSound, menu->soundChannel,0,0,-1);
	}
}

// move an eMenu's selected element down by one (if possible)
void
menuSelectDown ( struct eMenu* menu, Uint32 steps )
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
idealMenuHeight ( struct eMenu* menu )
{
	spFontPointer font        = *(menu->font);
	spFontPointer elementFont = *(menu->elementFont);
	int titleHeight   = font->maxheight;
	int elementHeight = elementFont->maxheight + 2;

	return titleHeight + (elementHeight * menu->elementCount);
}

// return menu's ideal (smallest while displaying everything) calculated width
int
idealMenuWidth ( struct eMenu* menu )
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
