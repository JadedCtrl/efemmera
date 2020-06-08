#include <sparrow3d.h>

struct eActor
{
	char name[512];

	Uint16 textColor;
	char emotePaths[20][512];
	int emoteCount;
	int emoteSelection;

	SDL_Surface* emote;
};

struct eScene 
{
	char backgroundPath[512];
	SDL_Surface* background;

	struct eActor* actor;

	SDL_Surface* surface;
};


void initScene		( struct eScene*, char[512], struct eActor* );
void drawScene		( struct eScene* );
void resizeScene	( struct eScene* );

void initActor		( struct eActor*, char[512] );
void drawActor		( struct eActor* );
void resizeActor	( struct eActor* );
void addEmote		( struct eActor*, char[512] );

